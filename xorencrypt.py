# Red Team Operator course code template
# payload encryption with XOR
#
# author: reenz0h (twitter: @sektor7net)

import sys

KEY = "mysecretkeee"

def xor(data, key):
    key = str(key)
    l = len(key)
    output_bytes = bytearray()

    for i in range(len(data)):
        current = data[i]  # data is now a byte, no need for ord()
        current_key = ord(key[i % len(key)])  # ord() is applied only to the key
        output_bytes.append(current ^ current_key)

    return output_bytes

def printCiphertext(ciphertext):
    print('{ 0x' + ', 0x'.join(hex(x)[2:] for x in ciphertext) + ' };')

try:
    plaintext = open(sys.argv[1], "rb").read()  # read as binary data
except:
    print("File argument needed! %s <raw payload file>" % sys.argv[0])
    sys.exit()

ciphertext = xor(plaintext, KEY)
printCiphertext(ciphertext)

