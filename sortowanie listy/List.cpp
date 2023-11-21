#include "List.h"
#include "iostream"

using namespace std;

// Wypisuje wszystkie elementy z listy
void List::printList() {
    cout << "\nhead: " << head->val << " tail: " << tail->val << endl;

    if (!head) {
        cout << "Lista jest pusta!";
    }

    else {
        cout << "H ";

        Node* temp = head;
        while (temp) {
            cout << "-> [" << temp->val << "] ";
            temp = temp->next;
        }
        cout << "-> NULL"<< endl;
    }
}


// ------------------------------------ DODAWANIE ELEMENTOW ------------------------------------
// Dodawanie elementu na poczatek listy
void List::addH(int newV) {
    Node* newNode = new Node(newV);

    newNode->next=head;
    head = newNode;

    if (tail == nullptr) {
        tail = newNode;
    }
}

// Dodawanie elementu na koniec listy
void List::addT(int newV) {
    Node* newNode = new Node(newV);
    if(!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = tail->next;
    }
}

// Dodawanie elementu po elemencie do ktorego przekazany jest wskaznik
void List::add(Node* &p, int newV) {
    Node* newNode = new Node(newV);

    newNode->next = p->next;
    p->next = newNode;
}


// ------------------------------------ USUWANIE ELEMENTOW ------------------------------------
// Usuwanie pierwszego elementu z listy
void List::removeH() {
    Node* temp = head;
    head = head->next;

    delete temp;
}

// Usuwanie ostatniego elementu z listy
void List::removeT() {
    Node* p = head;
    Node* temp = tail;

    while (p->next != tail) {
        p = p->next;
    }

    tail = p;
    p->next = nullptr;
    delete temp;
}

// Usuwanie nastepnika danego wskaznika w liscie
void List::removeNext(Node *&p) {
    Node* temp = p->next;
    p->next = p->next->next;

    delete temp;
}

// Usuwanie elementu o podanej wartosci
void List::removeByValue(int v) {
    addH(0);
    Node* p = head;

    while(p->next && p->next->val != v) {
        p = p->next;
    }

    if (p->next == nullptr) {
        cout << "Nie znaleziono podanej wartości." << endl;
    } else {
        Node* temp = p->next;
        p->next = p->next->next;
        delete temp;

        Node* temp2 = head;
        head = head->next;
        delete temp2;
    }
}
    // ------------------------------------- SORTOWANIE LISTY -------------------------------------
    void List::bubbleSort() {
    printList(); // kontrolne printowanie
    addH(-123456789); // wartownik
    //--

    bool moved = true;
    Node* T = nullptr;

    while(moved) {
        moved = false;
        Node* p = head;

        while (p->next->next != T) {
            Node* K = nullptr;

            if (p->next->val > p->next->next->val) {
                moved = true;

                Node* temp = p->next;
                p->next = temp->next;
                temp->next = p->next->next;
                p->next->next = temp;

                K = p;
            }

            T = K;
            p = p->next;
        }
    }

    //--
    removeH(); // usuwanie wartownika
    printList(); // printowanie zeby zobaczyc co stalo sie z lista
}
