# Steganography
## Purpose
This is a series of small programs written in C and Python that can be used as Steganographic tools.  There are tools to hide information in pictures, split information into several files, and make information mimic the look of different information.  Most programs come in pairs, one to hide the information, and one to find the information that someone else has hidden.  The purpose of these is not to make your data "safe" or unreadable by a snooper.  If someone knows that you have hidden data in a picture, they can easily find it.  The purpose of these, and Steganography in general, is to make it hard for someone who doesn't know where you hid the data to find it. If you want your data to be secure, encrypt it.   
The Python scripts can be converted to C code with a Cython interpreter, then all the code can be converted to executables with a C compiler.
## Files 
This contains the following files:
- ensteg.c
- desteg.c
- deal.c
- shuffle.c
- ngram_count.py
- huffman.py
- mimic.py
- pyngram.py
- tree.py
- bitFile.py

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
- python ngram_count.py -i filename n > ngramfile  
Counts the ngrams in input file and outputs "Ngrams" followed by the value of n, followed by all the ngrams in the input file a space and their frequency, ordered with highest frequency first.  Replaces newlines with the padding character U+80 to ease reading of output file.  The output of this can be used as the input for huffman.py.  
Uses Python module pyngram (included).  

**huffman.py**
- python huffman.py ngramfile > huffmanfile
Groups the ngrams by the first n-1 characters, then constructs Huffman codes for them.  Outputs "Huffman" then the value of n, then the prefix, followed by an indented list of the symbols and code lengths, for all the prefixes in the ngram file. Reads padding character U+80 as a newline, and outputs U+80 to mean a newline for ease of reading the output file.

**mimic.py**
- python mimic.py inputfile huffmanfile > outputfile  
Converts the inputfile into a file mimicking the relative frequencies expressed in the huffmanfile.  Can read to inputfile from standard input, outputs to standard output. Simplisically, the inputfile is treated as a Huffman-encoded bitstream and it is decoded using the information in the huffmanfile into the outputfile.  Expanding on that, the huffmanfile contains information about the ngrams of the file being mimicked.  The program starts with a seed of length n-1, and using that as the prefix, determines the next symbol based on the relative frequency of the ngrams starting with that prefix.  The inputfile is used as the 'random' bitstream to determine which symbol to pick.

**pyngram.py**  
Python module used in ngram_count.py. Created by [Jay Liew].

**tree.py**  
Python script defining the Node class to make tree creation and manipulation easier in huffman.py

**bitFile.py**  
Python script defining the bitRead class to allow files to be easily read one bit at a time.  Used in mimic.py.

## Acknowledgements
The code in ensteg.c and desteg.c is based off of code by [Joshua Shagam]  
Python module pyngram created by [Jay Liew]  

<!-- Links -->
[Josuha Shagam]: http://www.cs.nmsu.edu/~joshagam/css/
[Jay Liew]: http://jayliew.com/
