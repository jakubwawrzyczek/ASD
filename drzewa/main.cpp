#include <iostream>
using namespace std;

struct Node {
    Node* L; // na lewo
    Node* R; // na prawo
    Node* P; // rodzic
    int val;
};

void insert(Node* root, int newValue, Node* parent = nullptr) {
    if (!root->val) {
        root->val = newValue;
    } else {
        //jezeli nowa wartosc jest wieksza niz wartosc korzenia to:
        if (root->val <= newValue) {
            //jezeli prawy syn nie istnieje to wstawiamy tam nasza nowa wartosc
            if (!root->R) {
                Node* newSon = new Node;
                newSon->val = newValue;
                newSon->P = root;
                root->R = newSon;
            }
            //jezeli prawy syn juz jest to wywolujemy funkcje jeszcze raz z korzeniem w tym wlasnie synu
            else {
                insert(root->R, newValue, root);
            }
        }

        //jezeli nowa wartosc jest mniejsza niz wartosc korzenia to przechodzimy do lewego syna
        else {
            //jezeli lewy syn nie istnieje to wstawiamy tam nasza nowa wartosc
            if (!root->L) {
                Node* newSon = new Node;
                newSon->val = newValue;
                newSon->P = root;
                root->L = newSon;
            }
            //jezeli lewy syn juz jest to wywolujemy funkcje jeszcze raz z korzeniem w tym wlasnie synu
            else {
                insert(root->L, newValue, root);
            }
        }
    }
}

int main() {

    Node* root = new Node;

    insert(root, 8);
    insert(root, 7);
    insert(root, 10);
    insert(root, 9);

    cout << root->R->L->val;

}
