#include <stdio.h>
#include <stdlib.h>

#define LINE_LENGTH 100

// TODO figure out files

void print_file(char *filename) {
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("cannot open file\n");
		exit(1);
	}

	char buffer[LINE_LENGTH];
	while (1) {
		char *result = fgets(buffer, LINE_LENGTH, fp);
		if (result == NULL) {
			break;
		}
		printf("%s", buffer);
	}

	fclose(fp);
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		exit(0);
	}

	for (int i = 1; i < argc; i++) {
		print_file(argv[i]);
	}

	return(0);
}
