#include "List.h"
#include "iostream"

using namespace std;

void List::add(Node *&p, int newV) {}

// Wypisuje wszystkie elementy z listy
void List::printList() {
    if (!head) {
        cout << "Empty list!";
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

// Dodaje element na poczatek listy
void List::addH(int newV) {
    Node* newNode = new Node(newV);

    newNode->next=head;
    head = newNode;
}

// Dodaje element na koniec listy
void List::addT(int newV) {}

// Dodaje element po wybranej wartosci w liscie
void List::addAfter(int v, int newV) {}