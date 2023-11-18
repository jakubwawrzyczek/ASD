#include <iostream>
using namespace std;
#define COUNT 10

struct Node {
    Node* L = nullptr; // na lewo
    Node* R = nullptr; // na prawo
    Node* P = nullptr; // rodzic
    int val;
};

// LAB1
void insert(Node* &root, int newValue, Node* parent = nullptr) {
    // sprawdzamy czy w korzeniu jest juz jakas wartosc, jesli nie to wstawiamy tam
    if (!root) {
        Node* newNode = new Node;
        newNode->P = parent;
        newNode->val = newValue;
        root = newNode;
        return;
    }

    //jezeli nowa wartosc jest wieksza niz wartosc korzenia to:
    if (root->val <= newValue) {
        insert(root->R, newValue, root);
    }

    //jezeli nowa wartosc jest mniejsza niz wartosc korzenia to przechodzimy do lewego syna
    else {
        insert(root->L, newValue, root);
    }
}

void inOrder(Node* root)
{
    if (root->L) {
        inOrder(root->L);
    }
    cout << root->val << " ";
    if (root->R) {
        inOrder(root->R);
    }
}

Node* search(Node* root, int searchedVal) {

    // tu cos nie dziala bo jak nie ma wartosci w drzewie to zwraca drugi element po lewej
//    if (!root) {return nullptr;}
//
//    while (root) {
//        if (root->val == searchedVal) {
//            return root;
//        } else if (searchedVal > root->val) {
//            root = root->R;
//        } else if (searchedVal < root->val) {
//            root = root->L;
//        }
//    }

// rekurencyjnie
    if (!root) {
        cout << "Nie znaleziono podanej wartosci" << endl;
        return nullptr;
    } else if (root->val == searchedVal) {
        return root;
    }

    if (searchedVal >= root->val) {
        return search(root->R, searchedVal);
    } else {
        return search(root->L, searchedVal);
    }

}

Node* min(Node* root) {
    while (root->L) {
        root = root->L;
    }
    return root;

// rekurencyjnie
//    if(!root->L) {
//        return root;
//    } else {
//        return min(root->L);
//    }
}

Node* max(Node* root) {
    while (root->R) {
        root = root->R;
    }
    return root;

// rekurencyjnie
//    if(!root->R) {
//        return root;
//    } else {
//        return max(root->R);
//    }
}

Node* predecessor(Node* root, int val) {
    Node* element = search(root, val);

    if (element == min(root)) {
        cout << "Ten element nie ma poprzednika" << endl;
        return nullptr;
    }

    // czy ma lewe poddrzewo, jesli tak to szukamy w nim najwiekszej wartosci
    if (element->L) {return max(element->L);}

    // jesli nie ma lewego poddrzewa i jest lewym synem to przechodzimy do jego rodzica i idziemy do gory az element bedzie
    // prawym synem swojego rodzica i zwracamy go
    else if (!element->L && element == element->P->L) {
        while (element == element->P->L) {
            element = element->P;
        }
        return element->P;
    }

    // jesli nie ma lewego poddrzewa i jest prawym synem to zwracamy rodzica
    else if (!element->L && element == element->P->R) {
        return element->P;
    }
}

Node* successor(Node* root, int val) {
    Node* element = search(root, val);

    // jesli element jest maksymalnym z drzewa to nie ma nastepnika wiec zwracamy jego samego
    if (element == max(root)) {
        cout << "Ten element nie ma nastepnika" << endl;
        return nullptr;
    }

    // czy ma prawe poddrzewo, jesli tak to szukamy w nim najmniejszej wartosci
    if (element->R) {return min(element->R);}

    // jesli nie ma prawego poddrzewa i jest prawym synem to przechodzimy do jego rodzica i idziemy do gory az element bedzie lewym
    // synem swojego rodzica i zwracamy go
    else if (!element->R && element == element->P->R) {
        while (element == element->P->R) {
            element = element->P;
        }
        return element->P;
    }

    // jesli nie ma prawego poddrzewa i jest lewym synem to zwracamy rodzica
    else if (!element->R && element == element->P->L) {
        return element->P;
    }
}

