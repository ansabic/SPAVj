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

int compareStrings(const char *str1, const char *str2) {
    int counter1 = 0;
    int counter2 = 0;
    char c1 = str1[counter1];
    char c2 = str2[counter2];
    while (c1 != '\0' && c2 != '\0') {
        c1 = str1[counter1];
        c2 = str2[counter2];
        if (c1 != c2)
            return c2 - c1;
        counter1++;
        counter2++;
    }
    if (c1 == '\0' && c2 == '\0')
        return 0;
    else if (c1 == '\0')
        return c2 - 'a';
    else
        return -(c1 - 'a');
}

Dictionary add(Dictionary dict, char *str) {
    while (dict != NULL) {
        if (dict->count == 0) {
            Dictionary newDict = create();
            strcpy(newDict->word, str);
            newDict->word = str;
            newDict->count = 1;
            return newDict;
        }
        int diff = compareStrings(dict->word, str);
        if (diff < 0) {
            Dictionary result = malloc(sizeof(Dictionary));
            strcpy(result->word, str);
            result->next = dict;
            result->count = 1;
            return result;
        } else if (diff > 0) {
            if (dict->next != NULL && compareStrings(dict->next->word, str) > 0) {
                dict = dict->next;
            } else if (dict->next != NULL && dict->next->word == str) {
                dict->next->count++;
                return dict;
            } else {
                Dictionary result = create();
                result->word = str;
                if (dict->next != NULL)
                    result->next = dict->next;
                result->count = 1;
                dict->next = result;
                return result;
            }
        } else if (diff == 0) {
            dict->count++;
            return dict;
        }
    }
}

int filter(Word *w) {

}
