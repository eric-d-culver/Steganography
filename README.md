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
- ngramCount.py
- huffman.py
- mimicNgram.py
- demimicNgram.py
- pyngram.py
- tree.py
- bitFile.py
- huffFileRead.py
- makefile

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

**ngramCount.py**
- python ngramCount.py -i filename n > ngramfile  
- ngramCount -i filename n > ngramfile  
Counts the ngrams in input file and outputs "Ngrams" followed by the value of n, followed by all the ngrams in the input file, a space, and their frequency, ordered with highest frequency first.  Replaces newlines with the padding character U+80 to ease reading of output file.  The output of this can be used as the input for huffman.py.  
Uses Python module pyngram (included).  

**huffman.py**
- python huffman.py ngramfile > huffmanfile
- huffman ngramfile > huffmanfile  
Groups the ngrams by the first n-1 characters, then constructs Huffman codes for them.  Outputs "Huffman" then the value of n, then the prefix, followed by an indented list of the symbols and code lengths, for all the prefixes in the ngram file. Reads padding character U+80 as a newline, and outputs U+80 to mean a newline for ease of reading the output file.

**mimicNgram.py**
- python mimicNgram.py inputfile huffmanfile > outputfile  
- mimicNgram inputfile huffmanfile > outputfile  
Encodes the inputfile into a file mimicking the relative frequencies expressed in the huffmanfile.  Can read inputfile from standard input, outputs to standard output. Simplisically, the inputfile is treated as a Huffman-encoded bitstream and it is decoded using the information in the huffmanfile into the outputfile.  Expanding on that, the huffmanfile contains information about the ngrams of the file being mimicked.  The program starts with a seed of length n-1, and using that as the prefix, determines the next symbol based on the relative frequency of the ngrams starting with that prefix.  The inputfile is used as the 'random' bitstream to determine which symbol to pick.

**demimicNgram.py**  
- python demimicNgram.py inputfile huffmanfile > outputfile  
- demimicNgram inputfile huffmanfile > outputfile  
Decodes the inputfile (which mimickes the frequencies expressed in the huffmanfile) into the outputfile that created it via mimicNgram.  Can read inputfile from standard input, outputs to standard output.  

**pyngram.py**  
Python module used in ngramCount.py. Created by [Jay Liew][pyngram].

**tree.py**  
Python script defining the Node class to make tree creation and manipulation easier in huffman.py

**bitFile.py**  
Python script defining the bitRead class to allow files to be easily read one bit at a time.  Used in mimicNgram.py and demimicNgram.py.

**huffFileRead.py**
Python script defining function for reading Huffman files into memory. Used in mimicNgram.py and demimicNgram.py.

**makefile**  
- make all  
- make <name of program> (ex.: make ngramCount)
- make cleanup
- make clean  
Standard makefile to be used with \*nix make utility.  Requires Python and Cython to make python scripts into executables.  No guarantee it will work on all systems. Will not make helper python modules into stand alone executables. Also includes two useful commands: cleanup and clean.  "make cleanup" will remove all the intermediate files created when making the executables (i.e. object files, the Cython C files, etc.).  "make clean" will remove all the intermediate files and all the executables (useful to force everything to be remade).  
If it does not work the important lines are the three near the top.  CC should be equal to your C compiler.  PYTHON should be your python interpreter with version.  CYTHON should be your cython converter.  If your command line returns an error saying they don't exist, you may need to put in the entire directory path.  

## Acknowledgements
The code in ensteg.c and desteg.c is based off of code by [Joshua Shagam][ensteg].  
Python module pyngram created by [Jay Liew][pyngram].  

<!-- Links -->
[ensteg]: <http://www.cs.nmsu.edu/~joshagam/css/>
[pyngram]: <http://jayliew.com/>
