#ifndef CHAINEDHASH_H
#define CHAINEDHASH_H

#include "SinglyLinkedList.h"
#include <functional>
#include <stdexcept>
#include <iostream>

// hash func works for ints--need to make universal

template<class T>
class ChainedHash {
  SinglyLinkedList<T> **table;
  const int DEFAULT_CAP = 10;
  const int LOAD_FACTOR = 5;
  int max_cap;
  int manyItems;

  void resize() {
    //resize needs to make array bigger AND rehash everything
    SinglyLinkedList<T> **old = table;
    table = new SinglyLinkedList<T>*[max_cap*2];
    for(int i = 0; i < max_cap; ++i) {
      if(old[i] == nullptr) continue;
      while(!old[i]->isEmpty()){
        add(old[i]->front());
	old[i]->pop();
      }
      delete old[i];
      old[i] = nullptr;
    }
    delete[] old;
    old = nullptr;
    max_cap *= 2;
  }

  int hash(const T &d) {
    int index = d % max_cap;
    if(index < 0) index += max_cap;
    return index;
  }

public:
  ChainedHash() : max_cap(DEFAULT_CAP) {
    table = new SinglyLinkedList<T>*[max_cap];
  }

  ChainedHash(int cap) : max_cap(cap) {
    if(cap < 0) throw std::invalid_argument("capacity cannot be negative");
    table = new SinglyLinkedList<T>*[max_cap];
  }
  
  ~ChainedHash() {
    clear();
    delete[] table;
    table = nullptr;
  }

  int size() {
    return manyItems;
  }

  bool contains(const T &d) {
    // hash and map index
    // return result of contains on list if not null
    int index = hash(d);
    if(table[index] == nullptr) return false;
    return table[index]->contains(d);
  }

  bool add(const T &d) {
    // needs to hash and map index
    // if list there--add at head; else, start new list
    int index = hash(d);
    if(table[index] == nullptr) {
      table[index] = new SinglyLinkedList<T>();
    }
    table[index]->push(d);
    ++manyItems;

    if(manyItems > max_cap * LOAD_FACTOR) {
      resize();
    }
    // if manyBuckets hits load factor--rehash
    return true;
  }

  bool remove(const T &d) {
    // needs to hash and map index
    // if index is null--not in table; return false
    int index = hash(d);
    if(table[index] == nullptr) return false;
    // remove from list
    // return result of remove from list
    bool result = table[index]->remove(d);
    // might want to decrease size if empty?
    if(result) --manyItems;
    return result;
  }

  void clear() {
    // delete all buckets
    for(int i = 0; i < max_cap; ++i) {
      if(table[i] != nullptr) {
	table[i]->clear();
	table[i] = nullptr;
      }
    }
    manyItems = 0;
  }

  void display() {
    for(int i = 0; i < max_cap; ++i) {
      std::cout << "Index " << i << ": " << std::endl;
      if(table[i] != nullptr) table[i]->display();
    }
  }
};

#endif
