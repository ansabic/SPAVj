//
// Created by antonio on 14. 12. 2021..
//

#include <stddef.h>
#include <malloc.h>

typedef struct Element {
    struct Element *next;
    int value;
} Element;

Element *push(Element *list, int value) {
    Element *new = (Element *) malloc(sizeof(Element));
    new->value = value;
    new->next = NULL;
    if (list == NULL)
        return new;
    Element *current = list;
    while (current->next != NULL)
        current = current->next;
    current->next = new;
    return list;
}

Element *filterOdds(Element *lst) {
    if (lst == NULL)
        return NULL;
    Element *current = lst;
    Element *next = current->next;
    while (next != NULL) {
        if (next->value % 2 != 0) {
            current->next = next->next;
            free(next);
            next = current->next;
        } else {
            current = next;
            next = next->next;
        }

    }
    if (current->value % 2 != 0) {
        next = lst;
        lst = lst->next;
        free(next);
    }
    return lst;
}

Element *splitEvery2(Element *list) {
    if (list == NULL)
        return NULL;
    Element *newList = list;
    Element *current = newList;
    while (current != NULL) {
        if (current->next != NULL && current->next->next != NULL) {
            Element *temp = current->next->next;
            Element *toFree = current->next;
            current->next = temp;
            free(toFree);
            current = temp;
        } else {
            current->next = NULL;
            current = NULL;
        }
    }
    return newList;
}

Element *deleteEnd(Element *list) {
    Element *current = list;
    if (current == NULL || current->next == NULL) {
        free(current);
        return NULL;
    }
    while (current->next->next != NULL)
        current = current->next;
    free(current->next);
    current->next = NULL;
    return list;
}

Element *reverse(Element *list) {
    Element *newList = NULL;
    while (list != NULL) {
        Element *temp = list;
        list = list->next;
        temp->next = newList;
        newList = temp;
    }
    return newList;
}

Element *deleteN(Element *list, int n) {
    if (list == NULL)
        return NULL;
    Element *current = list;
    Element *next = current->next;
    while (next != NULL) {
        if (next->value == n) {
            if (next->next != NULL) {
                current->next = next->next;
                free(next);
            } else
                current->next = NULL;
        }
        current = current->next;
        if (current != NULL)
            next = current->next;
        else
            next = NULL;
    }
    if (list->value == n) {
        current = list;
        list = list->next;
        free(current);

    }
    return list;
}

void printElements(Element *list) {
    while (list != NULL) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}


int main() {
    Element *list = NULL;
    list = push(list, 7);
    list = push(list, 0);
    list = push(list, 12);
    list = push(list, 7);
    list = push(list, 2);
    list = push(list, 3);
    list = push(list, 1);
    list = push(list, 7);
    list = push(list, 7);
    list = push(list, 0);
    list = push(list, 12);
    list = push(list, 7);
    list = push(list, 2);
    list = push(list, 3);
    list = push(list, 1);
    list = push(list, 7);
    printElements(list);
    list = deleteEnd(list);
    printElements(list);
}

