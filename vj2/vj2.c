#include <stdio.h>
#include <malloc.h>
#include "stl.h"


void printObjekt(Objekt3D *objekt) {
    for (int i = 0; i < objekt->n; i++) {
        Trokut *trokut = (objekt->trokuti + i);
        Normala normala = objekt->trokuti->normala;
        printf("-----------------------------------------------------------------------\n");
        printf("TROKUT %d: \n", i);
        printf("\t NORMALA:\n");
        printf("\t (%.2f,%.2f,%.2f)\n", objekt->trokuti->normala.x, normala.y, normala.z);
        printf("\t TOCKE:\n");
        printf("\t");
        for (int j = 0; j < 3; j++) {
            Tocka *tocka = trokut->tocke + j;
            printf(" (%.2f,%.2f,%.2f)", tocka->x, tocka->y, tocka->z);
            if (j != 2)
                printf(" ,");
            else
                printf("\n");
        }
        if ((void *) (size_t) trokut->boja != NULL)
            printf("\t BOJA:\t%d\n", trokut->boja);

        printf("-----------------------------------------------------------------------\n");
    }
}

int main() {
    //FILE *file = fopen("/home/antonio/Downloads/primjertxt", "rt");
    //Objekt3D objekt = readFileText(file);
    //FILE* writeFile = fopen("/home/antonio/Downloads/myStl", "wb");
    //writeFileBinary(writeFile,objekt);
    FILE* readFile = fopen("/home/antonio/Downloads/primjerbin.stl", "rb");
    Objekt3D resultObjekt = readFileBinary(readFile);
    fclose(readFile);
    printObjekt(&resultObjekt);
    //FILE* writeText = fopen("/home/antonio/Downloads/readTest.stl", "wt");
    //writeFileText(writeText,"readTest",objekt);
}
