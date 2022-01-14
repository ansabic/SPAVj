#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include "dictionary.h"
#include "string.h"

int readWord(FILE *fd, char *buffer) {
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


int main4() {
    FILE *fd;
    char buffer[1024];
    Dictionary dict;

    fd = fopen("/home/antonio/CLionProjects/SPAVj/vj4/dummy.txt", "rt");
    if (fd == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    dict = create();
    while (readWord(fd, buffer)) {
        char *temp = malloc(sizeof(char) * 20);
        strcpy(temp, buffer);
        dict = add(dict, temp);
    }
    fclose(fd);
    print(dict);
    //dict = firstToEnd(dict);
    print(dict);
    destroy(dict);
    return 1;
}