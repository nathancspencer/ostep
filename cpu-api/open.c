#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int x = 100;
	int rc = fork();
	if (rc < 0) {
		exit(1);
	} else if (rc == 0) {
		printf("Child X initial: %d\n", x);
		x = 10;
		printf("Child X: %d\n", x);
	} else {
		x = 1000;
		printf("Parent X: %d\n", x);
	}
}
