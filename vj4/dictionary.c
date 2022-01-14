#include <stdio.h>
#include <malloc.h>
#include "dictionary.h"
#include "string.h"

void print(Dictionary dict) {
    while (dict != NULL) {
        printf("%s\t%d\n", dict->word, dict->count);
        dict = dict->next;
    }
}

void destroy(Dictionary dict) {
    while (dict != NULL) {
        Dictionary temp = dict;
        dict = dict->next;
        free(temp);
    }
}

Dictionary create() {
    Dictionary dict = malloc(sizeof(Dictionary));
    dict->word = NULL;
    dict->next = NULL;
    return dict;
}

Dictionary add(Dictionary head, char *str) {
    Dictionary current = head;
    if (current->word == NULL) {
        current->next = NULL;
        current->count = 1;
        current->word = str;
        return head;
    }
    int diffCurrent = strcmp(str, current->word);
    if (diffCurrent < 0) {
        Dictionary new = create();
        new->word = str;
        new->count = 1;
        new->next = current;
        return new;
    } else if (diffCurrent == 0) {
        current->count++;
        return head;
    }
    while (current->next != NULL) {
        int diffNext = strcmp(str, current->next->word);
        if (diffNext < 0) {
            Dictionary new = create();
            new->next = current->next;
            new->word = str;
            new->count = 1;
            current->next = new;
            return head;
        } else if (diffNext == 0) {
            current->count++;
            return head;
        } else
            current = current->next;
    }
    Dictionary new = create();
    new->next = NULL;
    new->word = str;
    new->count = 1;
    current->next = new;
    return head;
}

int filter(Word *w) {
    int counter = 0;
    while (w->word[counter] != '\0') {
        counter++;
        if (counter >= 2 && w->count > 5)
            return 1;
    }
    return 0;
}

Dictionary filterDictionary(Dictionary indict, int (*filter)(Word *w)) {
    if (indict != NULL) {
        Dictionary temp = create();
        Dictionary current = temp;
        while (indict != NULL) {
            if (filter(indict)) {
                current->word = indict->word;
                current->count = indict->count;
                current = current->next = create();
            }
            indict = indict->next;
        }
        destroy(indict);
        return temp;
    }
    return NULL;
}
