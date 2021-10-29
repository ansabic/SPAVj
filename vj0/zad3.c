#include<stdio.h>

int mystrcmp(char* prvi, char* drugi) {
	for (int i = 0; prvi[i]!='\0' || drugi[i] != '\0' ;i++) {
        int result = prvi[i] - drugi[i];
        if(result != 0)
            return result;
	}
	return 0;
}

int main() {
	char prvi[20];
	char drugi[20];
	printf("Unesi prvi string: \n");
	scanf("%s", prvi);
	printf("Unesi drugi string: \n");
	scanf("%s", drugi);
	int result = mystrcmp(prvi, drugi);
	printf("%d", result);
}
