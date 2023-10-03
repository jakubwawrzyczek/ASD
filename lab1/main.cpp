#include <iostream>
using namespace std;

struct Osoba {
    // dane
    string imie;
    string nazwisko;
    basic_string<char> wiek{};

    // wskaznik na nastepna osobe
    Osoba* nastepnaOsoba;

    Osoba(string i, string n, int w) {
        this->imie = i;
        this->nazwisko = n;
        this->wiek = w;
    }

    Osoba () {
        nastepnaOsoba = NULL;
    }
};

struct Lista {
    // wskaznik na pierwsza osobe w liscie
    Osoba *pierwszaOsoba = NULL;

    // konstruktor listy
    Lista() {
        pierwszaOsoba = NULL;
    }
    Lista(Osoba* x) {
        pierwszaOsoba = x;
    }

    // dodawanie osoby
    void dodaj(string i, string n, int w) {
        Osoba* nowaOsoba = new Osoba(i, n, w);

        if(pierwszaOsoba == NULL) {
            pierwszaOsoba = nowaOsoba;
            return;
        }

        Osoba* temp = pierwszaOsoba;
        while (temp->nastepnaOsoba == NULL) {
            temp = temp->nastepnaOsoba;
        }
        temp->nastepnaOsoba = nowaOsoba;
    }

    // wyswietlanie listy
    void wyswietlListe() {

    }

};



int main() {



}
