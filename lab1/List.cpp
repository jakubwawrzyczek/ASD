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

// Dodawanie punktu na koniec listy
void List::addPointT(int x, int y) {
    Node* newNode = new Node(x, y);

    if (!head) {
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


// ------------------------------------ LAB 2 ------------------------------------
// Dodawanie elementu po podanej wartosci
void List::addAfter(int v, int newV) {
    Node* p = head;

    while(p && p->val != v) {
        p = p->next;
    }

    if (p) {
        Node* newNode = new Node(newV);

        newNode->next = p->next;
        p->next=newNode;
    } else {cout << "W liscie nie znaleziono podanej wartosci." << endl;}
}

// Duplikowanie kazdego elementu
void List::lab2zad2() {
    Node* p = head;

    while (p) {
        add(p, p->val);
        p = p->next->next;
    }
}

// Kazdy element w liscie wystepuje tyle razy ile wynosi jego wartosc
void List::lab2zad3() {
    Node* p = head;

    while (p) {
        for (int i = 1 ; i < p->val ; i++) {
            add(p, p->val);
            p = p->next;
        }
        p = p->next;
    }
}

// Duplikowanie calej listy (Dodawanie kopii listy na koniec)
void List::lab2zad4() {
    Node* p = head;
    List tempList;

    while (p) {
        tempList.addT(p->val);
        p = p->next;
    }

    tail->next = tempList.head;
    tail = tempList.tail;
}

// Usuwanie co drugiego elementu z listy
void List::lab2zad5() {
    Node* p = head;

    while (p && p->next) {
        removeNext(p);
        p = p->next;
    }
}

// Usuwanie kazdego elementu ktorego wartosc jest liczba parzysta
void List::lab2zad6() {
    Node* p = head;

    while (head->val % 2 == 0) {
        head = head->next;
        p = head;
    }

    while (p && p->next) {
        if (p->next->val % 2 == 0) {
            removeNext(p);
        }
        else {
            p = p->next;
        }
    }
}



// ------------------------------------ LAB 3 ------------------------------------
// Zamien min z max !!!!!!!!!!!!
void List::lab3zad1() {
    addH(0);
    Node* p = head;
    Node* before_min = tail;
    Node* before_max = tail;

    while (p->next) {
        if (p->next->val < before_min->next->val) {
            before_min = p;
        }
        if (p->next->val > before_max->next->val) {
            before_max = p;
        }

        p=p->next;
    }



}

// Zamien element x z nastepnym
void List::lab3zad2(int x) {
    addH(0);    // H -> [1] -> [2] -> [3]   =>   H -> [0] -> [1] -> [2] -> [3]
    Node* p = head;


    // przechodzi po liscie i szuka wartosci x a jesli na nia natrafi to ustawia wskaznik na elemencie poprzednim
    while(p->next && p->next->val != x) {
        p = p->next;
    }

    if(p->next == nullptr) {
        cout << "Wartosc " << x << " nie zostala znaleziona\n";
    }
    else {
        // H -> [0] -> [1] -> [2] -> [3]
        //       ^      ^
        //       p     temp
        //
        // [0] -> [2], [1] -> [3], [2] -> [1]

        Node* temp = p->next;
        p->next = temp->next;
        temp->next = p->next->next;
        p->next->next = temp;

        Node* t2 = head;
        head = head->next;
        delete t2;
    }
}

// Zamien co drugi element
void List::lab3zad3() {
    addH(0);
    Node* p = head;

    while(p) {

        Node* temp = p->next;
        p->next = temp->next;
        temp->next = p->next->next;
        p->next->next = temp;

        if (p->next->next->next && p->next->next->next->next) {
            p = p->next->next;
        }

        else {
            p = nullptr;
        }
    }

    Node* t2 = head;
    head = head->next;
    delete t2;
}

// Zamien pierwszy z ostatnim
void List::lab3zad4() {
    if (!head || !head->next) {
        return;
    } else if(head->next == tail) {
        Node* t1 = head;
        Node* t2 = tail;

        head = t2;
        head->next = t1;
        tail = t1;
        t1->next = nullptr;
        return;
    } else {
        Node* last = head;
        Node* before_last = nullptr;
        while (last->next) {
            before_last = last;
            last = last->next;
        }

        addH(0);

        Node* temp = head->next;
        head->next = last;
        last->next = temp->next;
        before_last->next = temp;
        temp->next = nullptr;
        tail = temp;

        Node* t2 = head;
        head = head->next;
        delete t2;
    }


}

// ------------------------------------ LAB 4 ------------------------------------
// wstawianie do posortowanej listy
void List::lab4zad1(int newV) {
    addH(-999999999);
    Node* p = head;

    // lista w kolejnosci rosnacej
    while (p->next) {
        if (p->next->val >= newV) {
            add(p, newV);
            break;
        } else {p = p->next;}
    }

    if(!p->next) {addT(newV);}

    Node* t2 = head;
    head = head->next;
    delete t2;
}

// zamiana kolejnoscia elementow pomiedzy dwoma elementami
void List::lab4zad2(int x, int y) {

}

// zadanie z okregami
void List::lab4zad3() {

}
