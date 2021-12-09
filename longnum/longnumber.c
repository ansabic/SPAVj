//
// Created by antonio on 08. 12. 2021..
//
#include "constants.h"
#include "longnumber.h"
#include <stdlib.h>
#include <stdio.h>

LongNumber read_longnum(char *fname) {
    FILE *file = fopen(fname, "rt");
    char digit;
    LongNumber head = malloc(sizeof(LongNumber));
    int counter = 0;
    LongNumber current = head;
    LongNumber before = current;
    while (fread(&digit, sizeof(char), 1, file)) {
        if (digit && digit != '\0' && digit != EOF && digit != '\n') {
            counter++;
            if (counter % DIGIT_LIMIT == 0)
                realloc(head, (counter / DIGIT_LIMIT) * DIGIT_LIMIT * sizeof(int));
            current->z = atoi(&digit);
            before = current;
            current = current->next = malloc(sizeof(LongNumber));
        }
    }
    before->next = NULL;
    return head;
}

void print_longnum(LongNumber num) {
    while (num != NULL) {
        printf("%d", num->z);
        num = num->next;
    }
    printf("\n");
}

LongNumber reverse(LongNumber num) {
    LongNumber head = num;
    LongNumber before = num;
    int *array = malloc(sizeof(int) * DIGIT_LIMIT);
    int counter = 0;
    while (num != NULL) {
        if (counter % DIGIT_LIMIT == 0)
            realloc(array, (counter / DIGIT_LIMIT) * DIGIT_LIMIT * sizeof(int));
        array[counter] = num->z;
        counter++;
        num = num->next;
    }
    num = head;
    for (int i = counter - 1; i >= 0; --i) {
        num->z = array[i];
        before = num;
        num = num->next = malloc(sizeof(LongNumber));
    }
    before->next = NULL;
    free(array);
    return head;
}

LongNumber add_longnum(LongNumber a, LongNumber b) {
    LongNumber currentA = reverse(a);
    LongNumber currentB = reverse(b);
    LongNumber head = malloc(sizeof(LongNumber));
    LongNumber before = head;
    LongNumber resultPosition = head;
    int carry = 0;
    while (currentA != NULL || currentB != NULL) {
        int valueA = 0;
        int valueB = 0;
        if (currentA != NULL) {
            valueA = currentA->z;
            currentA = currentA->next;
        }
        if (currentB != NULL) {
            valueB = currentB->z;
            currentB = currentB->next;
        }
        int sum = valueA + valueB;
        resultPosition->z = (sum + carry) % 10;
        before = resultPosition;
        resultPosition = resultPosition->next = malloc(sizeof(LongNumber));
        if (sum >= 10)
            carry = sum / 10;
        else carry = 0;
    }
    if (carry != 0)
        resultPosition->z = carry;
    else
        before->next = NULL;
    return reverse(head);
}

LongNumber mul_by_digit(LongNumber num, int z) {
    LongNumber currentA = reverse(num);
    LongNumber head = malloc(sizeof(LongNumber));
    LongNumber before = head;
    LongNumber resultPosition = head;
    int carry = 0;
    while (currentA != NULL) {
        int valueA = currentA->z;
        currentA = currentA->next;
        int mult = valueA * z;
        resultPosition->z = (mult + carry) % 10;
        before = resultPosition;
        resultPosition = resultPosition->next = malloc(sizeof(LongNumber));
        if (mult >= 10)
            carry = (mult + carry) / 10;
        else carry = 0;
    }
    if (carry != 0)
        resultPosition->z = carry;
    else
        before->next = NULL;
    return reverse(head);
}

LongNumber mul_by_pow10(LongNumber num, int pow) {
    LongNumber reversed = reverse(num);
    LongNumber head = malloc(sizeof(LongNumber));
    LongNumber new = head;
    for (int i = 0; i < pow; i++) {
        new->z = 0;
        new = new->next = malloc(sizeof(LongNumber));
    }
    LongNumber old = new;
    while (reversed != NULL) {
        new->z = reversed->z;
        old = new;
        new = new->next = reversed;
        reversed = reversed->next;
    }
    old->next = NULL;
    return reverse(head);
}

LongNumber mul_longnum(LongNumber a, LongNumber b) {
    return NULL;
}
