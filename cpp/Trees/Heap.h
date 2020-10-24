#ifndef HEAP_H
#define HEAP_H

#include <queue>
#include <stdexcept>
#include <iostream>

template<class T>
class Heap {
  class Node {
    T data;
    Node *left, *right, *parent;
    friend class Heap;

    public:
      Node(const T &d, Node *l=nullptr, Node *r=nullptr, Node *p=nullptr) : data(d), left(l), right(r), parent(p) {}
      ~Node() {
        left = right = parent = nullptr;
      }
    };

  Node *root;
  Node *last;
  int manyItems;
  bool max;

  void bubbleUp(Node *n) {
    if(n == nullptr || n->parent == nullptr) return;
    std::cout << "bubbling up" << std::endl;
    if(max && n->parent->data >= n->data) return;
    if(!max && n->parent->data <= n->data) return;
    T d = n->data;
    n->data = n->parent->data;
    n->parent->data = d;
    bubbleUp(n->parent);
  }

  void bubbleDown(Node *n) {
    if(n == nullptr || n->left == nullptr && n->right == nullptr) return;
    std::cout << "bubbling down" << std::endl;
    Node *m = n->right == nullptr? n->left : nullptr;
    if(m == nullptr) {
      if(max) m = n->left->data > n->right->data ? n->left : n->right;
      else m = n->left->data < n->right->data ? n->left : n->right;
    }
    if(max && n->data < m->data || !max && n->data > m->data) {
      T d = n->data;
      n->data = m->data;
      m->data = d;
      bubbleDown(m);
    } 
  }

  // Helper function to add a node to a BST
  void addHelper(Node *n) {
    if(last == nullptr){
       last = root = n;
    } else if(last->parent == nullptr) {
      n->parent = last;
      last->left = n;
      last = n;
    } else if(last == last->parent->left) {
      n->parent = last->parent;
      last->parent->right = n;
      last = n;
    } else {
      Node *l = findParent();
      l->left = n;
      n->parent = l;
      last = n;
    } 
    ++manyItems;
    if(root != n) bubbleUp(n);
  }

  void removeHelper() {
    root->data = last->data;
    if(root == last) {
      delete root;
      delete last;
      root = nullptr;
      last = nullptr;
    } else if(last == last->parent->left) {
      last->parent->left = nullptr;
      Node *l = findNewLast();
      delete last;
      last = l;
      //find last
    } else {
      Node *p = last->parent;
      p->right = nullptr;
      delete last;
      last = p->left;
    }
    if(root != nullptr) bubbleDown(root);
    --manyItems;
  }

  Node* findNewLast() {
    Node *l = last;
    while(l->parent != nullptr && l == l->parent->left) {
      l = l->parent;
    }
    if(l->parent != nullptr) {
      l = l->parent;
      l = l->left;
    }
    while(l->right != nullptr) {
      l = l->right;
    }
    return l;
  }

  Node* findParent() {
    Node *l = last;
    while(l->parent != nullptr && l == l->parent->right){
      l = l->parent;
    }
    if(l->parent != nullptr) {
      l = l->parent;
      l = l->right;
    }
    while(l->left != nullptr) {
      l = l->left;
    }
    return l;
  }
  
  // Helper function to print nodes in-order
  void inOrder(Node *n) {
    if(n == nullptr) return;

    inOrder(n->left);
    std::cout << n->data << std::endl;
    inOrder(n->right);
  }
  
  // Helper function to print nodes by level
  void levelOrder(Node *n) {
    if(n == nullptr) return;

    std::queue<Node*> q;
    q.push(n);

    while(!q.empty()) {
      Node *tmp = q.front();
      std::cout << tmp->data << std::endl;
      q.pop();
      if(tmp->left != nullptr) q.push(tmp->left);
      if(tmp->right != nullptr) q.push(tmp->right);
    }
  }

  public:
    Heap(bool m) : root(nullptr), last(nullptr), manyItems(0), max(m) {}
    
    ~Heap() {
      delete root;
      delete last;
      last = nullptr;
      root = nullptr;
    }

    int size() {
      return manyItems;
    }

    T getMax() {
      if(!max) throw std::runtime_error("this is a min heap--max() not supported.");
      return root == nullptr ? nullptr : root->data;
    }

    T getMin() {
      if(max) throw std::runtime_error("this is a max head--min() not supported.");
      return root == nullptr ? nullptr : root->data;
    }

    void insert(const T &d) {
      Node *n = new Node(d);
      addHelper(n);
    }

    T remove() {
      if(root == nullptr) throw std::runtime_error("no elements in heap");
      T result = root->data;
      removeHelper();
      return result;
    }

    void display() {
      std::cout << "Level order: " << std::endl;
      levelOrder(root);
      std::cout << "In-Order:" << std::endl;
      inOrder(root);
    }
};

#endif
