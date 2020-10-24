// a basic unsorted singly linked list
#include "intList.h"
#include <stdexcept>
#include <iostream>

IntList::Node::Node() : next(nullptr) {}

IntList::Node::Node(int &d, Node *n) : data(d), next(n) {}

IntList::IntList() : manyItems(0), head(nullptr) {}

IntList::~IntList() {
  clear();
}

int IntList::size() {
  return manyItems;
}
    
bool IntList::isEmpty() {
  return manyItems == 0;
}

int IntList::front() {
  if(isEmpty()) throw std::runtime_error("Empty List!");
  return head->data;
}
    
    // simply adds at head of list
bool IntList::add(int &elem) {
  Node *n = new Node(elem, head);
  head = n;
  ++manyItems;
  return true;
}

void IntList::remove(int &elem) {
  if(isEmpty()) return;
  Node *n = head;
  if(head->data == elem){
    head = head->next;
    n = nullptr;
    --manyItems;
    return;
  }
  while(n->next != nullptr && n->next->data != elem)
    n = n->next;

  if(n->next == nullptr) return;
  Node *tmp = n->next;
  n->next = n->next->next;
  --manyItems;
  //delete tmp;
  tmp = nullptr;
  n = nullptr;
  return;
}

void IntList::clear() {
  Node *n = head;
  while(n != nullptr) {
    Node *next = n->next;
    delete n;
    n = nullptr;
    n = next;
  }
  head = nullptr;
  manyItems = 0;
}

    //LinkedList sort() {}

void IntList::reverse() {
  Node *lag, *cur, *next;
  lag = head;
  cur = head->next;
  while(cur->next != nullptr) {
    next = cur->next;
    cur->next = lag;
    lag = cur;
    cur = next;
  }
  cur->next = lag;
  head = cur;
}

void IntList::display() {
  Node *n = head;
  while(n != nullptr) {
    std::cout << n->data << std::endl;
    n = n->next;
  }
  n = nullptr;
}

