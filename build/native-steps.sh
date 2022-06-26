#!/usr/bin/env bash
#
# Actions invoked by build.ninja, which is generated by build/native_graph.py.
#
# Also some non-Ninja wrappers.
#
# Usage:
#   build/native-steps.sh <function name>

set -o nounset
set -o errexit
#eval 'set -o pipefail'

REPO_ROOT=$(cd $(dirname $0)/..; pwd)
readonly REPO_ROOT

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
  local variant=$1
  local dotd=${2:-}

  flags="
    $BASE_CXXFLAGS
    -I . 
    -I mycpp 
    -I cpp 
    -I _build/cpp 
    -I _devbuild/gen 
  "

  #
  # Environment variables respected
  #

  local more_flags=${CXXFLAGS:-}
  if test -n "$more_flags"; then
    flags="$flags $more_flags"
  fi

  case $variant in
    (dbg)
      flags="$flags -O0 -g"
      ;;
    (asan)
      # Note: Clang's ASAN doesn't like DUMB_ALLOC, but GCC is fine with it
      flags="$flags -O0 -g -fsanitize=address"
      ;;
    (opt)
      flags="$flags -O2 -g -D DUMB_ALLOC"
      # To debug crash with 8 byte alignment
      #flags="$CPPFLAGS -O0 -g -D DUMB_ALLOC -D ALLOC_LOG"
      ;;

    (uftrace)
      # -O0 creates a A LOT more data.  But sometimes we want to see the
      # structure of the code.
      # vector::size(), std::forward, len(), etc. are not inlined.
      # Also List::List, Tuple2::at0, etc.
      #local opt='-O2'
      local opt='-O0'

      # Do we want DUMB_ALLOC here?
      flags="$flags $opt -g -pg"
      ;;

    (malloc)
      flags="$flags -O2 -g"
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

  # Avoid memset().  TODO: remove this hack!
  flags="$flags -D NO_GC_HACK"

  # hack for osh_eval_stubs.h
  flags="$flags -D OSH_EVAL"

  # QSN is a special case used by the ASDL runtime
  flags="$flags -D USING_OLD_QSN"

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
    (asan)
      link_flags='-fsanitize=address'
      ;;
  esac

  link_flags="$link_flags -Wl,--gc-sections "
}

compile_one() {
  ### Compile one translation unit.  Invoked by build.ninja

  # Supports CXXFLAGS

  local compiler=$1
  local variant=$2
  local in=$3
  local out=$4
  local dotd=${5:-}  # optional .d file

  setglobal_compile_flags "$variant" "$dotd"

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
    flags="$flags -ferror-limit=1000"
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
  local out=$3
  shift 3

  setglobal_compile_flags "$variant" ""

  setglobal_link_flags $variant

  setglobal_cxx $compiler

  "$cxx" -o "$out" $flags "$@" $link_flags
}

strip_() {
  ### Invoked by ninja

  local in=$1
  local stripped=$2
  local symbols=$3

  strip -o $stripped $in

  objcopy --only-keep-debug $in $symbols
  objcopy --add-gnu-debuglink=$symbols $stripped
}

# test/cpp-unit.sh sources this
if test $(basename $0) = 'native-steps.sh'; then
  "$@"
fi
