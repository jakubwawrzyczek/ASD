#include <iostream>
#include <fstream>
#include <unistd.h>

const int sizeOfGraph = 8;

using namespace std;

class Node {
    friend class List;

public:
    Node(int v, int d) {
        this->vertex = v;
        this->distance = d;
        this->next = nullptr;
    }

    int vertex;
    int distance;
    Node* next;
};


class NodeLE {
public:
    NodeLE(int f, int t, int d) {
        this->from = f;
        this->to = t;
        this->distance = d;
        this->next = nullptr;
    }

    int from;
    int to;
    int distance;
    NodeLE* next = nullptr;
};

class ListLE {
public:
    NodeLE* head = nullptr;
    ListLE() { head = nullptr; }
    ListLE(NodeLE* newNode) { head = newNode; }
};

// --------------- Macierz sasiedztwa ---------------

int** fileToMN(string path) {
//    tworzymy tablice ktora zawiera odleglosci pomiedzy punktami, ktore sa reprezentowane jako numer
//    elementu danej tablicy, np:
//
//  punkt 0   1   2   3   4
//      0 0   1   2   1   0
//      1 1   0   3   4   6
//      2 2   3   0   1   1
//      3 1   4   1   0   1
//      4 0   6   1   1   0
//
//
//      zakladajac ze tablica to MN to wartosc MN[0][1] bedzie reprezentowala odleglosc pomiedzy
//      punktem 0 i 1
//
//      dodatkowo M[0][1] i M[1][0] moze sie roznic i wtedy po prostu z punktu 1 do 0 jest inna
//      odleglosc niz z 0 do 1

    fstream read;
    int size;

    read.open(path);
    read >> size;

    int** MN = new int*[size];

    for (int i = 0; i < size; i++)
        MN[i] = new int[size];

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            read  >> MN[i][j];

    return MN;
}

void printMN(int** MN, int size) {
    cout << "Macierz sąsiedztwa: " << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << MN[i][j] << "\t";
        }
        cout << endl;
    }
}

// --------------- Lista sasiedztwa ---------------

Node** MNtoLN(int** MN, int size) {

//    macierz sasiedztwa to tablica zawierajaca odleglosci a tutaj chcemy tablice ktorej numery elementu reprezentuja
//    numer punktu i ten element zawiera punkty ktore maja polaczenia z danym punktem
//
//    jesli w macierzu mamy wartosc 0 to znaczy ze nie ma polaczenia wiec nie dodajemy tego punktu

    Node** LN = new Node*[size];
    for (int i = 0; i < size; i++)
        LN[i] = nullptr;

    // dla kazdego punktu
    for (int i = 0; i < size; i++) {
        LN[i] = new Node(i, 0);
        Node* curr = LN[i];

        // bierzemy drugi punkt
        for (int j = 0; j < size; j++) {
            // a jesli odleglosc miedzy nimi jest wieksza od 0 (czyli istnieje polaczenie)
            if (MN[i][j] > 0) {
                // to dodajemy to polaczenie do tablicy
                // dodaj do LN[i] point rowny j i dystans rowny MN[i][j]

                while (curr->next) {
                    curr = curr->next;
                }

                curr->next = new Node(j, MN[i][j]);
            }

        }
    }
    return LN;
}

Node** LEtoLN(ListLE* LE, int size) {

//    tutaj trzeba przeleciec po kazdym node z listy i sprawdzac 'from' a na podstawie tego dodawac node do LN[from]
//    nie musze sprawdzac czy odleglosc jest >0 bo w LE nie powinno byc takich rzeczy

    cout << "kontrolka";
    Node** LN = new Node*[size];
    for (int i = 0; i < size; i++) {
        LN[i] = new Node(i,0 );
    }

    NodeLE* currLE = LE->head;

    while (currLE) {
        // tutaj za kazdym razem przechodzi od poczatku do ostatniego elementu w LE[i], moznaby to usprawnic bo przy
        // malych danych nie przeszkadza ale przy ogromnych grafach na pewno nie byloby szczegolnie przyjemne
        Node* currLN = LN[currLE->from];

        while (currLN->next) {
            currLN = currLN->next;
        }

        currLN->next = new Node(currLE->to, currLE->distance);

        currLE = currLE->next;
    }

    return LN;
}

void printLN(Node** LN, int size) {
    cout << "Lista sasiedztwa: " << endl;
    cout << "Punkt (numer punktu) -> (numer punktu do ktorego ma polaczenie, odleglosc pomiedzy nimi)" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Punkt " << i;
        Node* curr = LN[i];
        while (curr->next) {
            cout << " -> (" << curr->next->vertex << ", " << curr->next->distance << ")";
            curr = curr->next;
        }
        cout << endl;
    }
}

