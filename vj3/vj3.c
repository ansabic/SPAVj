#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//
// Created by antonio on 14. 11. 2021..
//
int* generiraj(int n) {
    int* niz = (int*)malloc(sizeof(int) * n);
    niz[0] = rand() % 5;
    for (int i = 1; i < n; i++) {
        niz[i] = niz[i - 1] + 1 + rand() % 5;
    }
    return niz;
}

void shuffle(int *niz, int n) {
    for (int i = 0; i < n; i++) {
        int j = (rand()) % n;
        int tmp = niz[i];
        niz[i] = niz[j];
        niz[j] = tmp;
    }
}

int* presjek(const int* a, const int* b, int n, FILE* file) {
    long start = clock()/CLOCKS_PER_SEC;
    int* result = malloc(sizeof (int) * n);
    int counter = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(a[i] == b[j]){
                result[counter] = a[i];
                counter++;
                break;
            }
        }
    }
    result = realloc(result, sizeof(int) * counter);
    long time = clock()/CLOCKS_PER_SEC - start;
    fprintf(file,"presjek,%d,%ld\n",n,time);
    printf("Gotov obican presjek sa %d clanova. Vrijeme izvrsavanja je %ld.\n",n,time);
    return result;
}

int cmp(const void* a, const void* b) {
    return *((int*)a) == *((int*)b);
}
int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int* presjek_jedan_sortiran(const int* a, int* b, int n, FILE* file) {
    long start = clock()/CLOCKS_PER_SEC;
    qsort(b,n,sizeof (int),cmpfunc);
    int* result = malloc(sizeof (int) * n);
    int counter = 0;
    for(int i = 0; i < n; i++) {
        int* tempResult = (int*) bsearch(&a[i], b, n, sizeof(int), cmp);
        if(tempResult != NULL) {
            result[counter] = *tempResult;
            counter++;
        }
    }
    result = realloc(result, sizeof(int) * counter);
    long time = clock()/CLOCKS_PER_SEC - start;
    fprintf(file,"presjek jedan sortiran,%d,%ld\n",n,time);
    printf("Gotov presjek sa jednim sortiranim nizom od %d clanova. Vrijeme izvrsavanja je %ld.\n",n,time);
    return result;
}

int* presjek_oba_sortirana(int* a, int* b, int n, FILE* file) {
    long start = clock()/CLOCKS_PER_SEC;
    qsort(b,n,sizeof (int),cmpfunc);
    qsort(a,n,sizeof (int),cmpfunc);
    int* result = malloc(sizeof (int) * n);
    int counter = 0;
    int i = 0;
    int j= 0;
    while(i < n) {
        if(a[i] == b[j]) {
            result[counter] = b[j];
            i++;
            continue;
        }
        else if(a[i] > b[j]) {
            j++;
            continue;
        }
        i++;
    }
    result = realloc(result, sizeof(int) * counter);
    long time = clock()/CLOCKS_PER_SEC - start;
    fprintf(file,"presjek oba sortirana,%d,%ld\n",n,time);
    printf("Gotov presjek sa oba sortirana niza od %d clanova. Vrijeme izvrsavanja je %ld.\n",n,time);
    return result;
}


int main() {
    int step = 300000;
    int start = 100000;
    int max = 3000000;
    FILE* file = fopen("/home/antonio/Downloads/data.csv","wt");
    fprintf(file,"\"algoritam\",\"N\",\"vrijeme\"\n");
    for(int j = 0; j < 3; j++) {
        switch (j) {
            case 0: {
                for(int i = start; i < max; i+= step) {
                    int* niz1 = generiraj(i);
                    int* niz2 = generiraj(i);
                    shuffle(niz1,i);
                    shuffle(niz2, i);
                    presjek(niz1, niz2, i, file);
                }
            }
            break;
            case 1: {
                for(int i = start; i < max; i+= step) {
                    int* niz1 = generiraj(i);
                    shuffle(niz1,i);
                    int* niz2 = generiraj(i);
                    presjek_jedan_sortiran(niz1, niz2, i, file);
                }
            }
            break;
            case 2: {
                for(int i = start; i < max; i+= step) {
                    int* niz1 = generiraj(i);
                    shuffle(niz1,i);
                    int* niz2 = generiraj(i);
                    shuffle(niz2,i);
                    presjek_oba_sortirana(niz1, niz2, i, file);
                }
            }
            break;
            default: {
                printf("Error!");
            }
        }
    }
    fclose(file);
    printf("Sve uspjesno!");
}
