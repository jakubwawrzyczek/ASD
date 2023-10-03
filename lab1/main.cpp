#include <iostream>
using namespace std;

struct Osoba {
public:
    Osoba(string i, string n, int w) {
        this->imie = i;
        this->nazwisko = n;
        this->wiek = w;

    }
private:
    // dane
    string imie;
    string nazwisko;
    int wiek{};

    // wskaznik na nastepna osobe
    struct Osoba* nastepna_osoba{};
};



int main() {



}
