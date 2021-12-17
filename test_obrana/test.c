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

    if (lst == NULL) {
        return NULL;
    }

    Element *pt = lst;
    Element *tmp = lst->next;
    while (tmp != NULL) {
        if (tmp->value % 2 != 0) {
            pt->next = tmp->next;
            free(tmp);
            tmp = pt->next;
        } else {
            pt = pt->next;
            tmp = tmp->next;
        }
    }

    if (lst->value % 2 != 0) {
        tmp = lst;
        lst = lst->next;
        free(tmp);
    }

    return lst;
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
    list = push(list, 0);
    list = push(list, 12);
    list = push(list, 7);
    list = push(list, 2);
    list = push(list, 3);
    list = push(list, 1);
    list = push(list, 7);
    list = filterOdds(list);
    printElements(list);
}

