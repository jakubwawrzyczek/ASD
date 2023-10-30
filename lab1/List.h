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
    void addPointT(int x, int y);       // Dodawanie punktu na koniec listy
    void add(Node* &p, int newV);       // Dodawanie elementu po elemencie do ktorego przekazany jest wskaznik


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
    void lab3zad1();            // Zamien min z max
    void lab3zad2(int x);       // Zamien element x z nastepnym
    void lab3zad3();            // Zamien co drugi element
    void lab3zad4();            // Zamien pierwszy z ostatnim
    // Zadanie 5                // Dzielenie listy na 3 rozne sposoby


    // ------------------------------------ LAB 4 ------------------------------------
    void lab4zad1(int newV);        // wstawianie do posortowanej listy
    void lab4zad2(int x, int y);    // zamiana kolejnoscia elementow pomiedzy dwoma elementami
    void lab4zad3();                // zadanie z okregami
};


#endif //ASD_LIST_H
