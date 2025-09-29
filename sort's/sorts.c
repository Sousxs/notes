#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Quicksort
int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quicksort_recursive(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort_recursive(arr, low, pi - 1);
        quicksort_recursive(arr, pi + 1, high);
    }
}

void quicksort(int* arr, size_t n) {
    quicksort_recursive(arr, 0, n - 1);
}

// Mergesort
void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = malloc(n1 * sizeof(int));
    int* R = malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L);
    free(R);
}

void mergesort_recursive(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesort_recursive(arr, left, mid);
        mergesort_recursive(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergesort(int* arr, size_t n) {
    mergesort_recursive(arr, 0, n - 1);
}

// Heapsort
void heapify(int* arr, size_t n, size_t i) {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapsort(int* arr, size_t n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// Bubble Sort
void bubblesort(int* arr, size_t n) {
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Insertion Sort
void insertionsort(int* arr, size_t n) {
    for (size_t i = 1; i < n; i++) {
        int key = arr[i];
        size_t j = i;
        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;
    }
}

// Selection Sort
void selectionsort(int* arr, size_t n) {
    for (size_t i = 0; i < n - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

int main() {
    const size_t ns[] = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
    const size_t num_ns = sizeof(ns) / sizeof(ns[0]);
    const unsigned int seed = 42;

    typedef void (*sort_func)(int*, size_t);
    const sort_func sorts[] = {quicksort, mergesort, heapsort, bubblesort, insertionsort, selectionsort};
    const char* sort_names[] = {"Quicksort", "Mergesort", "Heapsort", "Bubble Sort", "Insertion Sort", "Selection Sort"};
    const size_t num_sorts = sizeof(sorts) / sizeof(sorts[0]);

    printf("Note: For O(n^2) sorts (Bubble, Insertion, Selection), large n may take excessive time.\n");
    printf("Results in milliseconds:\n\n");

    for (size_t i = 0; i < num_ns; i++) {
        size_t n = ns[i];
        int* original = malloc(n * sizeof(int));
        if (!original) {
            fprintf(stderr, "Memory allocation failed for n=%zu\n", n);
            continue;
        }

        srand(seed);
        for (size_t j = 0; j < n; j++) {
            original[j] = rand() % (10 * n);
        }

        printf("n = %zu\n", n);
        for (size_t k = 0; k < num_sorts; k++) {
            int* arr = malloc(n * sizeof(int));
            if (!arr) {
                fprintf(stderr, "Memory allocation failed for sort %s, n=%zu\n", sort_names[k], n);
                continue;
            }
            memcpy(arr, original, n * sizeof(int));

            clock_t start = clock();
            sorts[k](arr, n);
            clock_t end = clock();

            double time_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;

            printf("%s: %.2f ms\n", sort_names[k], time_ms);

            free(arr);
        }
        printf("\n");

        free(original);
    }

    return 0;
}