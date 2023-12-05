#include <iostream>
using namespace std;

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void swap(int* arr, int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

// Bubble Sort
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

void bubbleSort(int* arr, long l, long r) {

    int n = r;
    int i = l;

    for (; i < n; i++) {
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

// Heaps
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


// Quick Sort
long partition(int* arr, long l, long r) {
    int x = arr[r];
    long i = l - 1;

    for (; l < r ; ++l) {
        if(arr[l] <= x) { swap(arr[++i], arr[l]); }
    }

    swap(arr[i+1], arr[r]);
    return i + 1;
}

void quickSort(int* arr, long l, long r) {
    if (l < r) {
        long p = partition(arr, l, r);
        quickSort(arr, l, p - 1);
        quickSort(arr, p + 1 , r);
    }
}


// Hybrid Sort (quick sort + bubble sort)
void hybridSort(int* arr, long l, long r) {
    if (r - l < 11) {
        bubbleSort(arr, l, r);
    }

    else if (l < r) {
        long p = partition(arr, l, r);
        quickSort(arr, l, p - 1);
        quickSort(arr, p + 1 , r);
    }
}


int main() {
//    int arr[24] = {NULL, 1, 2, 4, 6, 3, 2, 5, -3, 4 -12, -4, 55, 123, -23, -44, 0, -54, -56, -2003, -200, 20, 69, 60, 420};
//
//    hybridSort(arr, 0, 23);
//
//    printArray(arr, 24);



    // ---------- TABLICA POSORTOWANA ----------
    cout << "\n\n\n--- TABLICE POSORTOWANE ---\n";

    int posortowana_krotka[100] = {};
    int posortowana_dluga[10000] = {};

    // wypelnianie tablic
    for (int i = 0 ; i < 100 ; i++) {
        posortowana_krotka[i] = i;
    }
    for (int i = 0 ; i < 10000 ; i++) {
        posortowana_dluga[i] = i;
    }


    // sortowanie i mierzenie czasu dla krotkiej

    // bubble sort
    auto start = std::chrono::high_resolution_clock::now();
    bubbleSort(posortowana_krotka, 100);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Czas sortowania (krotka / posortowana / bubble sort): " << duration.count() << "ms" << endl;

    // quick sort
    start = std::chrono::high_resolution_clock::now();
    quickSort(posortowana_krotka, 0, 99);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Czas sortowania (krotka / posortowana / quick sort): " << duration.count() << "ms" << endl;

    // hybrid sort
    start = std::chrono::high_resolution_clock::now();
    hybridSort(posortowana_krotka, 0, 99);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Czas sortowania (krotka / posortowana / hybrid sort): " << duration.count() << "ms" << endl;

    cout << "\n\n";

    // sortowanie i mierzenie czasu dla dlugiej

    // bubble sort
    start = std::chrono::high_resolution_clock::now();
    bubbleSort(posortowana_dluga, 10000);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Czas sortowania (dluga / posortowana / bubble sort): " << duration.count() << "ms" << endl;

    // quick sort
    start = std::chrono::high_resolution_clock::now();
    quickSort(posortowana_dluga, 0, 9999);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Czas sortowania (dluga / posortowana / quick sort): " << duration.count() << "ms" << endl;

    // hybrid sort
    start = std::chrono::high_resolution_clock::now();
    hybridSort(posortowana_dluga, 0, 9999);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Czas sortowania (dluga / posortowana / hybrid sort): " << duration.count() << "ms" << endl;


    // ---------- TABLICA ODWROTNIE POSORTOWANA ----------
    cout << "\n\n\n--- TABLICE ODWROTNIE POSORTOWANE ---\n";

    int odwrotnie_posortowana_krotka1[100] = {};
    int odwrotnie_posortowana_krotka2[100] = {};
    int odwrotnie_posortowana_krotka3[100] = {};

    int odwrotnie_posortowana_dluga1[100000] = {};
    int odwrotnie_posortowana_dluga2[100000] = {};
    int odwrotnie_posortowana_dluga3[100000] = {};

    // wypelnianie tablic
    for (int i = 0 ; i < 100 ; i++) {
        int n = 100 - i;
        odwrotnie_posortowana_krotka1[i] = n;
        odwrotnie_posortowana_krotka2[i] = n;
        odwrotnie_posortowana_krotka3[i] = n;
    }
    for (int i = 0 ; i < 10000 ; i++) {
        int n = 10000 - i;
        odwrotnie_posortowana_dluga1[i] = n;
        odwrotnie_posortowana_dluga2[i] = n;
        odwrotnie_posortowana_dluga3[i] = n;
    }

    // sortowanie i mierzenie czasu dla krotkiej

    // bubble sort
    start = std::chrono::high_resolution_clock::now();
    bubbleSort(odwrotnie_posortowana_krotka1, 100);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Czas sortowania (krotka / odwrotnie posortowana / bubble sort): " << duration.count() << "ms" << endl;

    // quick sort
    start = std::chrono::high_resolution_clock::now();
    quickSort(odwrotnie_posortowana_krotka2, 0, 99);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Czas sortowania (krotka / odwrotnie posortowana / quick sort): " << duration.count() << "ms" << endl;

    // hybrid sort
    start = std::chrono::high_resolution_clock::now();
    hybridSort(odwrotnie_posortowana_krotka3, 0, 99);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Czas sortowania (krotka / odwrotnie posortowana / hybrid sort): " << duration.count() << "ms" << endl;

    cout << "\n\n";

    // sortowanie i mierzenie czasu dla dlugiej

    // bubble sort
    start = std::chrono::high_resolution_clock::now();
    bubbleSort(odwrotnie_posortowana_dluga1, 10000);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Czas sortowania (dluga / odwrotnie posortowana / bubble sort): " << duration.count() << "ms" << endl;

    // quick sort
    start = std::chrono::high_resolution_clock::now();
    quickSort(odwrotnie_posortowana_dluga2, 0, 9999);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Czas sortowania (dluga / odwrotnie posortowana / quick sort): " << duration.count() << "ms" << endl;

    // hybrid sort
    start = std::chrono::high_resolution_clock::now();
    hybridSort(odwrotnie_posortowana_dluga3, 0, 9999);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Czas sortowania (dluga / odwrotnie posortowana / hybrid sort): " << duration.count() << "ms" << endl;

    // ---------- TABLICA WYPELNIONA LOSOWYMI WARTOSCIAMI ----------
}
