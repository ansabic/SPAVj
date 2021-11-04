//
// Created by antonio on 03. 11. 2021..
//

#ifndef SPAVJ_STL_H
#define SPAVJ_STL_H

typedef struct {
    float x;
    float y;
    float z;
} Tocka;

typedef struct {
    float x;
    float y;
    float z;
} Normala;

typedef struct {
    Tocka *tocke;
    Normala normala;
    unsigned short boja;

} Trokut;

typedef struct {
    Trokut *trokuti;
    unsigned int n;
} Objekt3D;

Objekt3D* readFileBinary(FILE* file);
void writeFileBinary(FILE* file, Objekt3D* objekt);
Objekt3D* readFileText(FILE* file);
void writeFileText(FILE* file, char* fileName, Objekt3D* objekt);

#endif //SPAVJ_STL_H
