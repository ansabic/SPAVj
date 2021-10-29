#include<stdio.h>

void reverse(char* prvi, char* drugi) {
	int size = 0;
	while (prvi[size] != '\0') {
		size++;
	}
	int sizeSecond = 0;
	while (drugi[sizeSecond] != '\0') {
		sizeSecond++;
	}
	for (int i = 0; i < size; i++) {
		drugi[sizeSecond + i] = prvi[size - 1 - i];
	}
	drugi[sizeSecond + size] = '\0';
}

int main06() {
	char prvi[20];
	char drugi[20];
	printf("Unesi prvi string: \n");
	scanf("%s", prvi);
	printf("Unesi drugi string: \n");
	scanf("%s", drugi);
	reverse(prvi, drugi);
	printf("Drugi string je %s", drugi);
}
