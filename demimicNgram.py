#!/usr/bin/env python
import fileinput, sys
import bitFile

def readHuffman(file): # read info from Huffman file
	info=[]
	n=1
	symbols=[]
	for linenum, line in enumerate(file):
		if linenum == 0:
			if line != 'Huffman\n':
				raise Exception, "Only Huffman file accepted as input"
		elif linenum == 1:
			n = int(line)
		elif line[0] == '\t':
			symbols.append({'symbol': line[1].replace('\x80', '\n'), 'length': int(line[3:])})
		else:
			if len(info) > 0:
				symbols.sort(key = lambda thing: thing['length'])
				info[-1]['symbols'] = symbols
			symbols=[]
			info.append({'prefix': line[:(n-1)].replace('\x80', '\n')})
	info[-1]['symbols'] = sorted(symbols, key = lambda thing: thing['length'])
	return n, info

def addOne(list):
	if list == []:
		list.append(1)
	elif list[-1] == 0:
		list[-1] = 1
	else:
		list[-1] = 0
		list [:-1] = addOne(list[:-1])
	return list

def giveCodes(info): # assign codes to each symbol based on lengths (symbols in symbols should be sorted by length)
	for thing in info:
		curCode = []
		for symbol in thing['symbols']:
			while len(curCode) < symbol['length']:
				curCode.append(0)
			symbol['code'] = list(curCode)
			curCode = addOne(curCode)

def getSymbols(info, prefix):
	for thing in info:
		if thing['prefix'] == prefix:
			return thing['symbols']
	return []

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
		symbols = getSymbols(info, ''.join(prefix))
		code = getCode(symbols, char)
		#print str(code)
		output.write(code)
		# shift prefix
		#print prefix
		prefix.append(char)
		prefix = prefix[1:]
		char = infile.read(1)

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

	#print "reading Huffman"
	n, info = readHuffman(infofile)
	#print "giving codes"
	giveCodes(info)
	#print "decoding"
	'''
	for thing in info:
		if thing['prefix'] == 'The ':
			print thing['symbols']
	'''
	decode(infile, sys.stdout, info, n)
	infofile.close()
	infile.close()
