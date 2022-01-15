#include "hash.h"
#include <malloc.h>
#include <string.h>

#define HCONST 3567892

HashTable *NewTable(int size) {
    // kreira novu hash tablicu (alocira samu strukturu i niz pokaziva?a)
    HashTable *result = malloc(sizeof(HashTable));
    result->size = size;
    result->load = 0;
    result->table = malloc(sizeof(Bin) * size);
    return result;
}

unsigned int hash(char *word) {
    // od kljuca generira hash kod
    unsigned int key = 0;
    while (*word != '\0') {
        key = key * HCONST + *word;
        word++;
    }
    return key;
}

void Insert(HashTable *ht, char *word) {
    Bin **table = ht->table;
    // dodaje novu rijec u listu na odgovarajucem pretincu
    unsigned int wordHash = hash(word) % ht->size;
    Bin *current = table[wordHash];
    if (current == NULL) {
        current = malloc(sizeof(Bin));
        current->word = word;
        current->next = NULL;
        return;
    }
    while (current->next != NULL)
        current = current->next;
    current->word = word;
}

int Get(HashTable *ht, char *word) {
    // vraca 0 ili 1 ovisno o tome da li rijec postoji u tablici
    Bin **table = ht->table;
    if ((*table) == NULL)
        return 0;
    unsigned int wordHash = hash(word) % ht->size;
    Bin *current = table[wordHash];
    while (current != NULL) {
        if (strcmp(current->word, word) == 0)
            return 1;
        current = current->next;
    }

    return 0;
}

void DeleteTable(HashTable *ht) {
    // brise cijelu hash tablicu (liste na svim pretincima (rijec i element liste), pretince ...)
    for (int i = 0; i < ht->size; i++) {
        Bin *current = ht->table[i];
        while (current != NULL) {
            Bin *temp = current;
            current = current->next;
            free(temp);
        }
    }
}