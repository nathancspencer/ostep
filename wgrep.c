#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

int main(int argc, char *argv[]);
void print_file(char *searchterm, char *filename);
void print_stdin(char *searchterm);
int is_contained(char *searchterm, char *line);

int main(int argc, char *argv[]) {
	if (argc == 1) { printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}
	if (argc == 2) {
		print_stdin(argv[1]);
		exit(0);
	}	
	for (int i = 2; i < argc; i++) {
		print_file(argv[1], argv[i]);
	}

	exit(0);
}

void print_file(char *searchterm, char *filename) {
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("wgrep: cannot open file\n");
		exit(1);
	}

	char *buffer;
	size_t bufsize = 32;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if(buffer == NULL) {
		perror("Unable to allocate buffer");
		exit(1);
	}

	ssize_t line_length;
	while((line_length = getline(&buffer, &bufsize, fp)) > 0) {
		if (is_contained(searchterm, buffer)) {
			printf("%s", buffer);
		}
	}	
	fclose(fp);
}

void print_stdin(char *searchterm) {
	char *buffer;
	size_t bufsize = 32;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if(buffer == NULL) {
		perror("Unable to allocate buffer");
		exit(1);
	}

	ssize_t line_length;
	while((line_length = getline(&buffer, &bufsize, stdin)) > 0) {
		if (is_contained(searchterm, buffer)) {
			printf("%s", buffer);
		}
	}	
}

// could use knuth-morris-pratt if I was bothered
int is_contained(char *searchterm, char *line) {
	for(size_t i = 0; i < strlen(line); i++) {
		for (int j = 0; searchterm[j] == line[i + j]; j++) {
			if (j + 1 == strlen(searchterm)) return 1;
		}
	}
	return 0;
}
