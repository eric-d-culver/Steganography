/* ensteg.c
** do steganography stuff
** note that this assumes a binary-type pnm (P4,P5,P6) without a comment field
**
** usage:
**   steg image.pnm file.dat output.pnm
** enstegs the file in file.dat into image.pnm to form output.pnm.  Assumes
** that the destegged file can have trailing garbage without a problem
** (.tar.gz is fine).
*/

#include <stdio.h>
#include <limits.h>

unsigned long hash(char *str);

int main(int argc, char *argv[])
{
	FILE *fp1 = fopen(argv[1], "r");
	FILE *fp2 = fopen(argv[2], "r");
	FILE *fout = fopen(argv[3], "w");
	int w, h, max;
	char buf, copybuf[1024];

	fscanf(fp1, "%1024s", copybuf);
	fscanf(fp1, "%d%d%d\n", &w, &h, &max);
	fprintf(fout, "%s\n%d %d\n%d\n", copybuf, w, h, max);

	/* ensteg the data */
	printf ("enstegging...\n");
	while (fread(&buf, sizeof(char), 1, fp2))
	{
		int i;

		for (i = 0; i < CHAR_BIT; i++)
			{
			char b = fgetc(fp1);
			char s = (b&0xFE) | ((buf>>i)&1);
			fwrite(&s, sizeof(char), 1, fout);
			}
	}

	/* copy the remainder of the file (random-pad everything though) */
	printf ("copying rest/adding garbage...\n");
	srand(time(0)+hash(argv[2]));
	while ((max = fread(copybuf, sizeof(char), 1024, fp1)))
	{
		int i;

		for (i = 0; i < 1024; i++)
			copybuf[i] &= (0xFE | (rand()>>3));
		fwrite(copybuf, sizeof(char), max, fout);
	}

	printf ("done\n");

	/* clean up, such as it is */
	fclose (fp1);
	fclose (fp2);
	fclose (fout);

	return 0;
}

/* this is just to make the random garbage a little more random */
unsigned long hash (char *str) {
	unsigned long hash= 5381;
	int c;
	while (c=*str++)
		hash=((hash<<5)+hash)+c;

	return hash;
}
