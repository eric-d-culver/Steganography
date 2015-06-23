import sys, argparse
from pyngram import calc_ngram

def ngrams_text(file, n):
	return calc_ngram(file.read().replace("\n", ""), n)

def ngrams_bin(file, n):
	return calc_ngram(file.read(), n)

def print_ngrams(ngrams, n):
	print 'Ngrams'
	print str(n)
	for t in ngrams:
		print t[0] + " " + str(t[1])

if __name__ == '__main__':
	parser = argparse.ArgumentParser(description='Creates ngram probabilities for input file')
	parser.add_argument('-b', dest='binary', action='store_const', const=ngrams_bin, default=ngrams_text, help='binary file (defaults: text file)')
	parser.add_argument('-i', dest='filename', type=file, default=sys.stdin, help='name of file')
	parser.add_argument('n', type=int, help='size of ngrams in characters')
	args = parser.parse_args()
	print_ngrams(args.binary(args.filename, args.n), args.n)

