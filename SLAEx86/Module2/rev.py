#!/usr/bin/python3

import binascii

code = 'Hello World\n'

code = ""

coderev = code[::-1]

print(coderev)
print(len(code))
# in python2, print(coderev.encode('hex'))
print(binascii.hexlify(coderev.encode()))
