//
// Created by antonio on 05. 12. 2021..
//

#include <stdlib.h>
#include <stdio.h>
#include "constants.h"

struct {
    void* data;
    int priority;
} typedef heapValue;

typedef heapValue* heap;

heap initHeap() {
    heap h = malloc(sizeof(heapValue) * N);
    for(int i = 0; i < N; i++)
        h[i].data = NULL;
    return h;
}

heap insertInHeapIterative(heap heap, heapValue value) {
    int index = 0;
    while (heap[index].data != NULL)
        index++;
    heap[index] = value;
    while(index != 0) {
        heapValue* parent = &heap[(index - 1) / 2];
        heapValue* child = &heap[index];
        if(parent->priority < child->priority) {
            heapValue temp = *parent;
            *parent = *child;
            *child = temp;
            index = (index - 1) / 2;
        }
        else
            return heap;
    }
    return heap;
}

heap swapTopRecursively(heap heap, int index) {
    heapValue* parent = &heap[(index - 1) / 2];
    heapValue* child = &heap[index];
    if(parent->priority < child->priority) {
        heapValue temp = *parent;
        *parent = *child;
        *child = temp;
        index = (index - 1) / 2;
        return swapTopRecursively(heap, index);
    }
    return heap;
}

heap swapBottomRecursively(heap heap, int index, int* size) {
    int newIndex;
    heapValue* parent = &heap[index];
    heapValue* lChild = &heap[(index + 1) * 2 - 1];
    heapValue* rChild = &heap[(index + 1) * 2];
    heapValue* max;
    if(lChild->priority >= rChild->priority) {
        max = lChild;
        newIndex = (index + 1) * 2 - 1;
    }
    else {
        max = rChild;
        newIndex = (index + 1) * 2;
    }
    if(parent->priority < max->priority) {
        heapValue temp = *parent;
        *parent = *max;
        *max = temp;
        index = newIndex;
        (*size)--;
        return swapBottomRecursively(heap, index, size);
    }
    return heap;
}

heap insertInHeapRecursive(heap heap, heapValue value) {
    int index = 0;
    while (heap[index].data != NULL)
        index++;
    heap[index] = value;
    return swapTopRecursively(heap, index);
}

heap removeHeadFromHeapRecursively(heap heap, int* size) {
    heap[0] = heap[*size - 1];
    return swapBottomRecursively(heap, 0, size);
}

int main() {
    heap heap = initHeap();
    printf("How many elements?\n");
    int elementNumber;
    scanf("%d", &elementNumber);
    for(int i = 0; i < elementNumber; i++) {
        int value;
        printf("Enter priority: \n");
        scanf("%d", &value);
        heapValue heapValue;
        heapValue.priority = value;
        heapValue.data = (void *) (random() % 100);
        heap = insertInHeapRecursive(heap, heapValue);
    }
    heap = removeHeadFromHeapRecursively(heap, &elementNumber);
    for(int i = 0; i < elementNumber; i++) {
        printf("%d ",heap[i].priority);
    }
}