// --------------- Lista krawedzi ---------------

ListLE* LNtoLE(Node** LN, int size) {
    ListLE* LE = new ListLE();

    // to po to zeby nie musiec uwzgledniac przypadku kiedy w liscie jeszcze nic nie ma i musimy dac na heada, na koncu
    // trzeba usunac
    LE->head = new NodeLE(0, 0, 0);

    NodeLE* last = LE->head;

    // przechodzenie po kazdym elemencie LN i dodawanie go do Listy LE
    for (int i = 0; i < size; i++) {
        Node* curr = LN[i];

        while (curr->next) {
            last->next = new NodeLE(i, curr->next->vertex, curr->next->distance);

            curr = curr->next;
            last = last->next;
        }
    }

    NodeLE* temp = LE->head;
    LE->head = LE->head->next;
    delete temp;
    return LE;
}

ListLE* MNtoLE(int** MN, int size) {
//    chcac zamienic MN na LE musimy przeleciec po calej tablicy uzywajac zmiennych i, j - wtedy:
//
//    from: i,
//    to: j,
//    distace: MN[i][j],
//
//    i kazdy taki punkt dodajemy do LE

    ListLE* LE = new ListLE();
    LE->head = new NodeLE(0, 0, 0);
    NodeLE* last = LE->head;
    // ^ wyjasnione wyzej


    // dla kazdego punktu
    for (int i = 0; i < size; i++) {
        // bierzemy drugi punkt
        for (int j = 0; j < size; j++) {
            // a jesli odleglosc miedzy nimi jest wieksza od 0 (czyli istnieje polaczenie)
            if (MN[i][j] > 0) {
                // to dodajemy to polaczenie do tablicy
                // dodaj do LE nowy node gdzie from=i, to=j, distance=MN[i][j]

                last->next = new NodeLE(i, j, MN[i][j]);
                last = last->next;
            }

        }
    }

    NodeLE* temp = LE->head;
    LE->head = LE->head->next;
    delete temp;
    return LE;
} 

void printLE(ListLE* LE) {
    NodeLE* curr = LE->head;

    cout << "Lista krawedzi: " << endl;

    while (curr) {
        cout << "Od: " << curr->from << ", Do: " << curr->to << ", Odleglosc: " << curr->distance << endl;

        curr = curr->next;
    }
}

// --------------- Algorytm Prima ---------------

ListLE* Prim(Node** LN, int size, int start)  {
    // generowanie tablicy kolorow i wypelnianie jej zerami (wierzcholek startowy od razu jako 1)
    int colorTable[size];
    for (int i = 0; i < size; i++) {
        colorTable[i] = 0;
    }
    colorTable[start] = 1;

    // inicjowanie wynikowej listy krawedzi
    ListLE* LE = new ListLE();
    // to po to zeby nie musiec uwzgledniac przypadku kiedy w liscie jeszcze nic nie ma i musimy dac na heada, na koncu
    // trzeba usunac
    LE->head = new NodeLE(0, 0, 0);
    NodeLE* last = LE->head;

    bool isColorTableFull = false;

    while (!isColorTableFull) {
        // domyslnie na to zeby pozniej pod koniec sprawdzic znowu
        isColorTableFull = true;

        int minimalDistance = 2147483647;
        int vertexFrom = 2147483647;
        int vertexTo = 2147483647;

        for (int i = 0; i < size; i++) {
            if (colorTable[i] == 1) {
                Node* curr = LN[i];
                int f = curr->vertex;

                while (curr->next) {
                    if (curr->next->distance < minimalDistance && colorTable[curr->next->vertex] == 0) {
                        vertexFrom = f;
                        vertexTo = curr->next->vertex;
                        minimalDistance = curr->next->distance;
                    }
                    curr = curr->next;
                }

            }
        }

        
        colorTable[vertexTo] = 1;

        // sprawdzamy czy nie zapelnilismy calej tablicy kolorow
        for (int j = 0; j < size; j++) {
            if (colorTable[j] == 0) {
                isColorTableFull = false;
                break;
            }
        }
    }

    // usuwanie pomocniczego heada
    NodeLE* temp = LE->head;
    LE->head = LE->head->next;
    delete temp;

    // zwracanie wynikowej listy krawedzi
    return LE;
}

// --------------- Algorytm Kruskala ---------------


int main() {
    // MN w oparciu o plik
    int** MN = fileToMN("graf.txt");

    // LN w oparciu o MN
    Node** LN = MNtoLN(MN, sizeOfGraph);
    printLN(LN, sizeOfGraph);

    Prim(LN, sizeOfGraph, 5);

}
