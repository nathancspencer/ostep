#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

int main(int argc, char *argv[]); 
void unzip_files(int argc, char *argv[]);

int main(int argc, char *argv[]) {
	if (argc == 1) { 
		printf("wunzip: file1 [file2 ...]\n"); 
		exit(1); 
	} 

	unzip_files(argc, argv);

	exit(0); 
}

void unzip_files(int argc, char *argv[]) {
	char character;
	int count;

	for(int i = 1; i < argc; i++) {
		FILE *fp = fopen(argv[i], "r");
		if (fp == NULL) {
			printf("wunzip: cannot open file\n");
			exit(1);
		}

		while (fread(&count, sizeof(int), 1, fp), fread(&character, sizeof(char), 1, fp)) {
			for (int i = 0; i < count; i++) {
				fwrite(&character, sizeof(char), 1, stdout);
			}
		}

		fclose(fp);
	}
}
