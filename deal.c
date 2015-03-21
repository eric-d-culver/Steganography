/* deal.c
** use to divide a file among several files
** usage:
**    ./deal <filename> splitNum
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int piles=atoi(argv[2]); 
	FILE * fp=fopen(argv[1], "r");
	FILE ** fparray= (FILE **)malloc(sizeof(FILE *)*piles);

	/* all this just to get the right filenames */
	char extension[5];
	char *basename;

	char *dot=strchr(argv[1], '.');
	basename=(char *)malloc(sizeof(char)*(dot-argv[1]));
	strcpy(extension, dot);
	memcpy(basename, argv[1], dot-argv[1]);

	char *filename, *num;
	filename=(char *)malloc(sizeof(char)*(strlen(argv[1])+4));
	num=(char *)malloc(sizeof(char)*4);
	int i;
	for (i=0; i<piles; ++i) {
		strcpy(filename, basename);
		sprintf(num, "%d", i);
		strcat(filename, num);
		strcat(filename, extension);
		fparray[i]=fopen(filename, "w");
	}

	free(basename);
	free(filename);
	free(num);

	/* now "deal" out the bytes */
	printf("dealing...\n");
	char *bytes;
	bytes=(char *)malloc(sizeof(char)*piles);

	while (fread(bytes, sizeof(char), piles, fp)) {
		for (i=0; i<piles; ++i) {
			fwrite(&(bytes[i]), sizeof(char), 1, fparray[i]);
		}
	}
	printf("done\n");

	/* clean up */
	free(bytes);
	fclose(fp);
	for (i=0; i<piles; ++i) {
		fclose(fparray[i]);
	}
	free(fparray);

	return 0;
}
