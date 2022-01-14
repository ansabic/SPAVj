//
// Created by antonio on 05. 12. 2021..
//

#include <stdlib.h>
#include <stdio.h>
#include "constants.h"

struct {
    void *data;
    int priority;
} typedef heapValue;

typedef heapValue *heap;

heap initHeap() {
    heap h = malloc(sizeof(heapValue) * N);
    for (int i = 0; i < N; i++)
        h[i].data = NULL;
    return h;
}

heap swapTopRecursively(heap h, int index) {
    heap parent = &h[(index - 1) / 2];
    heap child = &h[index];
    if (parent->priority < child->priority) {
        heapValue temp = *parent;
        *parent = *child;
        *child = temp;
        index = (index - 1) / 2;
        return swapTopRecursively(h, index);
    }
    return h;
}

heap insertInHeapIterative(heap heap, heapValue value) {
    int index = 0;
    while (heap[index].data != NULL)
        index++;
    heap[index] = value;
    while (index != 0) {
        heapValue *parent = &heap[(index - 1) / 2];
        heapValue *child = &heap[index];
        if (parent->priority < child->priority) {
            heapValue temp = *parent;
            *parent = *child;
            *child = temp;
            index = (index - 1) / 2;
        } else
            return heap;
    }
    return heap;
}

heap insertInHeapRecursive(heap heap, heapValue value, int index) {
    if (heap[index].data != NULL)
         return insertInHeapRecursive(heap, value, index + 1);
    heap[index] = value;
    return swapTopRecursively(heap, index);
}


heap swapBottomRecursively(heap h, int index, int size) {
    int newIndex;
    heap parent = &h[index];
    heap lChild = &h[(index + 1) * 2 - 1];
    heap rChild = &h[(index + 1) * 2];
    heap max;
    if (lChild->priority >= rChild->priority) {
        max = lChild;
        newIndex = (index + 1) * 2 - 1;
    } else {
        max = rChild;
        newIndex = (index + 1) * 2;
    }
    if (parent->priority < max->priority) {
        heapValue temp = *parent;
        *parent = *max;
        *max = temp;
        index = newIndex;
        return swapBottomRecursively(h, index, size - 1);
    }
    return h;
}

heap removeHeadFromHeapRecursively(heap heap, int *size) {
    heap[0] = heap[*size - 1];
    (*size)--;
    return swapBottomRecursively(heap, 0, *size);
}

int main() {
    heap heap = initHeap();
    printf("How many elements?\n");
    int elementNumber;
    scanf("%d", &elementNumber);
    printf("Enter %d priorities: \n", elementNumber);
    for (int i = 0; i < elementNumber; i++) {
        int value;

        scanf("%d", &value);
        heapValue heapValue;
        heapValue.priority = value;
        heapValue.data = (void *) (random() % 100);
        heap = insertInHeapRecursive(heap, heapValue, 0);
    }
    for (int i = 0; i < elementNumber; i++) {
        printf("%d ", heap[i].priority);
    }
    printf("\n");
    heap = removeHeadFromHeapRecursively(heap, &elementNumber);
    //heap = heapSort(heap,elementNumber);
    for (int i = 0; i < elementNumber; i++) {
        printf("%d ", heap[i].priority);
    }
}
