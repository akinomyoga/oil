#!/usr/bin/env python2
from __future__ import print_function

import unittest
import re

from data_lang import htm8


class RegexTest(unittest.TestCase):

    def testDotAll(self):
        # type: () -> None

        # Note that $ matches end of line, not end of string
        p1 = re.compile(r'.')
        print(p1.match('\n'))

        p2 = re.compile(r'.', re.DOTALL)
        print(p2.match('\n'))

        #p3 = re.compile(r'[.\n]', re.VERBOSE)
        p3 = re.compile(r'[.\n]')
        print(p3.match('\n'))

        print('Negation')

        p4 = re.compile(r'[^>]')
        print(p4.match('\n'))

    def testAttrRe(self):
        # type: () -> None
        _ATTR_RE = htm8._ATTR_RE
        m = _ATTR_RE.match(' empty= val')
        print(m.groups())


class FunctionsTest(unittest.TestCase):

    def testFindLineNum(self):
        # type: () -> None
        s = 'foo\n' * 3
        for pos in [1, 5, 10, 50]:  # out of bounds
            line_num = htm8._FindLineNum(s, pos)
            print(line_num)


class AttrLexerTest(unittest.TestCase):

    def testAttrLexer(self):
        # type: () -> None

        # TODO: h8_id.StartTag and EndTag will expose the tag_name_pos - the
        # end of the tag name

        attr_lexer = htm8.AttrLexer('x <a>')
        attr_lexer.Init(4, 4)
        attr_lexer.ReadName()

        attr_lexer = htm8.AttrLexer('x <a>')
        attr_lexer.Init(4, 4)
        attr_lexer.ReadName()


if __name__ == '__main__':
    unittest.main()
