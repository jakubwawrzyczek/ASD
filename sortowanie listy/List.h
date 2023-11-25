#ifndef ASD_LIST_H
#define ASD_LIST_H
#include "Node.h"

class List {


public:
    Node* head = nullptr;
    List() { head = nullptr; }
    List(Node* newNode) { head = newNode; }

    void printList();   // Wyswietlanie listy
    int getLength();

    // ------------------------------------ DODAWANIE ELEMENTOW ------------------------------------
    void addH(int newV);                // Dodawanie elementu na poczatek listy
    void add(Node* &p, int newV);       // Dodawanie elementu po elemencie do ktorego przekazany jest wskaznik


    // ------------------------------------ USUWANIE ELEMENTOW ------------------------------------
    void removeH();                     // Usuwanie pierwszego elementu z listy
    void removeNext(Node* &pointer);    // Usuwanie nastepnika danego wskaznika w liscie
    void removeByValue(int v);          // Usuwanie elementu o podanej wartosci

    // ------------------------------------- SORTOWANIE LISTY -------------------------------------
    void bubbleSort();
    void sortowaniePrzezWybieranie();
    void combSort();
};


#endif //ASD_LIST_H
