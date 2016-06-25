#include "node.h"
using  namespace std;

Node::Node(char value, int freq) {
        this->value = value;
        this ->freq = freq;
        left = 0;
        right = 0;
}

Node :: Node(Node *left, Node *right) {
    freq = left->freq + right->freq;
    value = 0;
    this->left = left;
    this->right = right;
}
