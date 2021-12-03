#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include "dictionary.h"
#include "string.h"

char *readWord(FILE *fd) {
    char *buffer = malloc(sizeof(char) * 20);
    int i = 0;
    int c;
    do {
        c = fgetc(fd);
        if (c == EOF)
            return 0;
    } while (!isalpha(c));

    do {
        buffer[i] = (char) tolower(c);
        i++;
        c = fgetc(fd);
        if (c == 146)
            c = '\'';
    } while (isalpha(c) || c == '\'');

    buffer[i] = '\0';
    return buffer;
}


int main() {
    FILE *fd;
    Dictionary dict;

    fd = fopen("/home/antonio/CLionProjects/SPAVj/vj4/dummy.txt", "rt");
    if (fd == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    dict = create();
    char *buffer = readWord(fd);
    do {
        printf("%s\n", buffer);
        dict = add(dict, buffer);
        buffer = readWord(fd);
    } while (buffer != NULL);
    fclose(fd);
    //print(dict);
    Dictionary new = filterDictionary(dict, filter);
    print(new);
    destroy(dict);
}