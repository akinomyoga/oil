"""
bin/NINJA_subgraph.py
"""

from __future__ import print_function

from build import ninja_lib
from build.ninja_lib import log

_ = log


# TODO: remove this; probably should be sh_binary
RULES_PY = 'build/ninja-rules-py.sh'

def NinjaGraph(ru):
  n = ru.n

  ru.comment('Generated by %s' % __name__)

  with open('_build/NINJA/osh_eval/translate.txt') as f:
    deps = [line.strip() for line in f]

  prefix = '_gen/bin/osh_eval.mycpp'
  # header exports osh.cmd_eval
  outputs = [prefix + '.cc', prefix + '.h']
  n.build(outputs, 'gen-osh-eval', deps,
          implicit=['_bin/shwrap/mycpp_main', RULES_PY],
          variables=[('out_prefix', prefix)])

  # The main program!

  ru.cc_binary(
      '_gen/bin/osh_eval.mycpp.cc',
      preprocessed = True,
      matrix = ninja_lib.COMPILERS_VARIANTS + ninja_lib.GC_PERF_VARIANTS,
      top_level = True,  # _bin/cxx-dbg/osh_eval
      deps = [
        '//cpp/core',
        '//cpp/libc',
        '//cpp/osh',
        '//cpp/bindings',
        '//cpp/frontend_flag_spec',
        '//cpp/frontend_match',

        '//frontend/arg_types',
        '//frontend/consts',
        '//frontend/id_kind.asdl',
        '//frontend/option.asdl',
        '//frontend/signal',
        '//frontend/syntax.asdl',
        '//frontend/types.asdl',

        '//core/optview',
        '//core/runtime.asdl',

        '//osh/arith_parse',
        '//oil_lang/grammar',

        '//mycpp/runtime',
        ]
      )
