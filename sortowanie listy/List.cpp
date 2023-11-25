#include "List.h"
#include "iostream"

using namespace std;

// Wypisuje wszystkie elementy z listy
void List::printList() {
    if (!head) {
        cout << "Lista jest pusta!";
    }

    else {
        cout << "\nhead: " << head->val << endl;
        cout << "H ";

        Node* temp = head;
        while (temp) {
            cout << "-> [" << temp->val << "] ";
            temp = temp->next;
        }
        cout << "-> NULL"<< endl;
    }
}

int List::getLength() {
    if (!head) {return 0;}

    else {
        int len = 1;
        Node* p = head;

        while (p->next) {
            p = p->next;
            len++;
        }

        return len;
    }


}

// ------------------------------------ DODAWANIE ELEMENTOW ------------------------------------
// Dodawanie elementu na poczatek listy
void List::addH(int newV) {
    Node* newNode = new Node(newV);

    newNode->next=head;
    head = newNode;
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
    }

    void List::sortowaniePrzezWybieranie() {
        printList(); // kontrolne printowanie
        addH(-123456789); // wartownik
        //--

        List tempList;

        while (head->next) {
            // wyszukiwanie maksymalnej wartosci
            Node* beforeMax = head;
            Node* p = head;

            while(p->next) {
                if (p->next->val > beforeMax->next->val) {
                    beforeMax = p;
                }
                p = p->next;
            }

            Node* temp = beforeMax->next;

            // usuwanie z oryginalnej listy
            beforeMax->next = beforeMax->next->next;

            // przenoszenie jej do tymczasowej listy
            temp->next = tempList.head;
            tempList.head = temp;
        }

        //--
        removeH(); // usuwanie wartownika

        head = tempList.head;
        tempList.head = nullptr;
}

void List::combSort() {
    printList();
}
