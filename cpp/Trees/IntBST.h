#ifndef INTBST_H
#define INTBST_H

class IntBST {
  class Node {
    int data;
    Node *left, *right, *parent;
    friend class IntBST;

  public:
    Node(int d, Node *l, Node *r, Node *p);
    Node();
    ~Node();
  };

  Node *root;
  int manyItems;

  Node* addHelp(Node *n, int elem);
  Node* removeHelp(Node *n, int elem);
  void displayPreHelp(Node *n);
  void displayPostHelp(Node *n);
  void displayInHelp(Node *n);
  Node* findSucc(Node *n);

public:
  IntBST();
  ~IntBST();
  bool add(int elem);
  bool remove(int elem);
  void displayPre();
  void displayPost();
  void displayInOrder();
  bool contains(int elem);
  void clear();
};

#endif
