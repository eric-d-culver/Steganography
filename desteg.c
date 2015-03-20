/* desteg.c
** find steganography stuff
** note that this assumes a binary-type pnm (P4,P5,P6) without a comment field
**
** usage:
** 	desteg input.pnm file.dat 
** destegs info from image and puts in file.dat.  Assumes that the desteged file can have trailing garbage no problem
*/

#include <stdio.h>

int main (int argc, char *argv[]) {
	FILE *fp1 = fopen(argv[1], "r");
	FILE *fp2 = fopen(argv[2], "w");
	char copybuf[1024];

	fgets(copybuf, 1023, fp1);
	fgets(copybuf, 1023, fp1);
	fgets(copybuf, 1023, fp1);

	//desteg data
	printf("destegging...\n");
	while (fread(copybuf, sizeof(char), 8, fp1)) {
		int i;
		char s=0;
		for (i=0; i<8; ++i) {
			s|=((copybuf[i]&1)<<i);
		}
		fputc(s, fp2);
	}
	printf("done\n");

	fclose (fp1);
	fclose (fp2);

	return 0;
}
