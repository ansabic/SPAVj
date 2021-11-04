#include <stdio.h>
#include <malloc.h>

void saveNumbersToFileBinary(FILE *file, const int *n) {
    fwrite(n, sizeof(int), 1, file);
    printf("Unesi %d brojeva: \n", *n);
    for (int i = 0; i < *n; i++) {
        int tempN;
        scanf("%d", &tempN);
        fwrite(&tempN, sizeof(int), 1, file);
    }
}

int *readNumbersFromBinary(FILE *file, const int *n) {
    int *tempResult = malloc(sizeof(int) * *n + 1);
    fread(tempResult, sizeof(int), 1, file);
    for (int i = 1; i <= *n; i++)
        fread((tempResult + i), sizeof(int), 1, file);
    return tempResult;
}

void printArray(const int *niz) {
    printf("Broj clanova u nizu: %d\n", *niz);
    for (int i = 1; i <= *(niz); i++)
        printf("%d ", *(niz + i));
    printf("\n");
}

typedef struct {
    float x;
    float y;
} Koordinata;

void unesiKoordinate(Koordinata *koordinate, int n) {
    printf("Unesi %d koordinata: (format: x y) \n", n);
    for (int i = 0; i < n; i++) {
        scanf("%f", &((koordinate + i)->x));
        scanf("%f", &((koordinate + i)->y));
    }
}

void writeKoordinateBinary(Koordinata *koordinate, FILE *file, const int *n) {
    fwrite(n, sizeof(int), 1, file);
    for (int i = 0; i < *n; i++)
        fwrite(koordinate + i, sizeof(Koordinata), 1, file);
}

Koordinata *koordinataNaIndeksuBinary(FILE *file, const int index) {
    fseek(file, sizeof(int), SEEK_SET); //preskoci n na pocetku
    fseek(file, index * (sizeof(Koordinata)), SEEK_CUR);
    Koordinata *tempResult = malloc(sizeof(Koordinata));
    fread(tempResult, sizeof(Koordinata), 1, file);
    return tempResult;
}

Koordinata *coordinateFromFile(FILE *file) {
    int *n = malloc(sizeof(int));
    fread(n, sizeof(int), 1, file);
    Koordinata *tempResult = malloc(sizeof(Koordinata) * *n + 1);
    for (int i = 0; i < *n + 1; i++)
        fread(tempResult + i, sizeof(Koordinata), 1, file);
    return tempResult;
}

void ispisiKoordinate(Koordinata *koordinate, int n, int reverse) {
    if (!reverse) {
        for (int i = 0; i < n; i++)
            printf("(%f,%f) ", (koordinate + i)->x, (koordinate + i)->y);
    } else {
        for (int i = n - 1; i >= 0; i--)
            printf("(%f,%f) ", (koordinate + i)->x, (koordinate + i)->y);
    }
    printf("\n");
}

void addToEndCoordinateBinary(Koordinata *koordinata, FILE *file) {
    fwrite(koordinata, sizeof(Koordinata), 1, file);
}

int main() {
    /*int n;
    printf("Unesi kolicinu brojeva za unos: \n");
    scanf("%d",&n);
    FILE* fileWrite = fopen("/home/antonio/Downloads/binaryArray", "wb");
    saveNumbersToFileBinary(fileWrite,&n);
    fclose(fileWrite);
    FILE* file = fopen("/home/antonio/Downloads/binaryArray", "rb");
    int* result = readNumbersFromBinary(file,&n);
    printArray(result);
    fclose(file);*/

    int n;
    int index;
    printf("Unesi kolicinu koordinata za unos: \n");
    scanf("%d", &n);
    Koordinata *koordinata = malloc(sizeof(Koordinata) * n);
    unesiKoordinate(koordinata, n);
    FILE *file = fopen("/home/antonio/Downloads/binaryKoordinate", "wb");
    writeKoordinateBinary(koordinata, file, &n);
    fclose(file);
    printf("Unesi zeljeni indeks od 0 do %d: \n", n - 1);
    scanf("%d", &index);
    FILE *fileRead = fopen("/home/antonio/Downloads/binaryKoordinate", "rb");
    Koordinata *rjesenje = koordinataNaIndeksuBinary(fileRead, index);
    ispisiKoordinate(rjesenje, 1, 0);
    fclose(fileRead);
    Koordinata *tempCoordinate = malloc(sizeof(Koordinata));
    printf("Unesi tocku: \n");
    scanf("%f %f", &(tempCoordinate->x), &(tempCoordinate->y));
    FILE *fileWrite = fopen("/home/antonio/Downloads/binaryKoordinate", "a");
    addToEndCoordinateBinary(tempCoordinate, fileWrite);
    fclose(fileWrite);
    FILE *fileReadAgain = fopen("/home/antonio/Downloads/binaryKoordinate", "rb");
    Koordinata *tempResult = coordinateFromFile(fileReadAgain);
    fclose(fileReadAgain);
    ispisiKoordinate(tempResult, n + 1, 1);
}
