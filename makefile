#makefile for Steganography project
CC=gcc
WARNINGS = -Wall
CFLAGS= -std=c11 # $(WARNINGS)
PYMAIN = ngramCount.py huffman.py mimicHuff.py
PYHELP = pyngram.py tree.py bitFile.py
CYMAIN = $(PYMAIN:.py=.c)
CYHELP = $(PYHELP:.py=.c)
CYTHONOBJS = $(CYMAIN:.c=.o) $(CYHELP:.c=.o)
PYINCLUDES = $(shell python-config --include)
PYLINK = -lpython2.7
NODEPS = ensteg desteg deal shuffle
EXECS = ensteg desteg deal shuffle ngramCount huffman mimicHuff

all: $(EXECS)


$(CYMAIN): %.c: %.py
	cython --embed -o $@ $<

$(CYHELP): %.c: %.py
	cython -o $@ $<

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
	rm -f *.o *.pyc $(CYTHON)

clean:
	rm -f *.o *.pyc $(CYTHON) $(EXECS)
