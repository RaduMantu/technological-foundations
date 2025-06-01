#!/usr/bin/python3

import sys

inv = {
    # have a free one, on us
    'L' : 'A',
}

def main():
    # cli arguments check
    if len(sys.argv) != 2:
        print('Usage ./04-solver.py <input_file>')

    # read contents of file
    with open(sys.argv[1]) as f:
        enc = f.read()

    # make sure text is uppercase
    enc = enc.upper()

    # create (partially) translated text
    dec = [ it if it not in inv else '\033[1;31m%s\033[0m' % inv[it] \
            for it in enc ]
    dec = ''.join(dec)

    # print translated text
    print(dec)

# program entry point
if __name__ == '__main__':
    main()

