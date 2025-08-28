#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

int main(int argc, char *argv[]); 
void zip_files(int argc, char *argv[]);

int main(int argc, char *argv[]) {
	if (argc == 1) { 
		printf("wzip: file1 [file2 ...]\n"); 
		exit(1); 
	} 

	zip_files(argc, argv);

	exit(0); 
}

void zip_files(int argc, char *argv[]) {
	char character, previous_character;
	int count = 1;

	for(int i = 1; i < argc; i++) {
		FILE *fp = fopen(argv[i], "r");
		if (fp == NULL) {
			printf("wzip: cannot open file\n");
			exit(1);
		}

		while (fread(&character, sizeof(char), 1, fp)) {
			if (!previous_character) {
				previous_character = character;
				continue;
			}
			if (character == previous_character) {
				count++;
				continue;
			}

			fwrite(&count, sizeof(int), 1, stdout);
			fwrite(&previous_character, sizeof(char), 1, stdout);

			previous_character = character;
			count = 1;
		}

		fclose(fp);
	}

	fwrite(&count, sizeof(int), 1, stdout);
	fwrite(&character, sizeof(char), 1, stdout);
}
