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


    // ------------------------------------ USUWANIE ELEMENTOW ------------------------------------
    void removeH();                     // Usuwanie pierwszego elementu z listy
    void removeT();                     // Usuwanie ostatniego elementu z listy
    void removeNext(Node* &pointer);    // Usuwanie nastepnika danego wskaznika w liscie
    void removeByValue(int v);          // Usuwanie elementu o podanej wartosci

    // ------------------------------------ LAB 2 ------------------------------------
    void addAfter(int v, int newV);     // Dodawanie elementu po podanej wartosci
    void lab2zad2();    // Duplikowanie kazdego elementu
    void lab2zad3();    // Kazdy element w liscie wystepuje tyle razy ile wynosi jego wartosc
    void lab2zad4();    // Duplikowanie calej listy (Dodawanie kopii listy na koniec)
    void lab2zad5();    // Usuwanie co drugiego elementu z listy
    void lab2zad6();    // Usuwanie kazdego elementu ktorego wartosc jest liczba parzysta


    // ------------------------------------ LAB 3 ------------------------------------
    void lab31();           // zamien min z max
    void lab32(int x);      // zamien element x z nastepnym
    void lab33();           // zamien co drugi element
    void lab34();           // zamien pierwszy z ostatnim
    void lab35();


    // ------------------------------------ LAB 4 ------------------------------------
    void lab41(int newV);       // wstawianie do posortowanej listy
    void lab42(int x, int y);   // ??
    void lab43();               // ??


    // dzielenie listy
    void split1(Node* &head, Node* &head1, Node* &head2);
    void split2(Node* &head, Node* &head1, Node* &head2);
    void split3(Node* &head, Node* &head1, Node* &head2);
    // pierwsza lista ma elementy a dwie pozostale sa puste
    // po wykonaniu pierwsza lista jest pusta a dwie pozostale maja po 1/2 elementow


    // laczenie listy
    void merge(Node* &head, Node* &head1, Node* &head2);
    // polaczyc dwie posortowane listy
};


#endif //ASD_LIST_H
