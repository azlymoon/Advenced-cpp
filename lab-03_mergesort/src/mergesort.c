#include "mergesort.h"
#include <stdlib.h>

int merge(
    size_t element_size, 
    char* left,
    char* mid,
    char* right,
    int (*comparator)(const void*, const void*)
) {
    size_t i = 0, j = 0;
    size_t elements = (right - left) / element_size;
    char* result = malloc(elements * element_size);
    if (result == NULL) {
        return -1;
    }

    while (left + i * element_size < mid && mid + j * element_size < right) {
        if (comparator(left + i * element_size, mid + j * element_size) < 0) {
            for (size_t k = 0; k < element_size; k++)
                *(result + k + (i + j) * element_size) = *(left + k + i * element_size);
            i++;
        }
        else {
            for (size_t k = 0; k < element_size; k++)
                *(result + k + (i + j) * element_size) = *(mid + k + j * element_size);
            j++;
        }
    }
    while (left + i * element_size < mid) {
        for (size_t k = 0; k < element_size; k++)
            *(result + k + (i + j) * element_size) = *(left + k + i * element_size);
        i++;
    }
    while (mid + j * element_size < right) {
        for (size_t k = 0; k < element_size; k++)
            *(result + k + (i + j) * element_size) = *(mid + k + j * element_size);
        j++;
    }
    for (size_t l = 0; l < i + j; l++) {
        for (size_t k = 0; k < element_size; k++) {
            *(left + k + l * element_size) = *(result + k + l * element_size);
        }
    }
    free(result);
    return 0;
}

int mergesort(
    void* array,
    size_t elements, size_t element_size,
    int (*comparator)(const void*, const void*)
) {
    int status;
    char* arr = array;
    size_t m = elements / 2;
    if (elements <= 1)
        return 0;
    status = mergesort(arr, m, element_size, comparator);
    status = mergesort(arr + m * element_size, elements - m, element_size, comparator);
    if (status == -1)
        return -1;
    char* left = arr;
    char* mid = arr + (elements / 2) * element_size;
    char* right = arr + elements * element_size;
    if (merge(element_size, left, mid, right, comparator) == -1)
        return -1;
    return 0;
}