#ifndef ASD_NODE_H
#define ASD_NODE_H

class Node {
    friend class List;

    int val;
    Node* next;

public:
    Node(int v) {
        this->val = v;
        this->next = nullptr;
    }
};


#endif //ASD_NODE_H
