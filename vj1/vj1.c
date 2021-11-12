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
int* podniz(const int *niz,int start, int stop) {
    int* a = malloc(sizeof(int) * (start - stop + 1));
    for(int i = 0; i <= stop - start; i++) {
        a[i] = niz[start + i];
    }
    return a;
}

int* filtriraj(const int *niz, int n, int th, int *nth) {
    int* rez = malloc(sizeof(int) * n);
    int counter = 0;
    for(int i =0; i < n; i++) {
        if(niz[i]< th) {
                rez[counter] = niz[i];
                counter++;
        }
    }
    rez = realloc(rez,sizeof (int) * counter);
    *nth = counter;
    return rez;
}

int** podijeli(const int *niz, int n) {
    int** rez = malloc(sizeof(int*) * 2);
    int firstHalf = n/2;
    int secondHalf = n - n/2;
    int* prvi = malloc(sizeof (int) * firstHalf);
    int* drugi = malloc(sizeof (int) * secondHalf);
    for(int i = 0; i < n; i++) {
        if(i < firstHalf)
            *(prvi + i) = niz[i];
        else
            *(drugi + i - firstHalf) = niz[i];
    }
    *(rez) = prvi;
    *(rez + 1) = drugi;
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
            rez->vrhovi[i].x =*(niz_x + i);
            rez->vrhovi[i].y = *(niz_y + i);
        }
        return rez;
    }
    else
        return NULL;
}

Tocka** pozitivni(Poligon *p, int *np) {
    Tocka **tempResult = malloc( p->n * sizeof(Tocka*));
    int br = 0;
    for (int i = 0; i < p->n; i++) {
        if (p->vrhovi[i].x >= 0 && p->vrhovi[i].y >= 0) {
            tempResult[br] = (p->vrhovi + i);
            br++;
        }
    }
    *np = br;
    return tempResult;
}


int main1() {
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
