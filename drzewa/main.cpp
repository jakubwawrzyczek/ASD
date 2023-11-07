#include <iostream>
using namespace std;

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

Node* search(Node* root, int searchedVal) {

}

int main() {

    Node* root = nullptr;

    insert(root, 8);
    insert(root, 7);
    insert(root, 10);
    insert(root, 9);

    cout << root->R->L->val;

//    cout << search(root, 6);


}
