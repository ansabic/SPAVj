#include<stdio.h>
#include<string.h>

char* mystrstr(char* prvi, char* drugi) {
	int mainCounter = 0;
	while (prvi[mainCounter] != '\0') {
		int secondCounter = 0;
		while (prvi[mainCounter + secondCounter] == drugi[secondCounter] && prvi[mainCounter + secondCounter] != '\0') {
			secondCounter++;
            if(drugi[secondCounter] == '\0')
                return prvi + mainCounter;
		}
		mainCounter++;
	}
	return NULL;
}

int main05() {
	char prvi[20];
	char drugi[20];
	printf("Unesi prvi string: \n");
	scanf("%s", prvi);
	printf("Unesi drugi string: \n");
	scanf("%s", drugi);
	char* a = mystrstr(prvi, drugi);
    int i = 0;
	while(a[i] != '\0') {
        printf("%c", a[i]);
        i++;
    }
}
