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
    unsigned int result;
    fread(&result, sizeof(unsigned int), 1, file);
    return result;
}

Trokut readTrokut(FILE *file, int enableColor) {
    Trokut trokut;
    Normala normala;

    fread(&normala.x, sizeof(float), 1, file);
    fread(&normala.y, sizeof(float), 1, file);
    fread(&normala.z, sizeof(float), 1, file);
    trokut.normala = normala;

    for (int i = 0; i < 3; i++) {
        Tocka a;
        fread(&a.x, sizeof(float), 1, file);
        fread(&a.y, sizeof(float), 1, file);
        fread(&a.z, sizeof(float), 1, file);
        *(trokut.tocke + i) = a;
    }
    if (enableColor) {
        unsigned int color;
        fread(&color, sizeof(unsigned int), 1, file);
        trokut.boja = color;
    }
    return trokut;
}

Objekt3D readFileBinary(FILE *file) {
    Objekt3D objekt;
    readHeader(file);
    objekt.n = readNumberOfTriangles(file);
    objekt.trokuti = malloc(sizeof(Trokut) * objekt.n);
    for (int i = 0; i < objekt.n; i++)
        *(objekt.trokuti + i) = readTrokut(file, 1);
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

void skipLine(FILE *file) {
    char tempString[99];
    fgets(tempString, 99, file);
}

char *skipForLength(int stage, const char *string, FILE *file) {
    char tempString[99];
    return fgets(tempString, stage * 2 + (int) strlen(string) + 1, file);
}

Objekt3D readFileText(FILE *file) {
    Objekt3D result;
    result.trokuti = malloc(sizeof(Trokut) * 5000);
    int counter = 0;
    skipLine(file);
    while (prefix(SOLID_END, skipForLength(1, NORMAL, file)) != 1) {
        Trokut trokut;
        Normala normala;

        fscanf(file, "%f %f %f\n", &normala.x, &normala.y, &normala.z);
        trokut.normala = normala;
        skipLine(file);
        for (int i = 0; i < 3; i++) {
            skipForLength(3, VERTEX, file);
            Tocka a;
            fscanf(file, "%f %f %f\n", &a.x, &a.y, &a.z);
            *(trokut.tocke + i) = a;
        }
        *(result.trokuti + counter) = trokut;
        counter++;
    }
    result.n = counter;
    result.trokuti = realloc(result.trokuti, sizeof(Trokut) * counter);
    return result;
}
