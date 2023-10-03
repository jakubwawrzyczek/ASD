#include <iostream>
using namespace std;

class Node {
    friend class List;

    int data;
    Node* next;

public:
    Node(int d) {
        this->data = d;
        this->next = nullptr;
    }

    int getData() const;
};

int Node::getData() const {
    return Node::data;
}

// // // // // // // //

class List {
    Node* head = nullptr;

public:
    void insertNode();
};

void List::insertNode() {
    
}

int main() {

    Node node1 = Node(1);
    Node node2 = Node(2);
    Node node3 = Node(3);
    Node node4 = Node(4);
    Node node5 = Node(5);

}
