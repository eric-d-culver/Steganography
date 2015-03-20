/* shuffle.c
** used to recombine files seperated with deal.c
** into one file
** usage:
**    ./shuffle file0 file1 ...
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char *basename;
	char extension[5];
	basename=(char *)malloc(sizeof(char)*strlen(argv[1]));

	char *dot=strchr(argv[1], '.');
	strcpy(extension, dot);
	--dot;
	while ((dot!=argv[1])&&(atoi(dot)!=0)) {
		--dot;
	}
	memcpy(basename, argv[1], dot-argv[1]);
	strcat(basename, extension);

	FILE * fp=fopen(basename, "w");
	FILE ** fparray=(FILE **)malloc(sizeof(FILE *)*argc);

	free(basename);

	int i;
	int piles=argc-1;
	for (i=0; i<piles; ++i) {
		fparray[i]=fopen(argv[i+1], "r");
	}

	printf("shuffling...\n");
	char *bytes;
	bytes=(char *)malloc(sizeof(char)*piles);
	int read=1;

	while (read) {
		for (i=0; i<piles; ++i) {
			read&=fread(&(bytes[i]), sizeof(char), 1, fparray[i]);
		}
		fwrite(bytes, sizeof(char), piles, fp);
	}
	printf("done\n");


	fclose(fp);
	for (i=0; i<piles; ++i) {
		fclose(fparray[i]);
	}
	free(fparray);
	free(bytes);

	return 0;
}
