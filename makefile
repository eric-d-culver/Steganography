#makefile for Steganography project

# compiler/interpreters
CC=gcc
PYTHON=python
CYTHON=cython
# flags
WARNINGS = -Wall
CFLAGS= -std=c11 # $(WARNINGS)

# executable python files
PYMAIN = ngramCount.py huffman.py mimicHuff.py

# helping python modules
PYHELP = pyngram.py tree.py bitFile.py

# stand alone executables
NODEPS = ensteg desteg deal shuffle

# names of produced executables
EXECS = ensteg desteg deal shuffle ngramCount huffman mimicHuff

# additional helping variables
CYMAIN = $(PYMAIN:.py=.c)
CYHELP = $(PYHELP:.py=.c)
CYTHONOBJS = $(CYMAIN:.c=.o) $(CYHELP:.c=.o)
PYINCLUDES = $(shell $(PYTHON)-config --include)
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

mimicHuff: mimicHuff.o bitFile.o
	$(CC) $(CFLAGS) $(PYLINK) -o $@ $^

.PHONY: cleanup clean all


cleanup:
	rm -f *.o *.pyc $(CYMAIN) $(CYHELP)

clean:
	rm -f *.o *.pyc $(CYMAIN) $(CYHELP) $(EXECS)
