#include <iostream>
#include <fstream>
#include <unistd.h>

const int sizeOfGraph = 8;

using namespace std;

void printTable(int size, int* tab) {
    // printowanie oznaczen pol
    cout << "|";
    for (int i = 0; i < size; i++) {
        cout << " " << i << " |";
    }
    cout << endl;

    // printowanie linii poziomej
    for (int i = 0; i < (size*4 + 2); i++) {
        cout << "-";
    }
    cout << "\n| ";

    // printowanie zawartosci i przerw pionowych
    for (int i = 0; i < size; i++) {
        cout << tab[i] << " | ";
    }
    cout << endl << endl;
}


// --------------- Struktury -----

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

    void addH(int f, int t, int d) {
        NodeLE* newNode = new NodeLE(f, t, d);

        newNode->next=head;
        head = newNode;
    }

    void removeH() {
        NodeLE* temp = head;
        head = head->next;

        delete temp;
    }
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

ListLE* LNtoLEbezPowtorzen(Node** LN, int size) {
    ListLE* LE = new ListLE();

    // to po to zeby nie musiec uwzgledniac przypadku kiedy w liscie jeszcze nic nie ma i musimy dac na heada, na koncu
    // trzeba usunac
    LE->head = new NodeLE(0, 0, 0);

    NodeLE* last = LE->head;

    // przechodzenie po kazdym elemencie LN i dodawanie go do Listy LE, ale unikajac powtorzen
    for (int i = 0; i < size; i++) {
        Node* curr = LN[i];

        while (curr->next) {
            int currnextV = curr->next->vertex;
            int distance = curr->next->distance;
            // if sprawdza czy 'i' ktore aktualnie sprawdzamy nie powtorzylo sie juz gdzies wczesniej w sprawdzanych
            // punktach (ciezko to wyjasnic w tekscie)
            if (curr->next->vertex > i) {
                last->next = new NodeLE(i, curr->next->vertex, curr->next->distance);
                last = last->next;
            }
            curr = curr->next;

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

ListLE* copyLE(ListLE* LE) {
    ListLE* newLE = new ListLE();

    NodeLE* curr = LE->head;

    while (curr) {
        newLE->addH(curr->from, curr->to, curr->distance);

        curr = curr->next;
    }

    return newLE;
}

// sortowanie listy krawedzi (potrzebne do kruskala) (pracuje na kopii zeby oryginalnej listy nie ruszac)
ListLE* sortLE(ListLE* LE) {
    if (LE->head == nullptr || LE->head->next == nullptr) {
        // nie sortujemy tablicy ktora ma jeden badz 0 elementow
        return LE;
    }

    // wartownik zeby uproscic zamienianie miejscami
    LE->addH(-1, -1, -1);

    NodeLE* end = nullptr;
    bool swapped;

    do {
        swapped = false;
        NodeLE* p = LE->head;

        while (p->next && p->next->next != end) {
            NodeLE* K = nullptr;

            int a = p->next->distance;
            int b = p->next->next->distance;

            if (p->next->distance > p->next->next->distance) {
                swapped = true;

                NodeLE* temp = p->next;
                p->next = temp->next;
                temp->next = p->next->next;
                p->next->next = temp;

                K = p;
            }

            p = p->next;
        }

        end = p->next;
    } while (swapped);

    // usuwamy wartownik
    LE->removeH();

    return LE;
}


// --------------- Algorytm Prima ---------------

ListLE* prim(Node** LN, int size, int start)  {
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

        // cout << vertexFrom << " -> " << vertexTo << ", "; // pomocnicze printowanie aktualnie wybranego polaczenia

        // tu trzeba dodac do lsity sasiedztwa
        NodeLE* newNode = new NodeLE(vertexFrom, vertexTo, minimalDistance);
        last->next = newNode;
        last = last->next;

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

ListLE* kruskal(Node** LN, int size) {

    ListLE* LER = new ListLE(); // LE, ktora zwrocimy

    // najpierw trzeba zadbac o to zeby w LN nie bylo powtorzen i zamienic ja na LE
    ListLE* LE = LNtoLEbezPowtorzen(LN, size);

    ListLE* copy = copyLE(LE);   // kopiowanie zeby nie pracowac na oryginalnej liscie
    copy = sortLE(copy);      // sortowanie

    // generowanie tablicy forest i wypelnianie jej zerami (0 oznacza ze punkt nie jest uwzgledniony w zadnym lesie)
    // dodatkowo od razu inicjuje zmienna ktora bedzie iteratorem lasow
    // nie robie tablicy kolorow bo w tym przypadku wykorzystam do tego tablice lasow i tym samym zuzyje mniej pamieci
    // jesli w tablicy lasow punkt ma wartosc jakakolwiek inna niz 0 to to samo co jakby w tablicy kolorow mial 1

    int forestIterator = 1;
    int forest[size];
    for (int i = 0; i < size; i++) {
        forest[i] = 0;
    }

    NodeLE* currLE = copy->head;

    while (currLE) {

        printTable(size, forest);

        // zapisywanie wskaznika currLE do nowej zmiennej
        NodeLE* node = currLE;
        // 'wypiecie' currLE z listy i ustawienie heada (i currLE) jako nastepny
        copy->head = copy->head->next;
        currLE = copy->head;
        node->next = nullptr;
        // mozemy to zrobic na poczatku bo pozniej i tak w sumie musimy go albo przepiac do innej listy albo usunac

        int v1 = node->from;
        int v2 = node->to;

        // sprawdzam czy krawedz currLE ma dwa biale wierzcholki, a jezeli tak to dolaczam ja do nowego drzewa i do LER
        // dodatkowo musze zmienic kolor obu jej wierzcholkow na 'szary' i zwiekszyc iterator o 1
        if (forest[v1] == 0 && forest[v2] == 0) {
            forest[v1] = forest[v2] = forestIterator;
            forestIterator++;


            // dodawanie przed glowe do LER
            NodeLE* temp = LER->head;
            LER->head = node;
            node->next = temp;

            cout << "dwa biale [" << v1 << "]->[" << v2 <<"]" << endl;
        }

        // jesli krawedz currLE ma tylko jeden bialy wierzcholek to dolaczana jest do istniejacego juz lasu i LER
        // dodatkowo zmieniam kolor drugiego wierzcholka na szary (nie robie tego bo nie korzystam z tablicy kolorow)
        else if (forest[v1] != 0 && forest[v2] == 0) {
            forest[v2] = forest[v1];   // zmiana lasu v2 na ten do ktorego jest przypisany v1

            // dodawanie przed glowe do LER
            NodeLE* temp = LER->head;
            LER->head = node;
            node->next = temp;

            cout << "jeden bialy [" << v1 << "]->[" << v2 <<"]" << endl;
        }

        else if (forest[v1] == 0 && forest[v2] != 0) {
            forest[v1] = forest[v2];   // zmiana lasu v1 na ten do ktorego jest przypisany v2

            // dodawanie przed glowe do LER
            NodeLE* temp = LER->head;
            LER->head = node;
            node->next = temp;
            cout << "jeden bialy [" << v1 << "]->[" << v2 <<"]" << endl;
        }

        // jesli krawedz currLE ma dwa szare wierzcholk i NALEZA ONE DO DWOCH ROZNYCH LASOW to lacze je w jeden i do LER
        else if (forest[v1] != forest[v2] && forest[v1] != 0 && forest[v2] != 0) {
            // wybieram mniejszy z lasow (kwestia kosmetyczna tylko i wylacznie)
            int smaller = forest[v1] > forest[v2] ? forest[v2] : forest[v1];
            int bigger = forest[v1] < forest[v2] ? forest[v2] : forest[v1];

            // chcac 'polaczyc lasy' tak naprawde po prostu zmieniam wszystkie wartosci forest[v1] na forest[v2] lub
            // forest[v2] na forest[v1]

            for (int i = 0; i < size; i++) {
                if (forest[i] == bigger) {
                    forest[i] = smaller;
                }
            }

            // dodawanie przed glowe do LER
            NodeLE* temp = LER->head;
            LER->head = node;
            node->next = temp;

            cout << "dwa szare i rozne drzewa [" << v1 << "]->[" << v2 <<"]" << endl;
        }

        // jesli krawedz currLE ma dwa szare wierzcholki i naleza one do TEGO SAMEGO LASU to jest ona odrzucana
        else if (forest[v1] == forest[v2] && forest[v1] != 0 && forest[v2] != 0) {
            delete node;
            cout << "dwa szare i to samo drzewo [" << v1 << "]->[" << v2 <<"]" << endl;
        }
    }

    return LER;
}

int main() {
    // MN w oparciu o plik
    int** MN = fileToMN("graf.txt");

    // LN w oparciu o MN
    Node** LN = MNtoLN(MN, sizeOfGraph);
    // LE w oparciu o LN
    ListLE* LE = LNtoLE(LN, sizeOfGraph);

    // wyszukiwanie najkrotszej drogi przechodzacej przez kazdy punkt
    // prim
    ListLE* algorytmPrima = prim(LN, sizeOfGraph, 2);
    printLE(algorytmPrima);

    // kruskal
    ListLE* algorytmKruskala = kruskal(LN, sizeOfGraph);
    printLE(algorytmKruskala);
}
