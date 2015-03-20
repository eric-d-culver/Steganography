#!/bin/sh
gcc ensteg.c -o ensteg
gcc desteg.c -o desteg
gcc deal.c -o deal
gcc shuffle.c -o shuffle
./deal input.txt 3
./ensteg input.ppm input0.txt output0.ppm
./ensteg input.ppm input1.txt output1.ppm
./ensteg input.ppm input2.txt output2.ppm
./desteg output0.ppm output0.txt
./desteg output1.ppm output1.txt
./desteg output2.ppm output2.txt
./shuffle output0.txt output1.txt output2.txt
