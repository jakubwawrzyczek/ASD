#ifndef ASD_LIST_H
#define ASD_LIST_H
#include "Node.h"

class List {


public:
    Node* head = nullptr;
    Node* tail = nullptr;
    List() { head = nullptr; }
    List(Node* newNode) { head = newNode; }

    // wstawianie elementow
    void addT(int newV);
    void addH(int newV);
    void add(Node* &p, int newV);
    void addAfter(int v, int newV);
    void duplicateEveryValue();
    void zad3();
    void duplicateEntireList();

    // usuwanie elementow
    void removeNext(Node* &p);
    void removeEvery2ndElement();
    void removeEvenElements();

    // lab3
    void lab31(); // zamien min z max
    void lab32(int x); // zamien element x z nastepnym
    void lab33(); // zamien co drugi element
    void lab34(); // zamien pierwszy z ostatnim
    void lab35();

    // lab4
    void lab41(int newV);   // wstawianie do posortowanej listy
    void lab42(int x, int y);   // ??
    void lab43();   // ??

    // dzielenie listy
    void split1(Node* &head, Node* &head1, Node* &head2);
    void split2(Node* &head, Node* &head1, Node* &head2);
    void split3(Node* &head, Node* &head1, Node* &head2);
    // pierwsza lista ma elementy a dwie pozostale sa puste
    // po wykonaniu pierwsza lista jest pusta a dwie pozostale maja po 1/2 elementow

    // laczenie listy
    void merge(Node* &head, Node* &head1, Node* &head2);
    // polaczyc dwie posortowane listy

    void printList();
};


#endif //ASD_LIST_H