// LAB2
void deleteNode(Node* root, int nodeVal) {
    Node* element = search(root, nodeVal);

    if (!element) { return; }

    // zapisuje sobie czy ma danego syna zeby pozniej tego nie sprawdzac za kazdym razem w warunkach
    bool rightSon = (element->R) != nullptr;
    bool leftSon = (element->L) != nullptr;

    // pierwszy przypadek — wezel nie ma zadnego syna
    if (!rightSon && !leftSon) {
        cout << "Brak synow" << endl; // sprawdzenie, czy dalem poprawne warunki

        // no i teraz chcemy po prostu to usunac, nic pod nim nie ma wiec nic nie musimy przenosic

        // jezeli element jest prawym synem swojego rodzica to...
        if (element == element->P->R) { element->P->R = nullptr; }

        // jezeli element jest lewym synem swojego rodzica to...
        else if (element == element->P->L) { element->P->L = nullptr; }

        // jezeli tu przejdzie to mamy blad wiec printuje error albo obsluguje go jakos
        else {
            cout << "Blad w instrukcji warunkowej sprawdzajacej czy element jest prawym czy lewym synem, prawdopodobnie "
                    "zaburzona zostala struktura drzewa";}

        // no i na koniec po prostu usuwam tego node'a
        delete element;
    }

    // drugi przypadek — wezel ma tylko jednego syna
    else if ((rightSon && !leftSon) || (leftSon && !rightSon)) {
        cout << "Jeden syn" << endl; // sprawdzenie, czy dalem poprawne warunki

        // teraz musimy go znowu usunac, ale najpierw zmieniamy wskaznik ojca Elementu na syna elementu

        Node* elementSon = (element->R) ? element->R : element->L; // syn elementu ktory usuwamy

        // jezeli element jest prawym synem swojego rodzica to zapisujemy syna elementu do prawego syna rodzica elementu
        if (element == element->P->R) { element->P->R = elementSon; }

        // jezeli element jest lewym synem swojego rodzica to zapisujemy syna elementu do lewego syna rodzica elementu
        else if (element == element->P->L) { element->P->L = elementSon; }

        // jezeli tu przejdzie to mamy blad wiec printuje error albo obsluguje go jakos
        else {
            cout << "Blad w instrukcji warunkowej sprawdzajacej czy element jest prawym czy lewym synem, prawdopodobnie "
                    "zaburzona zostala struktura drzewa";}

        // no i na koniec po prostu usuwam tego node'a
        delete element;
    }

    // trzeci przypadek — wezel ma obu synow
    else {
        cout << "Dwoch synow" << endl; // sprawdzenie, czy dalem poprawne warunki

        // zapisujemy wskaznik do nastepnika
        Node* successorPointer = successor(root, element->val);

        // sprawdzamy synow nastepnika (moze miec maksymalnie jednego wiec wystarczy nam jedna zmienna przetrzymujaca to
        Node* successorSon = nullptr;

        if (successorPointer->R) { successorSon = successorPointer->R; } // jesli ma prawego syna to zapisujemy go w zmiennej przechowujacej syna
        else if (successorPointer->L) { successorSon = successorPointer->L; } // jesli ma lewego syna to zapisujemy go w zmiennej przechowujacej syna

        // jezeli nastepnik nie ma synow to po prostu zastepujemy wartosc wezla ktory usuwamy wartoscia nastepnika a ten
        // usuwamy
        if (!successorSon) {
            // zastepujemy wartosc
            element->val = successorPointer->val;

            // nie musimy sprawdzac ktorym synem swojego rodzica jest nastepnik bo jesli bylby prawym to nie bylby nastepnikiem
            // usuwamy go
            successorPointer->P->L = nullptr;

            delete successorPointer;

        }

        // jezeli nastepnik ma jednego syna to aby nie dawac zbednych polecen zmieniamy wartosc elementu ktory usuwamy na
        // taka jaka ma nastepnik a pozniej w jego miejsce wstawiamy jego syna i usuwamy nastepnik
        else {
            // zastepujemy wartosc
            element->val = successorPointer->val;

            // nie musimy sprawdzac ktorym synem swojego rodzica jest nastepnik bo jesli bylby prawym to nie bylby nastepnikiem
            // usuwamy go
            Node* successorParentPointer = successorPointer->P;

            successorPointer->P->L = successorPointer->P;

            delete successorPointer;

        }
    }
}

void deleteLeaves(Node* root) {

}

void rotate(Node* &root, string side) {
    if (side == "R") {
        // jezeli nie ma prawego syna to nie obrocimy w prawo
        if (!root->R) return;

        if (root->R->L) {
            // zapisuje aktualnego lewego syna przyszlego roota
            Node* temp = root->R->L;

            // obecny root staje sie lewym synem przyszlego roota
            root->R->L = root;

            // prawy syn obecnego roota zostaje nowym rootem
            root = root->R;

            // ustawiam parentow zeby wszystko sie zgadzalo
            root->P = nullptr;
            root->L->P = root;
            temp->P = root->L;

            // lewy syn nowego roota idzie jako prawy syn starego roota
            root->L->R = temp;
        } else {
            root->R->L = root;
            root = root->R;
            root->L->P = root;
            root->P= nullptr;
            root->L->R = nullptr;
        }

    } else if (side == "L") {
        

    } else {
        cout << "Niepoprawna wartosc zmiennej side, wybierz \"L\" lub \"R\"" << endl;
    }
}

// It does reverse inorder traversal
void print2DUtil(Node* &root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->R, space);

    // Print current node after space
    // count
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->val << "\n";

    // Process left child
    print2DUtil(root->L, space);
}

// Wrapper over print2DUtil()
void print2D(Node* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}


int main() {

    Node* root = nullptr;

    insert(root, 10);
    insert(root, -15);
    insert(root, 30);
    insert(root, -30);
    insert(root, 0);
    insert(root, 20);
    insert(root, 60);
    insert(root, 15);
    insert(root, 26);
    insert(root, 50);
    insert(root, 80);
    insert(root, 24);

    print2D(root);
    rotate(root, "R");
    cout << "\n\n---------------------------------------\n\n";

    rotate(root, "R");
    cout << "\n\n---------------------------------------\n\n";

    rotate(root, "R");
    cout << "\n\n---------------------------------------\n\n";

    print2D(root);
//    inOrder(root);
}
