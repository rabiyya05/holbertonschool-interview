#!/usr/bin/python3
"""0x09. UTF-8 Validation - task 0. UTF-8 Validation
"""


def validUTF8(data):
    """Validates UTF-8 encoding of series of bytes represented as a list of
    integers.

    bytes.decode() is a Pythonic way to automate what can be done manually by
    checking the values in a byte array. UTF-8 characters can be 1-4 bytes
    wide, and valid formatting is as follows:
        Unicode:  UTF8 bytes:   UTF8 byte prefixes:
        0-7f          1         0xxxxxxx
        80-7ff        2         110xxxxx, 10xxxxxx
        800-ffff      3         1110xxxx, 10xxxxxx, 10xxxxxx
        10000-10ffff  4         11110xxx, 10xxxxxx, 10xxxxxx, 10xxxxxx

    Args:
        data (list): list of integers representing one byte value each

    Returns:
        bool: True if encoding validated, False otherwise
    """
    if not (type(data) is list and all([isinstance(n, int) for n in data])):
        return False

    # convert signed to unsigned for bytes(), only need to consider 8 least
    # significant bits as these ints represent bytes for this exercise
    data = [n + 256 if n < 0 and n > -129 else n for n in data]

    # mask out all but 8 least significant bits
    data = [n & 0xFF if n >= 0 else n for n in data]

    try:
        # bytes.decode() default args included for clarity
        bytes(data).decode(encoding='utf-8', errors='strict')
    except (ValueError, UnicodeDecodeError):
        return False

    return True
