#include<stdio.h>
void mystrcopy(char* first, char* second) {
	int counter = 0;
	while (second[counter] != '\0') {
		first[counter] = second[counter];
		counter++;
	}
	first[counter] = '\0';
}


int main02() {
	char prvi[20];
	char drugi[20];
	printf("Unesi prvi string: \n");
	scanf("%s", prvi);
	printf("Unesi drugi string: \n");
	scanf("%s", drugi);
	mystrcopy(prvi, drugi);
	printf("Prvi string je %s \n Drugi string je %s \n", prvi, drugi);
}
