#!/bin/python

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

def flatten(info): # 'flatten' by making the prefixes the keys
	newInfo = {}
	for thing in info:
		newInfo[thing['prefix']] = thing['symbols']
	return newInfo

def huffRead(infofile): # read file, add codes, flatten
    n, info = readHuffman(infofile)
    giveCodes(info)
    info = flatten(info)
    return info
