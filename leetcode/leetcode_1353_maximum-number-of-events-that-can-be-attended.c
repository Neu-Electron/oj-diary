typedef struct {
    int* data;
    int capacity;
    int size;
} MinHeap;

MinHeap* createHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap* heap, int index) {
    while (index != 0 && heap->data[(index - 1) / 2] > heap->data[index]) {
        swap(&heap->data[(index - 1) / 2], &heap->data[index]);
        index = (index - 1) / 2;
    }
}

void heapifyDown(MinHeap* heap, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        if (smallest == index)
            break;

        swap(&heap->data[index], &heap->data[smallest]);
        index = smallest;
    }
}

void push(MinHeap* heap, int value) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = (int*)realloc(heap->data, heap->capacity * sizeof(int));
    }
    heap->data[heap->size++] = value;
    heapifyUp(heap, heap->size - 1);
}

int pop(MinHeap* heap) {
    if (heap->size == 0)
        return -1;
    int root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapifyDown(heap, 0);
    return root;
}

int top(MinHeap* heap) {
    if (heap->size == 0)
        return -1;
    return heap->data[0];
}

int isEmpty(MinHeap* heap) { return heap->size == 0; }

void freeHeap(MinHeap* heap) {
    free(heap->data);
    free(heap);
}

int compareEvents(const void* a, const void* b) {
    int* eventA = *(int**)a;
    int* eventB = *(int**)b;
    if (eventA[0] != eventB[0]) {
        return eventA[0] - eventB[0];
    }
    return eventA[1] - eventB[1];
}

int maxEvents(int** events, int eventsSize, int* eventsColSize) {
    qsort(events, eventsSize, sizeof(int*), compareEvents);

    MinHeap* minHeap = createHeap(eventsSize);
    int day = 0, ans = 0;
    int eventIndex = 0;

    while (!isEmpty(minHeap) || eventIndex < eventsSize) {
        if (isEmpty(minHeap)) {
            day = events[eventIndex][0];
        }

        while (eventIndex < eventsSize && events[eventIndex][0] <= day) {
            push(minHeap, events[eventIndex][1]);
            eventIndex++;
        }

        pop(minHeap);
        ans++;
        day++;

        while (!isEmpty(minHeap) && top(minHeap) < day) {
            pop(minHeap);
        }
    }

    freeHeap(minHeap);
    return ans;
}