#include <stdio.h>
#include "stl.h"


void printObjekt(Objekt3D* objekt) {
    for(int i = 0; i < objekt->n; i++) {
        Trokut* trokut = (objekt->trokuti + i);
        Normala normala = objekt->trokuti->normala;
        printf("-----------------------------------------------------------------------\n");
        printf("TROKUT %d: \n",i);
        printf("\t NORMALA:\n");
        printf("\t (%.2f,%.2f,%.2f)\n",objekt->trokuti->normala.x, normala.y, normala.z);
        printf("\t TOCKE:\n");
        printf("\t");
        for(int j = 0; j < 3; j++) {
            Tocka* tocka = trokut->tocke + j;
            printf(" (%.2f,%.2f,%.2f)", tocka->x,tocka->y, tocka->z);
            if(j != 2)
                printf(" ,");
            else
                printf("\n");
        }
        printf("-----------------------------------------------------------------------\n");
    }
}

int main() {
    FILE* file = fopen("/home/antonio/Downloads/primjerbin", "rb");
    Objekt3D* objekt = readFileBinary(file);
    printObjekt(objekt);
}
