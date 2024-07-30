"""num.py - math functions"""
from __future__ import print_function

from _devbuild.gen.value_asdl import value
from mycpp import mops


def ToBig(i):
    # type: (int) -> value.Int
    return value.Int(mops.IntWiden(i))


def Exponent(x, y):
    # type: (mops.BigInt, mops.BigInt) -> mops.BigInt

    # TODO: can we avoid this?
    y_int = mops.BigTruncate(y)

    assert y_int >= 0, 'checked by caller'

    result = mops.BigInt(1)
    for i in xrange(y_int):
        result = mops.Mul(result, x)
    return result


def IntDivide(x, y):
    # type: (mops.BigInt, mops.BigInt) -> mops.BigInt
    """
    Implementation that only uses the host language (Python or C++) to divide
    non-negative numbers.  Python rounds toward negative infinity, while C++
    rounds toward zero.

    Oils rounds toward zero.
    """
    assert y.i != 0, 'checked by caller'

    sign = 1

    if mops.Greater(mops.ZERO, x):
        ax = mops.Negate(x)
        sign = -1
    else:
        ax = x

    if mops.Greater(mops.ZERO, y):
        ay = mops.Negate(y)
        sign = -sign
    else:
        ay = y

    return mops.Mul(mops.IntWiden(sign), mops.Div(ax, ay))


def IntRemainder(x, y):
    # type: (mops.BigInt, mops.BigInt) -> mops.BigInt
    """
    Implementation that only uses the host language (Python or C++) to divide
    non-negative numbers.

    Takes the sign of the first argument x.

    Python % is modulus, while C % is remainder.  Both OSH and YSH % is
    remainder, like C.
    """
    assert y.i != 0, 'checked by caller'

    if mops.Greater(mops.ZERO, x):
        ax = mops.Negate(x)
        sign = -1
    else:
        ax = x
        sign = 1

    if mops.Greater(mops.ZERO, y):
        ay = mops.Negate(y)
    else:
        ay = y

    # Only use host language % on non-negative numbers.  Apply sign afteward.
    return mops.Mul(mops.IntWiden(sign), mops.Rem(ax, ay))
