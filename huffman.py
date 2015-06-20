import fileinput
import tree

def getNgram(data):
	return data['ngram']

def codeLength(root, length):
	if root == None:
		return
	root.data['length'] = length
	codeLength(root.left, length+1)
	codeLength(root.right, length+1)

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
		info.append({'ngram': str(ngram), 'prob': int(prob)})

info.sort(key = getNgram)

print 'Huffman'
print str(n)

while info:
	prefix = info[0]['ngram'][:-1]
	forest = []
	prefixed = []
	for data in info:
		if data['ngram'][:-1] < prefix:
			continue
		if data['ngram'][:-1] > prefix:
			break
		if data['ngram'][:-1] == prefix:
			prefixed.append(data)
	for data in prefixed:
		forest.append(tree.Node({ 'symbol': data['ngram'][-1:], 'prob': data['prob'] }))
		info.remove(data)
	# construct huffman tree over forest
	while len(forest) > 1:
		forest.sort(key = lambda node: node.data['prob'])
		x, y, forest = forest[0], forest[1], forest[2:]
		forest.append(tree.Node({'prob':x.data['prob'] + y.data['prob']}, x, y))
	codeLength(forest[0], 0)
	leaves = []
	tree.getLeaves(forest[0], leaves)
	# print prefix
	print prefix + ':'
	# print symbols and huffman code length
	for leaf in leaves:
		print '\t' + str(leaf.data['symbol']) + ' ' + str(leaf.data['length'])
	forest[0] = tree.freeTree(forest[0])
