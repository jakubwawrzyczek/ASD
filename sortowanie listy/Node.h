#ifndef ASD_NODE_H
#define ASD_NODE_H

class Node {
    friend class List;

    int val;
    int valX;
    int valY;
    Node* next;

public:
    Node(int v) {
        this->val = v;
        this->next = nullptr;
    }

    Node(int x, int y) {
        this->valX = x;
        this->valY = y;
        this->next = nullptr;
    }
};


#endif //ASD_NODE_H
