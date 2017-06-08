#makefile for Steganography project

# compiler/interpreters
CC=gcc
PYTHON=python2.7
CYTHON=cython
# flags
WARNINGS = -Wall
CFLAGS= -std=c11 # $(WARNINGS)

# executable python files
PYMAIN = ngramCount.py huffman.py mimicNgram.py demimicNgram.py

# helping python modules
PYHELP = pyngram.py tree.py #bitFile.py

# stand alone executables
NODEPS = ensteg desteg deal shuffle

# names of produced executables
EXECS = ensteg desteg deal shuffle ngramCount huffman mimicNgram demimicNgram

# additional helping variables
CYMAIN = $(PYMAIN:.py=.c)
CYHELP = $(PYHELP:.py=.c)
CYTHONOBJS = $(CYMAIN:.c=.o) $(CYHELP:.c=.o)
PYINCLUDES = $(shell $(PYTHON)-config --includes)
PYLINK = -l$(PYTHON)

all: $(EXECS)


$(CYMAIN): %.c: %.py
	$(CYTHON) --embed -o $@ $<

$(CYHELP): %.c: %.py
	$(CYTHON) -o $@ $<

$(CYTHONOBJS): %.o: %.c
	$(CC) $(CFLAGS) $(PYINCLUDES) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NODEPS): %: %.o
	$(CC) $(CFLAGS) -o $@ $<

ngramCount: ngramCount.o pyngram.o
	$(CC) $(CFLAGS) $(PYLINK) -o $@ $^

huffman: huffman.o tree.o
	$(CC) $(CFLAGS) $(PYLINK) -o $@ $^

mimicNgram: mimicNgram.o bitFile.o
	$(CC) $(CFLAGS) $(PYLINK) -o $@ $^

demimicNgram: demimicNgram.o bitFile.o
	$(CC) $(CFLAGS) $(PYLINK) -o $@ $^

output.txt: ensteg desteg deal shuffle input.txt input.ppm
	./deal input.txt 3
	./ensteg input.ppm input0.txt output0.ppm
	./ensteg input.ppm input1.txt output1.ppm
	./ensteg input.ppm input2.txt output2.ppm
	./desteg output0.ppm output0.txt
	./desteg output1.ppm output1.txt
	./desteg output2.ppm output2.txt
	./shuffle output0.txt output1.txt output2.txt

ngrams10.txt: ngramCount shakespeare.txt
	echo "counting ngrams..."
	./ngramCount -i shakespeare.txt 10 > ngrams10.txt
	echo "done."

huffman10.txt: huffman ngrams10.txt
	echo "huffmaning..."
	./huffman ngrams10.txt > huffman10.txt
	echo "done." 

play10.txt: mimicNgram huffman10.txt input.txt
	echo "mimicking ngrams..."
	./mimicNgram input.txt huffman10.txt "Then die " > play10.txt
	echo "done."

deplay10.txt: demimicNgram huffman10.txt play10.txt
	echo "demimicking..."
	./demimicNgram play10.txt huffman10.txt > deplay.txt
	echo "done."

.PHONY: testrun test3 cleanup cleanupMiddles cleanupEnds clean all
	

testrun: output.txt deplay.txt
	

cleanup:
	rm -f *.o *.pyc $(CYMAIN) $(CYHELP)

cleanupMiddles:
	rm -f input?.txt output?.txt ngrams10.txt huffman10.txt

cleanupEnds:
	rm -f output?.ppm output.txt play10.txt deplay10.txt

clean:
	rm -f *.o *.pyc $(CYMAIN) $(CYHELP) $(EXECS)
