# Steganography
## Files 
This contains the following files:
- ensteg.c
- desteg.c
- deal.c
- shuffle.c
- ngram_count.py

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
Counts the ngrams in input file and outputs "Ngram file" followed by the value of n, followed by all the ngrams in the input file a pipe and their frequency, ordered with highest frequency first.  The output of this can be used as the input for a mimic function.
Uses non-standard Python module pyngram.  Can be installed with 'sudo pip install pyngram'.

## Acknowledgements
The code in ensteg.c and desteg.c is based off of code by [Joshua Shagam](http://www.cs.nmsu.edu/~joshagam/css/)
