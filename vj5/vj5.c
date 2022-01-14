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


heap insertInHeapRecursive(heap heap, heapValue value, int* lastIndex) {
    heap[*lastIndex] = value;
    (*lastIndex)++;
    return swapTopRecursively(heap, *lastIndex);
}


heap swapBottomRecursively(heap h, int index, int size) {
    int newIndex;
    int leftIndex = (index + 1) * 2 - 1;
    int rightIndex = (index + 1) * 2;
    heap parent = &h[index];
    heap lChild = &h[leftIndex];
    heap rChild = &h[rightIndex];
    heap max;
    if(leftIndex > size && rightIndex <= size) {
        max = lChild;
        newIndex = leftIndex;
    }
    else if(rightIndex > size && leftIndex <= size) {
        max = rChild;
        newIndex = rightIndex;
    }
    else if(rightIndex >= size && leftIndex >= size) {
        return h;
    }
    else if (lChild->priority >= rChild->priority) {
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
        heap = insertInHeapRecursive(heap, heapValue, &elementNumber);
    }
    for (int i = 0; i < elementNumber; i++) {
        printf("%d ", heap[i].priority);
    }
    printf("\n");
    heap = removeHeadFromHeapRecursively(heap, &elementNumber);
    //heap = heapSort(heap,elementNumber);
    for (int i = 0; i < elementNumber - 1; i++) {
        printf("%d ", heap[i].priority);
    }
}
