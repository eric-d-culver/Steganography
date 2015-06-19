# Steganography
## Files 
This contains the following files:
- ensteg.c
- desteg.c
- deal.c
- shuffle.c
- ngram_count.py
- huffman.py
- pyngram.py
- tree.py

## Usage
**ensteg.c**
- ensteg input.pnm file.data output.pnm  
Takes an input picture in a pnm binary format (P4, P5, P6) with no comments and hides the bytes of file.data in the least significant bit of the pixels of the picture and outputs the result in the same format.

**desteg.c**
- desteg input.pnm hidden.data  
Takes an input picture in a pnm binary format (P4, P5, P6) with no comments and extracts the least significant bit of each pixel and outputs them into hidden.data

**deal.c**
- deal input.data number  
Takes the bytes in input.data and "deals" them into num files (named input0.data, input1.data, etc.) by putting the first byte into the first file, the second byte into the second file, and so on.

**shuffle.c**
- shuffle input0.data input1.data ...  
Takes the bytes of the input files and shuffles them into one file (named input.data, i.e. simply remove the number from the first filename) by taking the first byte of the first file, then the first byte of the second file, and so on, then the second byte of each file, and then the third byte, and so on.

**ngram_count.py**
- python ngram_count.py [-b] filename n > ngramfile  
Counts the ngrams in input file and outputs "Ngrams" followed by the value of n, followed by all the ngrams in the input file a pipe and their frequency, ordered with highest frequency first.  The output of this can be used as the input for a mimic function.  
Uses Python module pyngram (included).  

**huffman.py**
- python huffman.py ngramfile > huffmanfile
Groups the ngrams by the first n-1 characters, then constructs Huffman codes for them.  Outputs "Huffman" then the value of n, then the prefix, followed by an indented list of the symbols and code lengths, for all the prefixes in the ngram file.

**pyngram.py**  
Python module used in ngram_count.py. Created by [Jay Liew].

**tree.py**
Python script defining the Node class to make tree creation easier in huffman.py

## Acknowledgements
The code in ensteg.c and desteg.c is based off of code by [Joshua Shagam]
Python module pyngram created by [Jay Liew]

<!-- Links -->
[Josuha Shagam]: http://www.cs.nmsu.edu/~joshagam/css/
[Jay Liew]: http://jayliew.com/
