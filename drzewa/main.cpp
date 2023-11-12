//#include <bits/stdc++.h>

#include <iostream>
using namespace std;
#define COUNT 10

struct Node {
    Node* L = nullptr; // na lewo
    Node* R = nullptr; // na prawo
    Node* P = nullptr; // rodzic
    int val;
};

void insert(Node* &root, int newValue, Node* parent = nullptr) {
    // sprawdzamy czy w korzeniu jest juz jakas wartosc, jesli nie to wstawiamy tam
    if (!root) {
        Node* newNode = new Node;
        newNode->P = parent;
        newNode->val = newValue;
        root = newNode;
        return;
    }

    //jezeli nowa wartosc jest wieksza niz wartosc korzenia to:
    if (root->val <= newValue) {
        insert(root->R, newValue, root);
    }

    //jezeli nowa wartosc jest mniejsza niz wartosc korzenia to przechodzimy do lewego syna
    else {
        insert(root->L, newValue, root);
    }
}

void inOrder(Node* root)
{
    if (root->L) {
        inOrder(root->L);
    }
    cout << root->val << " ";
    if (root->R) {
        inOrder(root->R);
    }
}

Node* search(Node* root, int searchedVal) {
    if (!root) {return nullptr;}

    while (root) {
        if (root->val == searchedVal) {
            return root;
        } else if (searchedVal > root->val) {
            root = root->R;
        } else if (searchedVal < root->val) {
            root = root->L;
        }
    }

// rekurencyjnie
//    if (!root) {
//        cout << "Nie znaleziono podanej wartosci" << endl;
//        return nullptr;
//    } else if (root->val == searchedVal) {
//        return root;
//    }
//
//    if (searchedVal >= root->val) {
//        return search(root->R, searchedVal);
//    } else {
//        return search(root->L, searchedVal);
//    }

}

Node* min(Node* root) {
    while (root->L) {
        root = root->L;
    }
    return root;

// rekurencyjnie
//    if(!root->L) {
//        return root;
//    } else {
//        return min(root->L);
//    }
}

Node* max(Node* root) {
    while (root->R) {
        root = root->R;
    }
    return root;

// rekurencyjnie
//    if(!root->R) {
//        return root;
//    } else {
//        return max(root->R);
//    }
}

Node* poprzednik(Node* root, int val) {
    Node* element = search(root, val);

    if (element == min(root)) {
        cout << "Ten element nie ma poprzednika" << endl;
        return nullptr;
    }

    // czy ma lewe poddrzewo, jesli tak to szukamy w nim najwiekszej wartosci
    if (element->L) {return max(element->L);}

    // jesli nie ma lewego i jest lewym synem to przechodzimy do jego rodzica i idziemy do gory az element bedzie prawym
    // synem swojego rodzica i zwracamy go
    else if (!element->L && element == element->P->L) {
        while (element == element->P->L) {
            element = element->P;
        }
        return element->P;
    }
}

Node* nastepnik(Node* root, int val) {
    Node* element = search(root, val);

    // jesli element jest maksymalnym z drzewa to nie ma nastepnika wiec zwracamy jego samego
    if (element == max(root)) {
        cout << "Ten element nie ma nastepnika" << endl;
        return nullptr;
    }

    // czy ma prawe poddrzewo, jesli tak to szukamy w nim najmniejszej wartosci
    if (element->R) {return min(element->R);}

    // jesli nie ma prawego i jest prawym synem to przechodzimy do jego rodzica i idziemy do gory az element bedzie lewym
    // synem swojego rodzica i zwracamy go
    else if (!element->R && element == element->P->R) {
        while (element == element->P->R) {
            element = element->P;
        }
        return element->P;
    }

    // jesli nie ma prawego i jest lewym synem to zwracamy rodzica
    else if (!element->R && element == element->P->L) {
        return element->P;
    }
}

// It does reverse inorder traversal
void print2DUtil(Node* root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->R, space);

    // Print current node after space
    // count
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->val << "\n";

    // Process left child
    print2DUtil(root->L, space);
}

// Wrapper over print2DUtil()
void print2D(Node* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}


int main() {

    Node* root = nullptr;

    insert(root, 50);
    insert(root, 17);
    insert(root, 72);
    insert(root, 12);
    insert(root, 23);
    insert(root, 54);
    insert(root, 76);
    insert(root, 9);
    insert(root, 14);
    insert(root, 19);
    insert(root, 24);
    insert(root, 67);
    insert(root, 18);


//    print2D(root);
//    cout << search(root, 50)->val << endl;
//    cout << min(root)->val << endl;
    cout << poprzednik(root, 17)->val << endl;
//    inOrder(root);
}
