#include<stdio.h>

void mystrcat(char* prvi, char* drugi) {
	int firstCounter = 0;
	while (prvi[firstCounter] != '\0') {
		firstCounter++;
	}
	int secondCounter = 0;
	while (drugi[secondCounter] != '\0') {
		prvi[firstCounter + secondCounter] = drugi[secondCounter];
		secondCounter++;
	}
	prvi[firstCounter + secondCounter] = '\0';
}

int main04() {
	char prvi[20];
	char drugi[20];
	printf("Unesi prvi string: \n");
	scanf("%s", prvi);
	printf("Unesi drugi string: \n");
	scanf("%s", drugi);
	mystrcat(prvi, drugi);
	printf("Zajednicki string je: %s", prvi);
}
