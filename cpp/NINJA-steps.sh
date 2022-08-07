#!/usr/bin/env bash
#
# Actions invoked by build.ninja, which is generated by ./NINJA_config.py.
#
# Also some non-Ninja wrappers.
#
# Usage:
#   build/NINJA-steps.sh <function name>

set -o nounset
set -o errexit
#eval 'set -o pipefail'

REPO_ROOT=$(cd "$(dirname $0)/.."; pwd)

. build/common.sh  # for $BASE_CXXFLAGS

line_count() {
  local out=$1
  shift  # rest are inputs
  wc -l "$@" | sort -n | tee $out
}

#
# Mutable GLOBALS
#

cxx=''         # compiler
flags=''       # compile flags
link_flags=''  # link flags

#
# Functions to set them
#

setglobal_cxx() {
  local compiler=$1

  case $compiler in 
    (cxx)   cxx='c++'    ;;
    (clang) cxx=$CLANGXX ;;
    (*)     die "Invalid compiler $compiler" ;;
  esac
}

setglobal_compile_flags() {
  ### Set flags based on $variant $more_cxx_flags and $dotd

  local variant=$1
  local more_cxx_flags=$2
  local dotd=${3:-}

  # Args from Ninja/shell respected
  flags="$BASE_CXXFLAGS $more_cxx_flags"

  # Environment variables respected
  local env_flags=${CXXFLAGS:-}
  if test -n "$env_flags"; then
    flags="$flags $env_flags"
  fi

  flags="$flags -I $REPO_ROOT"

  case $variant in
    (dbg)
      flags="$flags -O0 -g"
      ;;

    (coverage)
      # source-based coverage is more precise than say sanitizer-based
      # https://clang.llvm.org/docs/SourceBasedCodeCoverage.html
      flags="$flags -O0 -g -fprofile-instr-generate -fcoverage-mapping"
      ;;

    (asan)
      flags="$flags -O0 -g -fsanitize=address"
      ;;

    (ubsan)
      # faster build with -O0
      flags="$flags -O0 -g -fsanitize=undefined"
      ;;

    (gcstats)
      # unit tests use for gHeap.Report()
      flags="$flags -g -D GC_PROTECT -D GC_STATS"
      ;;

    (gcevery)
      flags="$flags -g -D GC_PROTECT -D GC_STATS -D GC_EVERY_ALLOC"
      ;;

    (oldstl)
      # Could this be ASAN?
      # For cpp/gc_binding_test
      flags="$flags -O0 -g -D OLDSTL_BINDINGS"
      ;;

    (opt)
      flags="$flags -O2 -g"
      ;;
    (dumballoc)
      # optimized build with bump allocator
      flags="$flags -O2 -g -D DUMB_ALLOC"
      ;;

    (uftrace)
      # -O0 creates a A LOT more data.  But sometimes we want to see the
      # structure of the code.
      # vector::size(), std::forward, len(), etc. are not inlined.
      # Also List::List, Tuple2::at0, etc.
      #local opt='-O2'
      local opt='-O0'
      flags="$flags $opt -g -pg"
      ;;

    (tcmalloc)
      flags="$flags -O2 -g -D TCMALLOC"
      ;;
    (alloclog)
      # debug flags
      flags="$flags -O0 -g -D DUMB_ALLOC -D ALLOC_LOG"
      ;;

    (*)
      die "Invalid variant $variant"
      ;;
  esac

  # needed to strip unused symbols
  # https://stackoverflow.com/questions/6687630/how-to-remove-unused-c-c-symbols-with-gcc-and-ld

  # Note: -ftlo doesn't do anything for size?

  flags="$flags -fdata-sections -ffunction-sections"

  # https://ninja-build.org/manual.html#ref_headers
  if test -n "$dotd"; then
    flags="$flags -MD -MF $dotd"
  fi
}

setglobal_link_flags() {
  local variant=$1

  case $variant in
    (tcmalloc)
      link_flags='-ltcmalloc'
      ;;

    # Must REPEAT these flags, otherwise we lose sanitizers / coverage
    (asan)
      link_flags='-fsanitize=address'
      ;;
    (ubsan)
      link_flags='-fsanitize=undefined'
      ;;
    (coverage)
      link_flags='-fprofile-instr-generate -fcoverage-mapping'
      ;;
  esac

  link_flags="$link_flags -Wl,--gc-sections "
}

compile_one() {
  ### Compile one translation unit.  Invoked by build.ninja

  local compiler=$1
  local variant=$2
  local more_cxx_flags=$3
  local in=$4
  local out=$5
  local dotd=${6:-}  # optional .d file

  setglobal_compile_flags "$variant" "$more_cxx_flags" "$dotd"

  case $out in
    (_build/preprocessed/*)
      flags="$flags -E"
      ;;

    # DISABLE spew for generated code.  mycpp/pea could flag this at the PYTHON
    # level, rather than doing it at the C++ level.
    (_build/obj/*/osh_eval.*)
      flags="$flags -Wno-unused-variable -Wno-unused-but-set-variable"
      ;;
  esac

  # TODO: exactly when is -fPIC needed?  Clang needs it sometimes?
  if test $compiler = 'clang' && test $variant != 'opt'; then
    flags="$flags -fPIC"
  fi

  # this flag is only valid in Clang, doesn't work in continuous build
  if test "$compiler" = 'clang'; then
    flags="$flags -ferror-limit=10"
  fi

  setglobal_cxx $compiler

  "$cxx" $flags -o "$out" -c "$in"
}

link() {
  ### Link oil-native.  Invoked by build.ninja

  local compiler=$1
  local variant=$2
  local out=$3
  shift 3
  # rest are inputs

  setglobal_link_flags $variant

  setglobal_cxx $compiler

  "$cxx" -o "$out" $link_flags "$@"
}

compile_and_link() {
  local compiler=$1
  local variant=$2
  local more_cxx_flags=$3
  local out=$4
  shift 4


  setglobal_compile_flags "$variant" "$more_cxx_flags" ""  # no dotd

  setglobal_link_flags $variant

  setglobal_cxx $compiler

  echo ""
  echo "Building: $cxx -o $out $flags $@ $link_flags"
  echo ""
  "$cxx" -o "$out" $flags "$@" $link_flags
}

strip_() {
  ### Invoked by ninja

  local in=$1
  local stripped=$2
  local symbols=${3:-}

  strip -o $stripped $in

  if test -n "$symbols"; then
    objcopy --only-keep-debug $in $symbols
    objcopy --add-gnu-debuglink=$symbols $stripped
  fi
}

# test/cpp-unit.sh sources this
if test $(basename $0) = 'NINJA-steps.sh'; then
  "$@"
fi
