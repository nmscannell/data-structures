#ifndef INTGRAPH_H
#define INTGRAPH_H

#include <stack>
#include <queue>
#include <priority_queue>
#include <functional>
#include <stdexcept>
#include <iostream>
#include <type_traits>

// this class uses open address hashing with linear probing
class IntGraph {
  int *table;
  SinglyLinkedList<int> **values;
  bool *used;
  const int DEFAULT_CAP = 10;
  const float LOAD_FACTOR = 0.75;
  int max_cap;
  int manyItems;

  void rehash() {
    int *old = table;
    SinglyLinkedList<int> **oldV = values;
    values = new SinglyLinkedList<int>*[max_cap*2]{};
    table = new int[max_cap*2]{};
    used = new bool[max_cap*2]{};
    for(int i = 0; i < max_cap; ++i) {
      add(old[i]);
    }
    delete[] old;
    old = nullptr;
    delete[] oldV;
    oldV = nullptr;
    max_cap *= 2;
  }

  int hash(int d) {
    int index = d % max_cap; //std::hash<int>(d) % max_cap;
    if(index < 0) index += max_cap;
    return index;
  }

  int findIndex(int d) {
    int index = hash(d);
    int count = 0;
    while(count < max_cap && used[index]) {
      if(d == table[index]) return index;
      ++count;
      index = nextIndex(index);
    }
    return -1;
  }

  int nextIndex(int index) {
    if(index + 1 == max_cap) return 0;
    return index + 1;
  }

public:
  IntGraph() : max_cap(DEFAULT_CAP) {
    table = new int[max_cap]{};
    values = new SinglyLinkedList<int>*[max_cap]{};
    used = new bool[max_cap]{};
  }

  IntGraph(int cap) : max_cap(cap) {
    if(cap < 0) throw std::invalid_argument("capacity cannot be negative");
    table = new int[max_cap]{};
    values = new SinglyLinkedList<int>*[max_cap]{};
    used = new bool[max_cap]{};
  }

  ~IntGraph() {
    delete[] table;
    delete[] used;
    delete[] values;
    values = nullptr;
    used = nullptr;
    table = nullptr;
  }

  int size() {
    return manyItems;
  }

  bool contains(int d) {
    return findIndex(d) != -1;    
  }

  bool add(int d, SinglyLinkedList<int>* v) {
    // get hashed index
    int index = findIndex(d);
    if(index != -1) return false;

    index = hash(d);
    std::cout << "hash: " << index << std::endl;
    while(table[index] != 0)
      index = nextIndex(index);
    table[index] = d;
    values[index] = v;
    used[index] = true;
    ++manyItems;

    if(manyItems > LOAD_FACTOR * max_cap) rehash();
    return true;
  }

  bool remove(int d) {
    int index = findIndex(d);
    if(index == -1) return false;
    table[index] = 0;
    delete values[index];
    values[index] = nullptr;
    --manyItems;
    return true;
  }

  SinglyLinkedList<int> getAdjacent(int d) {
    int index = findIndex(d);
    if(index == -1) return nullptr;
    return values[index];
  }

  int* bfs(int s, int d) {}

  int* dfs(int s, int d) {}

  int* dijkstra(int s, int d) {}

  void clear() {
    delete[] table;
    table = new int[DEFAULT_CAP]{};
    delete[] used;
    used = new bool[DEFAULT_CAP]{};
    delete[] values;
    values = new SinglyLinkedList<int>*[DEFAULT_CAP]{};
    manyItems = 0;
  }

  void display() {
    for(int i = 0; i < max_cap; ++i) {
      std::cout << "key: " << table[i] << " value: " << values[i] << std::endl;
    }
  }

};

#endif
