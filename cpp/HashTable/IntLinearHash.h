#ifndef INTLINEARHASH_H
#define INTLINEARHASH_H

#include <functional>
#include <stdexcept>
#include <iostream>
#include <type_traits>

// this class uses open address hashing with linear probing
class IntLinearHash {
  int *table;
  bool *used;
  const int DEFAULT_CAP = 10;
  const float LOAD_FACTOR = 0.75;
  int max_cap;
  int manyItems;

  void rehash() {
    int *old = table;
    table = new int[max_cap*2]{};
    used = new bool[max_cap*2]{};
    for(int i = 0; i < max_cap; ++i) {
      add(old[i]);
    }
    delete[] old;
    old = nullptr;
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
  IntLinearHash() : max_cap(DEFAULT_CAP) {
    table = new int[max_cap]{};
    used = new bool[max_cap]{};
  }

  IntLinearHash(int cap) : max_cap(cap) {
    if(cap < 0) throw std::invalid_argument("capacity cannot be negative");
    table = new int[max_cap]{};
    used = new bool[max_cap]{};
  }

  ~IntLinearHash() {
    delete[] table;
    delete[] used;
    used = nullptr;
    table = nullptr;
  }

  int size() {
    return manyItems;
  }

  bool contains(int d) {
    return findIndex(d) != -1;    
  }

  bool add(int d) {
    // get hashed index
    int index = findIndex(d);
    if(index != -1) return false;

    index = hash(d);
    std::cout << "hash: " << index << std::endl;
    while(table[index] != 0)
      index = nextIndex(index);
    table[index] = d;
    used[index] = true;
    ++manyItems;

    if(manyItems > LOAD_FACTOR * max_cap) rehash();
    return true;
  }

  bool remove(int d) {
    int index = findIndex(d);
    if(index == -1) return false;
    table[index] = 0;
    --manyItems;
    return true;
  }

  void clear() {
    delete[] table;
    table = new int[DEFAULT_CAP]{};
    delete[] used;
    used = new bool[DEFAULT_CAP]{};
    manyItems = 0;
  }

  void display() {
    for(int i = 0; i < max_cap; ++i) {
      std::cout << "element: " << table[i] << " used: " << used[i] << std::endl;
    }
  }

};

#endif
