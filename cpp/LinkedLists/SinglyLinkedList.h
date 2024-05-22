#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <stdexcept>
#include <iostream>

template<class T>
class SinglyLinkedList {
  class Node {
    T data;
    Node *next;
    friend class SinglyLinkedList;
    public:
      Node() : data(nullptr), next(nullptr) {}

      Node(const T &d, Node *n=nullptr) : data(d), next(n) {}
    };

  int manyItems;
  Node *head, *tail;
  
  public: 
    SinglyLinkedList() : manyItems(0), head(nullptr) {}

    ~SinglyLinkedList() {
      clear();
    }

    int size() {
      return manyItems;
    }

    bool isEmpty() {
      return manyItems == 0;
    }

    T front() {
      if(isEmpty()) throw std::runtime_error("list is empty");
      return head->data;
    }

    T back() {
      if(isEmpty()) throw std::runtime_error("list is empty");
      return tail->data;
    }

    bool add(const T &elem) {
      if(head == nullptr) {
        head = tail = new Node(elem, nullptr);
      } else {
        tail->next = new Node(elem, nullptr);
	tail = tail->next;
      }
      ++manyItems;
      return true;
    }

    bool push(const T &elem) {
      Node *n = new Node(elem, head);
      head = n;
      if(tail == nullptr) tail = head;
      ++manyItems;
      n = nullptr;
      return true;
    }

    bool pop() {
      return remove(head->data);
    }

    bool remove() {
      return remove(tail->data);
    }

    bool remove(const T &elem) {
      if(isEmpty()) return false;
      Node *n = head;
      if(head->data == elem) {
        head = head->next;
	if(head == nullptr) tail = nullptr;
	delete n;
	n = nullptr;
	--manyItems;
	return true;
      }
      while(n->next != nullptr && n->next->data != elem) {
	n = n->next;
      }
      if(n->next == nullptr) return false;
      Node *tmp = n->next;
      n->next = n->next->next;
      if(n->next == nullptr) tail = n;
      --manyItems;
      delete tmp;
      tmp = n = nullptr;
      return true;
    }

    void clear() {
      Node *n = head;
      while(n != nullptr) {
	Node *next = n->next;
	delete n;
	n = next;
      }
      head = tail = nullptr;
      manyItems = 0;
    }

    void reverse() {
      if (isEmpty() || head->next == nullptr) return;
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
      tail = head;
      tail->next = nullptr;
      head = cur;
      lag = cur = next = nullptr;
    }

    bool contains(const T &d) {
      if(head->data == d || tail->data == d) return true;
      Node *n = head;
      while(n != nullptr && n->data != d) {
	n = n->next;
      }
      return n != nullptr;
    }

    void display(Node* n) {
        std::cout << "n: " << n << "; n->data: " << n->data << "; n->next: " << n->next << std::endl;
    }

    void display() {
      Node *n = head;
      while(n != nullptr) {
	display(n);
	n = n->next;
      }
      n = nullptr;
    }
};

#endif
