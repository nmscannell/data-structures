#ifndef INTLIST_H
#define INTLIST_H

class IntList {
  class Node {
 //   int data;
   // Node *next;

    public:
      int data;
      Node *next;
      Node();
      Node(int &d, Node *n);
    };

  int manyItems;
  Node *head;
  
  public: 
    IntList();
    ~IntList();
    int size();
    bool isEmpty();
    int front();
    bool add(int &elem);
    void remove(int &elem);
    void clear();
    void reverse();
    void display();
};

#endif
