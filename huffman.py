import fileinput
import tree

def getNgram(data):
	return data['ngram']

def codeLength(root, length): # assigns lengths (distance from root) to each node in the tree from root
	if root == None:
		return
	root.data['length'] = length
	codeLength(root.left, length+1)
	codeLength(root.right, length+1)

def printHuffCode(prefix, leaves):
	print str(prefix).replace('\n', '\x80') + ':' # print prefix
	for leaf in leaves: # print symbols and huffman code length
		print '\t' + str(leaf.data['symbol']).replace('\n', '\x80') + ' ' + str(leaf.data['length'])

def extractPrefixed(prefix, info):
	symbols = []
	prefixed = []
	for data in info:
		if data['ngram'][:-1] < prefix:
			continue
		if data['ngram'][:-1] > prefix:
			break
		if data['ngram'][:-1] == prefix:
			prefixed.append(data)
	for data in prefixed:
		symbols.append(tree.Node({ 'symbol': data['ngram'][-1:], 'prob': data['prob'] }))
		info.remove(data)
	return symbols

def makeHuffmanTree(forest): # construct huffman tree over forest
	while len(forest) > 1:
		forest.sort(key = lambda node: node.data['prob'])
		x, y = forest[:2]
		forest.remove(x)
		forest.remove(y)
		forest.append(tree.Node({'prob':x.data['prob'] + y.data['prob']}, x, y))

def getNgramsFromFile():
	info = []
	n=1
	for line in fileinput.input():
		if fileinput.lineno() == 1:
			if line != 'Ngrams\n':
				raise Exception, "Only Ngram files accepted as input"
		elif fileinput.lineno() == 2:
			n = int(line)
		else:
			ngram = line[:n]
			prob = line[(n+1):]
			info.append({'ngram': str(ngram).replace('\x80', '\n'), 'prob': int(prob)})
	return n, info

n, info = getNgramsFromFile()
info.sort(key = getNgram)

print 'Huffman'
print str(n)

while info:
	prefix = info[0]['ngram'][:-1]
	forest = extractPrefixed(prefix, info)
	makeHuffmanTree(forest)
	codeLength(forest[0], 0)
	leaves = tree.getLeaves(forest[0], [])
	printHuffCode(prefix, leaves)
	forest[0] = tree.freeTree(forest[0])
