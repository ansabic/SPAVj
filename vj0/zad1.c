#include<stdio.h>

int mystrlen(char* string) {
	int counter = 0;
	while (string[counter] != '\0') {
		counter++;
	}
	return counter;
}

main01() {
	char string[20];
	printf("Unesi string: \n");
	scanf("%s", string);
	int counter = mystrlen(string);
	printf("Velicina stringa je %d", counter);
	return 0;
}
