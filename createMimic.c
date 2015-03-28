#include <limits.h>
#include <string.h>

int main(int argc, char* argv[]) {
	FILE *fin=fopen(argv[1], "r");
	int n=atoi(argv[2]);
	FILE *fout=fopen(argv[3], "w");

	char *window=(char *)malloc((n-1)*sizeof(char));
	char buffer;
	char *ngram=(char *)malloc((n-1)*sizeof(char));

	int freqs[1<<CHAR_BIT];

	fread(window, sizeof(char), n-1, fin);

	while(fread(buffer, sizeof(char), 1, fin)==1) {
		if (memcmp(window, ngram, n-1)) {
			++freqs[buffer];
		}
		for (int i=0; i<(n-2); ++i) {
			window[i]=window[i+1];
		}
		window[n-1]=buffer;
	}
	

	return 0;
}
