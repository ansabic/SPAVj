#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>
#include "stl.h"
#include "constants.h"


void readHeader(FILE* file) {
    fseek(file,HEADER_SIZE,SEEK_SET);
}
unsigned int readNumberOfTriangles(FILE* file) {
    unsigned int* result = malloc(sizeof (unsigned int));
    fread(result, sizeof(unsigned int),1,file);
    return *result;
}

Trokut *readTrokut(FILE *file, int enableColor) {
    Trokut *trokut = malloc(sizeof(Trokut));
    trokut->tocke = malloc(sizeof (Tocka) * 3);
    Normala *normala = malloc(sizeof(Normala));

    float *normalX = malloc(sizeof (float));
    float *normalY= malloc(sizeof (float));
    float *normalZ= malloc(sizeof (float));
    fread(normalX, sizeof(float), 1, file);
    fread(normalY, sizeof(float), 1, file);
    fread(normalZ, sizeof(float), 1, file);
    normala->x = *normalX;
    normala->y = *normalY;
    normala->z = *normalZ;
    trokut->normala = *normala;

    for(int i = 0; i < 3; i++) {
        Tocka* a = malloc(sizeof (Tocka));
        float* x= malloc(sizeof (float));
        float* y= malloc(sizeof (float));
        float* z= malloc(sizeof (float));
        fread(x,sizeof(float),1,file);
        fread(y,sizeof(float),1, file);
        fread(z,sizeof(float),1, file);
        a->x = *x;
        a->y = *y;
        a->z = *z;
        *(trokut->tocke + i)  = *a;
    }
    if(enableColor) {
        unsigned int* color;
        fread(color,sizeof (unsigned int),1,file);
        trokut->boja = *color;
    }
    return trokut;
}

Objekt3D* readFileBinary(FILE* file) {
    Objekt3D* objekt = malloc(sizeof(Objekt3D));

    readHeader(file);
    objekt->n = readNumberOfTriangles(file);
    objekt->trokuti = malloc(sizeof (Trokut) * objekt->n);
    for(int i = 0; i < objekt->n; i++)
        *(objekt->trokuti + i) = *readTrokut(file,0);
    return objekt;
}
