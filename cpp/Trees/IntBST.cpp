#include "IntBST.h"
#include <iostream>

IntBST::Node::Node(int d, Node *l, Node *r, Node *p) : data(d), left(l), right(r), parent(p) {}
IntBST::Node::Node() : left(nullptr), right(nullptr), parent(nullptr) {};
IntBST::Node::~Node() {
  left = right = nullptr;
}

IntBST::IntBST() : root(nullptr) {}

IntBST::~IntBST() {
  clear();
  delete root;
  root = nullptr;
}

IntBST::Node* IntBST::addHelp(Node *n, int elem) {
  if(n == nullptr)
    return new Node(elem, nullptr, nullptr, nullptr);

  if(elem < n->data) {
    n->left = addHelp(n->left, elem);
    n->left->parent = n;
  }else{
    n->right = addHelp(n->right, elem);
    n->right->parent = n;
  }
  return n;
}

IntBST::Node* IntBST::removeHelp(Node *n, int elem) {
  if(n == nullptr) return nullptr;
  if(elem < n->data){
     n->left = removeHelp(n->left, elem);
  }else if(elem > n->data){
     n->right = removeHelp(n->right, elem);
  }else{
    //if left is null--replace with right child
    //if right is null--replace with left
    //find successor--leftmost of right child; replace data and remove child.
    if(n->left == nullptr){
      Node *rc = n->right;

      if(rc != nullptr) {
        rc->parent = n->parent;
      }
      delete n;
      n = nullptr;
      return rc;
    }
    else if(n->right == nullptr){
      Node *lc = n->left;
      lc->parent = n->parent;
      delete n;
      n = nullptr;
      return lc;
    }else{
      Node *tmp = n->right;
      while(tmp->left != nullptr) {
        tmp = tmp->left;
      }
      n->data = tmp->data;
      n->right = removeHelp(n->right, tmp->data);
    }
  }
  return n;
}

void IntBST::displayPreHelp(Node *n) {
  if(n == nullptr) return;
  std::cout << n->data << std::endl;
  displayPreHelp(n->left);
  displayPreHelp(n->right);
}

void IntBST::displayPostHelp(Node *n) {
  if(n == nullptr) return;
  displayPostHelp(n->left);
  displayPostHelp(n->right);
  std::cout << n->data << std::endl;
}

void IntBST::displayInHelp(Node *n) {
  if(n == nullptr) return;
  displayInHelp(n->left);
  std::cout << n->data << std::endl;
  displayInHelp(n->right);
}

bool IntBST::add(int elem) {
  if(contains(elem)) return false;
  root = addHelp(root, elem);
  ++manyItems;
  return true;
}

bool IntBST::remove(int elem) {
  if(!contains(elem)) return false;
  root = removeHelp(root, elem);
  --manyItems;
  return true;
}

void IntBST::displayPre() {
  std::cout << "Printing in pre-order: " << std::endl;
  displayPreHelp(root);
}

void IntBST::displayPost() {
  std::cout << "Printing in post-order: " << std::endl;
  displayPostHelp(root);
}

void IntBST::displayInOrder() {
  std::cout << "Printing in-order: " << std::endl;
  displayInHelp(root);
}

bool IntBST::contains(int elem) {
  Node *n = root;
  while(n != nullptr) {
    if(elem < n->data) n = n->left;
    else if(elem == n->data) return true;
    else n = n->right;
  }
  return false;
}

void IntBST::clear() {
//  delete root;
//  root = nullptr;
}
