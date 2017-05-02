#!/usr/bin/env python
import fileinput, sys
import bitFile
import huffFileRead

def encode(infile, outfile, info, seed = ''): # read file bit by bit and encode using codes in info into output stream
	inBits = bitFile.bitRead(infile)
	outfile.write(seed)
	prefix = list(seed)
	while len(inBits.peek(1)) != 0:
		symbols = info[''.join(prefix)]
		# using symbols and bits from input.read(), determine what the next symbol is
		nextChar = ''
		for thing in symbols:
			if inBits.peek(thing['length']) == thing['code']:
                                inBits.read(thing['length'])
				nextChar = thing['symbol']
                                break
                if nextChar == '':
                    nextChar = ' ' # if the prefix does not occur in huffman file, add a space
		# write next symbol to output and shift prefix
		outfile.write(nextChar)
		prefix.append(nextChar)
		prefix = prefix[1:]

if __name__ == "__main__": # Stdin should be the file that is being hidden, stdout is file mimicing freqs of huffman file
        if len(sys.argv) > 3:
                prefix = sys.argv[3]
                infofile = open(sys.argv[2], 'r')
                infile = open(sys.argv[1], 'r')
	elif len(sys.argv) > 2:
                prefix = "Shall I c"
		infofile = open(sys.argv[2], 'r')
		infile = open(sys.argv[1], 'r')
	elif len(sys.argv) > 1:
                prefix = "Shall I c"
		infofile = open("huffman10.txt", 'r')
		infile = open(sys.argv[1], 'r')
	else:
                prefix = "Shall I c"
		infofile = open("huffman10.txt", 'r')
		infile = sys.stdin

        #outfile = open("play10.txt", 'w')
        outfile = sys.stdout
        n, info = huffFileRead.huffRead(infofile)
        #print info
	encode(infile, outfile, info, prefix)
	infofile.close()
	infile.close()
