#!/usr/bin/env python
import fileinput, sys
import bitFile
import huffFileRead

def getCode(symbols, char):
        for thing in symbols:
                if thing['symbol'] == char:
                        return thing['code']
        return []

def decode(infile, outfile, info, n): # write a file bit by bit using codes in info
        output = bitFile.bitWrite(outfile)
        prefix = list(infile.read(n-1)) # prefix is first n-1 characters (the seed)
        char = infile.read(1)
        while char:
                symbols = info[''.join(prefix)]
                code = getCode(symbols, char) # find code corresponding to prefix and next char
                output.write(code) # write those bits to outfile
                prefix.append(char) # shift prefix
                prefix = prefix[1:]
                char = infile.read(1) # read next char

if __name__ == "__main__": # Stdout should be the file that is being hidden, stdin is file mimicing freqs of huffman file
        if len(sys.argv) > 2:
                infofile = open(sys.argv[2], 'r')
                infile = open(sys.argv[1], 'r')
        elif len(sys.argv) > 1:
                infofile = open("huffman5.txt", 'r')
                infile = open(sys.argv[1], 'r')
        else:
                infofile = open("huffman5.txt", 'r')
                infile = sys.stdin

        outfile = sys.stdout
        n, info = huffFileRead.huffRead(infofile)
        #print info
        decode(infile, outfile, info, n)
        infofile.close()
        infile.close()
