"""
cpp/NINJA_subgraph.py
"""

from __future__ import print_function

from build import ninja_lib
from build.ninja_lib import log

# Some tests use #ifndef CPP_UNIT_TEST to disable circular dependencies on
# generated code
CPP_UNIT_MATRIX = [
  ('cxx', 'dbg', '-D CPP_UNIT_TEST'),
  ('cxx', 'asan', '-D CPP_UNIT_TEST'),
  ('cxx', 'ubsan', '-D CPP_UNIT_TEST'),
  #('cxx', 'gcevery', '-D CPP_UNIT_TEST'),
  #('cxx', 'rvroot', '-D CPP_UNIT_TEST'),
  ('clang', 'coverage', '-D CPP_UNIT_TEST'),
]

def NinjaGraph(ru):
  ru.comment('Generated by %s' % __name__)

  ru.cc_library(
      '//cpp/core', 
      srcs = ['cpp/core.cc'],
      deps = [
        '//frontend/syntax.asdl',
        '//mycpp/runtime',
        ],
  )

  ru.cc_binary(
      'cpp/core_test.cc',
      deps = [
        '//cpp/core',
        '//cpp/bindings',  # TODO: it's only stdlib
        ],
      matrix = ninja_lib.COMPILERS_VARIANTS)

  ru.cc_binary(
      'cpp/data_race_test.cc',
      deps = [
        '//cpp/core',
        '//mycpp/runtime',
        ],
      matrix = ninja_lib.SMALL_TEST_MATRIX + [
        ('cxx', 'tsan'),
        ('clang', 'tsan'),
      ])

  # Note: depends on code generated by re2c
  ru.cc_library(
      '//cpp/frontend_match', 
      srcs = [
        'cpp/frontend_match.cc',
      ],
      deps = [
        '//frontend/syntax.asdl',
        '//frontend/types.asdl',
        '//mycpp/runtime',
      ],
  )

  ru.cc_binary(
      'cpp/frontend_match_test.cc',
      deps = ['//cpp/frontend_match'],
      matrix = ninja_lib.COMPILERS_VARIANTS)

  ru.cc_library(
      '//cpp/frontend_flag_spec', 
      srcs = [
        'cpp/frontend_flag_spec.cc',
      ],
      deps = [
        '//core/runtime.asdl',
        '//frontend/arg_types',  # generated code
        '//mycpp/runtime',
      ],
  )

  ru.cc_binary(
      'cpp/frontend_flag_spec_test.cc',
      deps = ['//cpp/frontend_flag_spec'],
      # special -D CPP_UNIT_TEST
      matrix = CPP_UNIT_MATRIX)

  ru.cc_library(
      '//cpp/libc', 
      srcs = ['cpp/libc.cc'],
      deps = ['//mycpp/runtime'])

  ru.cc_binary(
      'cpp/libc_test.cc', 
      deps = ['//cpp/libc'],
      matrix = ninja_lib.COMPILERS_VARIANTS)

  ru.cc_library(
      '//cpp/osh', 
      srcs = ['cpp/osh.cc'],
      deps = [
        '//frontend/syntax.asdl', 
        '//cpp/core', 
        '//mycpp/runtime', 
      ]
  )

  ru.cc_binary(
      'cpp/osh_test.cc', 
      deps = ['//cpp/osh'],
      matrix = ninja_lib.COMPILERS_VARIANTS)

  ru.cc_library(
      '//cpp/bindings', 
      # TODO: split these into their own libraries
      srcs = [
        'cpp/frontend_tdop.cc',
        'cpp/pgen2.cc',
        'cpp/pylib.cc',
        'cpp/stdlib.cc',
      ],
  )

  ru.cc_binary(
      'cpp/binding_test.cc',
      deps = [
        '//core/runtime.asdl',  # sizeof_test uses this
        '//cpp/bindings',
        '//mycpp/runtime',
        ],
      matrix = ninja_lib.COMPILERS_VARIANTS)

  # Note: there is no cc_library() for qsn.h
  ru.cc_binary(
      'cpp/qsn_test.cc',
      deps = [
        '//mycpp/runtime',
        ],
      matrix = ninja_lib.COMPILERS_VARIANTS)
