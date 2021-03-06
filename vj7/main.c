#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include "hash.h"

int readWordvj7(FILE *fd, char *buffer) {
    int c;
    do {
        c = fgetc(fd);
        if (c == EOF)
            return 0;
    } while (!isalpha(c));

    do {
        *buffer = tolower(c);
        buffer++;
        c = fgetc(fd);
        if (c == 146)
            c = '\'';
    } while (isalpha(c) || c == '\'');

    *buffer = '\0';
    return 1;
}

void fillTable(HashTable *dict) {
    FILE *fd;
    char buffer[1024];

    fd = fopen("/home/antonio/CLionProjects/SPAVj/vj7/big.txt", "rt");
    if (fd == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (readWordvj7(fd, buffer)) {
        //printf("%s\n", buffer);
        if (!Get(dict, buffer))
            Insert(dict, strdup(buffer));
    }

    fclose(fd);
}

int main() {
    int i, size;
    HashTable *dict;

    for (size = (1 << 8); size < (1 << 18); size *= 2) {
        float st, et;
        dict = NewTable(size);
        st = clock();
        fillTable(dict);
        et = clock();
        printf("Size = %d, load factor = %f, time = %f\n", dict->size, (float) dict->load / dict->size,
               (et - st) / CLOCKS_PER_SEC);
        DeleteTable(dict);
    }
}