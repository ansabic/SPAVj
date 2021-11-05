#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>
#include "stl.h"
#include "constants.h"
#include <string.h>


void readHeader(FILE *file) {
    fseek(file, HEADER_SIZE, SEEK_SET);
}

unsigned int readNumberOfTriangles(FILE *file) {
    unsigned int *result = malloc(sizeof(unsigned int));
    fread(result, sizeof(unsigned int), 1, file);
    return *result;
}

Trokut *readTrokut(FILE *file, int enableColor) {
    Trokut *trokut = malloc(sizeof(Trokut));
    trokut->tocke = malloc(sizeof(Tocka) * 3);
    Normala *normala = malloc(sizeof(Normala));

    float *normalX = malloc(sizeof(float));
    float *normalY = malloc(sizeof(float));
    float *normalZ = malloc(sizeof(float));
    fread(normalX, sizeof(float), 1, file);
    fread(normalY, sizeof(float), 1, file);
    fread(normalZ, sizeof(float), 1, file);
    normala->x = *normalX;
    normala->y = *normalY;
    normala->z = *normalZ;
    trokut->normala = *normala;

    for (int i = 0; i < 3; i++) {
        Tocka *a = malloc(sizeof(Tocka));
        float *x = malloc(sizeof(float));
        float *y = malloc(sizeof(float));
        float *z = malloc(sizeof(float));
        fread(x, sizeof(float), 1, file);
        fread(y, sizeof(float), 1, file);
        fread(z, sizeof(float), 1, file);
        a->x = *x;
        a->y = *y;
        a->z = *z;
        *(trokut->tocke + i) = *a;
    }
    if (enableColor) {
        unsigned int *color = malloc(sizeof(unsigned int));
        fread(color, sizeof(unsigned int), 1, file);
        trokut->boja = *color;
    }
    return trokut;
}

Objekt3D *readFileBinary(FILE *file) {
    Objekt3D *objekt = malloc(sizeof(Objekt3D));

    readHeader(file);
    objekt->n = readNumberOfTriangles(file);
    objekt->trokuti = malloc(sizeof(Trokut) * objekt->n);
    for (int i = 0; i < objekt->n; i++)
        *(objekt->trokuti + i) = *readTrokut(file, 1);
    return objekt;
}

void emptyHeaderWriteBinary(FILE *file) {
    fseek(file, HEADER_SIZE, SEEK_SET);
}

void writeSizeBinary(FILE *file, Objekt3D *objekt3D) {
    unsigned int n = objekt3D->n;
    fwrite(&n, sizeof(unsigned int), 1, file);
}

void writeTriangleBinary(FILE *file, Objekt3D *objekt3D) {
    for (int i = 0; i < objekt3D->n; i++) {
        Trokut *trokut = objekt3D->trokuti + i;
        Normala normala = trokut->normala;
        fwrite(&normala.x, sizeof(float), 1, file);
        fwrite(&normala.y, sizeof(float), 1, file);
        fwrite(&normala.z, sizeof(float), 1, file);

        for (int j = 0; j < 3; j++) {
            Tocka *tocka = trokut->tocke + j;
            fwrite(&tocka->x, sizeof(float), 1, file);
            fwrite(&tocka->y, sizeof(float), 1, file);
            fwrite(&tocka->z, sizeof(float), 1, file);
        }
        if ((void *) (size_t) trokut->boja != NULL) {
            unsigned short boja = trokut->boja;
            fwrite(&boja, sizeof(unsigned short), 1, file);
        } else {
            unsigned short boja = 0;
            fwrite(&boja, sizeof(unsigned short), 1, file);

        }
    }
}

void writeFileBinary(FILE *file, Objekt3D *objekt3D) {
    emptyHeaderWriteBinary(file);
    writeSizeBinary(file, objekt3D);
    writeTriangleBinary(file, objekt3D);
}

void writeFileText(FILE *file, char *fileName, Objekt3D *objekt3D) {
    fprintf(file, "%s %s\n", SOLID, fileName);
    for (int i = 0; i < objekt3D->n; i++) {
        Normala normala = objekt3D->trokuti->normala;
        Trokut *trokut = objekt3D->trokuti + i;
        fprintf(file, "  %s %.5f %.5f %.5f\n", NORMAL, normala.x, normala.y, normala.z);
        fprintf(file, "    %s\n", START);
        for (int j = 0; j < 3; j++) {
            Tocka *tocka = trokut->tocke + j;
            fprintf(file, "      %s %.5f %.5f %.5f\n", VERTEX, tocka->x, tocka->y, tocka->z);
        }
        fprintf(file, "    %s\n", END);
        fprintf(file, "  %s\n", NORMAL_END);
    }
    fprintf(file, "%s %s\n", SOLID_END, fileName);
}

int prefix(const char *pre, const char *str) {
    return strncmp(pre, str, strlen(pre)) == 0;
}

char *skipLine(FILE *file) {
    char *tempString = malloc(sizeof(char) * 50);
    return fgets(tempString, 99, file);
}

char *skipForLength(int stage, const char *string, FILE *file) {
    char *tempString = malloc(sizeof(char) * 50);
    return fgets(tempString, stage * 2 + (int) strlen(string) + 1, file);
}

Objekt3D *readFileText(FILE *file) {
    Objekt3D *result = malloc(sizeof(Objekt3D));
    result->trokuti = malloc(sizeof(Trokut) * 5000);
    int counter = 0;
    skipLine(file);
    while (prefix(SOLID_END, skipForLength(1, NORMAL, file)) != 1) {
        Trokut *trokut = malloc(sizeof(Trokut));
        Normala *normala = malloc(sizeof(Normala));
        trokut->tocke = malloc(sizeof(Tocka) * 3);
        float *normalX = malloc(sizeof(float));
        float *normalY = malloc(sizeof(float));
        float *normalZ = malloc(sizeof(float));

        fscanf(file, "%f %f %f\n", normalX, normalY, normalZ);
        normala->x = *normalX;
        normala->y = *normalY;
        normala->z = *normalZ;
        trokut->normala = *normala;
        skipLine(file);
        for (int i = 0; i < 3; i++) {
            skipForLength(3, VERTEX, file);
            Tocka *a = malloc(sizeof(Tocka));
            float *x = malloc(sizeof(float));
            float *y = malloc(sizeof(float));
            float *z = malloc(sizeof(float));
            fscanf(file, "%f %f %f\n", x, y, z);
            a->x = *x;
            a->y = *y;
            a->z = *z;
            *(trokut->tocke + i) = *a;
        }
        *(result->trokuti + counter) = *trokut;
        counter++;
    }
    result->n = counter;
    return result;
}
