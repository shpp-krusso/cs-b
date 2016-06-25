#ifndef NODE_H
#define NODE_H

class Node
{
public:
  int freq;
  char value;
  Node * left;
  Node * right;
  Node(char value, int freq);
  Node(Node * left, Node * right);
  
};

#endif // NODE_H
