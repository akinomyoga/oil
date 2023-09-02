#!/usr/bin/env bash
#
# Make lists of source code
#
# Usage:
#   doctools/src-tree.sh <function name>

set -o nounset
set -o pipefail
set -o errexit

REPO_ROOT=$(cd $(dirname $0)/.. && pwd)  # tsv-lib.sh uses this
readonly REPO_ROOT

source test/common.sh
source test/tsv-lib.sh

export PYTHONPATH=.

test-src-tree() {
  local out=_tmp/src-tree
  doctools/src_tree.py files $out stdlib/*.ysh spec/*.test.sh
}

repo() {
  git ls-files
}

no-cpython() {
  grep -v 'Python-2.7.13'
}

compress() {
  local out=_tmp/source-code.zip

  rm -f -v $out

  repo | no-cpython | xargs --verbose -- zip $out
  echo

  # 1688 files in 3.6 MB, OK seems fine
  repo | no-cpython | wc -l

  ls -l -h $out
}

extensions() {
  repo \
    | no-cpython \
    | grep -v 'testdata/' \
    | awk --field-separator . '{ print $(NF) }' \
    | sort | uniq -c | sort -n
}

metrics() {
  metrics/source-code.sh osh-files
  echo
  metrics/source-code.sh ysh-files

  # Also see metrics/line_counts.py (104 lines)
}

line-counts() {
  metrics/source-code.sh overview
  metrics/source-code.sh for-translation
}

lint() {
  # We're not formatting now
  test/lint.sh py2-files-to-format
  echo
  test/lint.sh py3-files
}

important() {
  build/doc.sh important-source-code
}

# _tmp/source-code/
#   lines.attrs - Intermediate file format
#
# osh/README.md lines=1   
# osh/foo.py sloc=23
# osh/foo.py overview=true
#
# can also be:
# j"osh/README.md" {"lines": 1}
# or 
# {"name": "osh/README.md", "lines": 1}
#
# doctools/do_files.py
#   - sometimes, count lines
#   - sometimes, count significant lines
#     - output syntax highlighted files
#     - breadcrumb, link to github
#   - output ATTRS file
#
# shell:
#   overview, for-translation, etc.

# doctools/do_dirs.py
#   - read all the ATTRS files
#   - output _tmp/source/code/{,osh,...}/index.html
#     - with subdir counts

# 2. THen
# Pipe those in by lines, cat them



# Source Viewer Features
#
# - Dirs with entry counts (recursive I think)
# - Files with line counts
#   - sloc?  But what if we don't have it?
# - Breadcrumb
# - Filtering by sets
#   - this is hard because it's N dimensional
#   - I think you may just highlight by set
#     - or do some light JavaScript, letting you hide files
#     - you can embed JSON
#     - you can have checkboxes on each page
#     - do this LATER

# Sets of files
#
# test/lint.sh
#   py2-files-to-format
#   py3-files
#
# metrics/source-code.sh overview
# metrics/source-code.sh for-translation
#
# These should be corrected
#
#   osh-files
#   ysh-files

# spec tests:
# 
# test/spec-runner.sh all-tests-to-html

# Columns
# - Name
# - Number of lines
# - Can we get the cloc or sloccount report?
#   - https://github.com/AlDanial/cloc - this is a 17K line Perl script!
#   - https://dwheeler.com/sloccount/ - no release since 2004 ?
#
# Honestly I want to write my own
#  - syntax highlighter, that finds string literals and comments
#  - as a side effect it estimates significant lines of code
#    - minus comments and blank lines
#  - supports
#    - Python - multi-line strings
#    - shell and YSH -- here docs?
#    - C++ - #ifdef, including #if 0 perhaps
#    - ASDL - just blank lines and comments
#    - maybe grammar files



if test $(basename $0) = 'src-tree.sh'; then
  "$@"
fi
