#include <iostream>
#include <fstream>

using namespace std;

int** readFromFile(string path) {
    fstream read;
    int size;

    read.open(path);
    read >> size;

    int** M = new int*[size];

    for (int i = 0; i < size; i++)
        M[i] = new int[size];

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            read  >> M[i][j];


    return M;
}

int main() {
    int** M = readFromFile("graf.txt");

    cout << M[0][0];

}
