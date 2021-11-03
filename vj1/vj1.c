#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void unesiNiz(int* a, int* n) {
    printf("Unesi velicinu niza: \n");
    scanf("%d", n);
    printf("Unesi niz: \n");
    for(int i = 0; i < *n; i++)
        scanf("%d", &a[i]);
}

void unesiNizFloat(float* a, int* n) {
    printf("Unesi velicinu niza: \n");
    scanf("%d", n);
    printf("Unesi niz: \n");
    for(int i = 0; i < *n; i++)
        scanf("%f", &a[i]);
}

void unesiDvaNiza(int* a, int* b, int* n, int* m) {
    printf("Unesi velicinu prvog niza: \n");
    scanf("%d", n);
    printf("Unesi niz: \n");
    for(int i = 0; i < *n; i++)
        scanf("%d", &a[i]);
    printf("Unesi velicinu drugog niza: \n");
    scanf("%d", m);
    printf("Unesi niz: \n");
    for(int i = 0; i < *m; i++)
        scanf("%d", &b[i]);
}

void unesiRaspon(int* pocetak, int* kraj) {
    printf("Odaberi pocetak: \n");
    scanf("%d",pocetak);
    printf("Odaberi kraj: \n");
    scanf("%d",kraj);
}
void printNiz(float* niz, int n) {
    for(int i = 0; i<n; i++) {
        printf("%f ",niz[i]);
    }
}
void printPointersStartValues(int** a, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d \n",*a[i]);
    }
}
int* podniz(int *niz,int start, int stop) {
    int* a = malloc(sizeof(int*));
    for(int i = 0; i <= stop - start; i++) {
        a[i] = niz[start + i];
    }
    return a;
}

int* filtriraj(int *niz, int n, int th, int *nth) {
    int* rez = malloc(sizeof(niz));
    int* counter = malloc(sizeof(int));
    for(int i =0; i < n; i++) {
        if(niz[i]< th) {
                rez[*counter] = niz[i];
                *counter = *counter + 1;
        }
    }
    *nth = *counter;
    return rez;
}

int** podijeli(int *niz, int n) {
    int** rez = malloc(sizeof(int**) * 2);
    int half = n/2;
    for(int i = 0; i< 2; i++) {
        int* tempRez = malloc(sizeof(int*));
        tempRez = niz;
        rez[i] = tempRez;
        niz +=half;
    }
    return rez;
}

typedef struct  {
    float x;
    float y;
} Tocka;

typedef struct  {
    Tocka* vrhovi;
    int n;
} Poligon;

void printPoligon(Poligon* poligon) {
    for(int i= 0; i< poligon->n; i++) {
        printf("(%.2f , %.2f)\n",poligon->vrhovi[i].x,poligon->vrhovi[i].y);
    }
}

Poligon* novi_poligon(const float *niz_x, const float *niz_y, int n) {
    if(n >= 3) {
        Poligon* rez =  malloc(sizeof(Poligon));
        rez->vrhovi = malloc(n * sizeof(Tocka));
        rez->n = n;
        for(int i =0; i < n; i++) {
            Tocka tempTocka;
            tempTocka.x = *(niz_x + i);
            tempTocka.y = *(niz_y + i);
            rez->vrhovi[i] = tempTocka;
        }
        return rez;
    }
    else
        return NULL;
}

Tocka** pozitivni(Poligon *p, int *np) {
    Tocka **tempResult = malloc( p->n * sizeof(struct Tocka*));
    int br = 0;
    for (int i = 0; i < p->n; i++) {
        *(tempResult + i) = malloc(sizeof(Tocka));
        if (p->vrhovi[i].x >= 0 && p->vrhovi[i].y >= 0) {
            *tempResult[br] = *(p->vrhovi + i);
            br++;
        }
    }
    *np = br;
    return tempResult;
}


int main111() {
    int a[20];
    int b[20];

    float c[20];
    float d[20];

    int* n = malloc(sizeof(int));
    int* m = malloc(sizeof(int));

    int pocetak;
    int kraj;

    int* nth = malloc(sizeof(int*));
    unesiNizFloat(c, n);
    unesiNizFloat(d, m);

    //unesiRaspon(&pocetak, &kraj);
    //int** temp = podijeli(a,n);
    //printPointersStartValues(temp,2);
    Poligon* poligon = novi_poligon(c,d,*n) ;
    //printPoligon(poligon);
    int * size  = malloc(sizeof(int));
    size[0] = 1;

    Tocka** rez = pozitivni(poligon,size);
    for (int i = 0; i < *size; i++) {
        printf("(%f,%f)", rez[i]->x, rez[i]->y);
    }

}
