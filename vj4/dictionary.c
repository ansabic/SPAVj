#include <stdio.h>
#include <malloc.h>
#include "dictionary.h"
#include "string.h"

void print(Dictionary dict) {
    while (dict != NULL && dict->count != 0) {
        printf("%s\t%d\n", dict->word, dict->count);
        dict = dict->next;
    }
}

void destroy(Dictionary dict) {
    while (dict != NULL) {
        Dictionary temp = dict->next;
        dict = dict->next;
        free(temp);
    }
}

Dictionary create() {
    Dictionary dict = malloc(sizeof(Dictionary));
    dict->word = malloc(sizeof(char));
    dict->count = 0;
    return dict;
}

int compareStrings(const char *relative, const char *str) {
    int counter = 0;
    char c1 = relative[counter];
    char c2 = str[counter];
    while (c1 != '\0' && c2 != '\0') {
        c1 = relative[counter];
        c2 = str[counter];
        if (c1 != c2 && c1 != '\0' && c2 != '\0')
            return c2 - c1;
        counter++;
    }
    if (c1 == '\0' && c2 == '\0')
        return 0;
    else if (c1 == '\0')
        return c2 - 'a';
    else
        return -(c1 - 'a');
}

Dictionary add(Dictionary dict, char *str) {
    //Pocetak, prazan dict
    if (dict->count == 0) {
        dict->word = str;
        dict->count = 1;
        return dict;
    }
    Dictionary temp = dict;
    Dictionary before = dict;
    int diff = compareStrings(temp->word, str);
    //Rijec je veca alfanumericki od relativne u rijecniku
    while (diff > 0 && temp->next != NULL) {
        before = temp;
        temp = temp->next;
        diff = compareStrings(temp->word, str);
    }
    if (diff == 0) {
        temp->count++;
        return dict;
    } else if (diff < 0) {
        Dictionary new = create();
        if (temp->next != NULL || before == temp)
            new->next = temp;
        new->word = str;
        new->count = 1;
        if (before == temp)
            return new;

        before->next = new;
        return dict;
    }
        //Kraj dict-a
    else {
        Dictionary new = create();
        new->count = 1;
        new->word = str;
        temp->next = new;
        return dict;
    }
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
    Dictionary newDict = create();
    Dictionary point = newDict;
    while (indict != NULL) {
        if (filter(indict)) {
            point->count = indict->count;
            point->word = indict->word;
            point->next = create();
            point = point->next;
        }
        indict = indict->next;
    }
    return newDict;
}
