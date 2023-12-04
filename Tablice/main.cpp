#include <iostream>
using namespace std;

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
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
}

int main() {
    int tab[24] = {1, 2, 4, 6, 3, 2, 5, -3, 4 -12, -4, 55, 123, -23, -44, 0, -54, -56, -2003, -200, 20, 69, 60, 420};


}
