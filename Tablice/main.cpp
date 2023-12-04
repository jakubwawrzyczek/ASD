#include <iostream>
using namespace std;

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void bubbleSort(int* arr, int len) {

    int n = len-1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            // Porównaj sąsiadujące elementy i zamień, jeśli są w niewłaściwej kolejności
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

}

void swap(int* arr, int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void heapify(int* arr, int n, int heapsize) {
    int L = 2*n;
    int R = 2*n+1;
    int largest = 0;

    if (L <= heapsize && arr[L] > arr[n]) {
        largest = L;
    }
    else {
        largest = n;
    }

    if (R <= heapsize && arr[R] > arr[largest]) {
        largest = R;
    }

    if (largest != n) {
        swap(arr, largest, n);
        heapify(arr, largest, heapsize);
    }
}

void buildHeap(int* arr, int heapsize) {
    for (int i = heapsize / 2 ; i < 0 ; i--) {
        heapify(arr, i, heapsize);
    }
}

void heapSort(int* arr, int heapsize) {
    buildHeap(arr, heapsize);

    while (heapsize > 0) {
        swap(arr, 1, heapsize);
        heapsize--;
        heapify(arr, 1, heapsize);
    }
}

int main() {
    int arr[24] = {NULL, 1, 2, 4, 6, 3, 2, 5, -3, 4 -12, -4, 55, 123, -23, -44, 0, -54, -56, -2003, -200, 20, 69, 60, 420};

    heapSort(arr, 24);

    printArray(arr, 24);

}
