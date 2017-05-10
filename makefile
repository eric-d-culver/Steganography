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

.PHONY: cleanup cleanupMiddles cleanupEnds clean all


cleanup:
	rm -f *.o *.pyc $(CYMAIN) $(CYHELP)

cleanupMiddles:
	rm -f input?.txt output?.txt ngrams10.txt huffman10.txt

cleanupEnds:
	rm -f output?.ppm output.txt play10.txt deplay10.txt

clean:
	rm -f *.o *.pyc $(CYMAIN) $(CYHELP) $(EXECS)
