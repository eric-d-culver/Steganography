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
				#print "lengthening"
				#print curCode
				curCode.append(0)
			symbol['code'] = list(curCode)
			#print "assigning"
			#print curCode
			curCode = addOne(curCode)
			#print "adding one"
			#print curCode

def getSymbols(info, prefix):
	for thing in info:
		if thing['prefix'] == prefix:
			return thing['symbols']
	return []

def encode(infile, outfile, info, seed = ''): # read file bit by bit and encode using codes in info into output stream
	input = bitFile.bitRead(infile)
	outfile.write(seed)
	prefix = list(seed)
	while len(input.peek(1)) != 0:
		symbols = getSymbols(info, ''.join(prefix))
		# using symbols and bits from input.read(), determine what the next symbol is
		next = ''
		for thing in symbols:
			if input.peek(thing['length']) == thing['code']:
				input.read(thing['length'])
				next = thing['symbol']
		# write next symbol to output and shift prefix
		if next == '':
			next = ' '
		outfile.write(next)
		prefix.append(next)
		prefix = prefix[1:]
		#print prefix

if __name__ == "__main__": # Stdin should be the file that is being hidden, stdout is file mimicing freqs of huffman file
	if len(sys.argv) > 2:
		infofile = open(sys.argv[2], 'r')
		infile = open(sys.argv[1], 'r')
	elif len(sys.argv) > 1:
		infofile = open("huffman5.txt", 'r')
		infile = open(sys.argv[1], 'r')
	else:
		infofile = open("huffman5.txt", 'r')
		infile = sys.stdin

	n, info = readHuffman(infofile)
	giveCodes(info)
	encode(infile, sys.stdout, info, "The ")
	'''
	for thing in info:
		if thing['prefix'] == "    ":
			print thing
	'''
	infofile.close()
	infile.close()
