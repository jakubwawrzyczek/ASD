#ifndef ASD_LIST_H
#define ASD_LIST_H
#include "Node.h"

class List {


public:
    Node* head = nullptr;
    Node* tail = nullptr;
    List() { head = nullptr; }
    List(Node* newNode) { head = newNode; }

    void printList();   // Wyswietlanie listy

    // ------------------------------------ DODAWANIE ELEMENTOW ------------------------------------
    void addH(int newV);                // Dodawanie elementu na poczatek listy
    void addT(int newV);                // Dodawanie elementu na koniec listy
    void add(Node* &p, int newV);       // Dodawanie elementu po elemencie do ktorego przekazany jest wskaznik


    // ------------------------------------ USUWANIE ELEMENTOW ------------------------------------
    void removeH();                     // Usuwanie pierwszego elementu z listy
    void removeT();                     // Usuwanie ostatniego elementu z listy
    void removeNext(Node* &pointer);    // Usuwanie nastepnika danego wskaznika w liscie
    void removeByValue(int v);          // Usuwanie elementu o podanej wartosci
};


#endif //ASD_LIST_H
