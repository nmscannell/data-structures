#ifndef LINEARHASH_H
#define LINEARHASH_H

#include <functional>
#include <stdexcept>
#include <iostream>
#include <type_traits>

//need to figure out how to make this work for any type...
// this class uses open address hashing with linear probing
template<class T>
class LinearHash {
  T *table;
  bool *used;
  const int DEFAULT_CAP = 10;
  const float LOAD_FACTOR = 0.75;
  int max_cap;
  int manyItems;

  void rehash() {
    T *old = table;
    table = new T[max_cap*2]{};
    used = new bool[max_cap*2]{};
    for(int i = 0; i < max_cap; ++i) {
      add(old[i]);
     // delete old[i];
     // old[i] = nullptr;
    }
    delete[] old;
    old = nullptr;
    max_cap *= 2;
  }

  int hash(T &d) {
    int index = std::hash<T>()(d) % max_cap;
    if(index < 0) index += max_cap;
    return index;
  }

  int findIndex(T d) {
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
  LinearHash() : max_cap(DEFAULT_CAP) {
    table = new T[max_cap]{};
    used = new bool[max_cap]{};
  }

  LinearHash(int cap) : max_cap(cap) {
    if(cap < 0) throw std::invalid_argument("capacity cannot be negative");
    table = new T[max_cap]{};
    used = new bool[max_cap]{};
  }

  ~LinearHash() {
    delete[] table;
    delete[] used;
    used = nullptr;
    table = nullptr;
  }

  int size() {
    return manyItems;
  }

  bool contains(T d) {
    return findIndex(d) != -1;    
  }

  bool add(T d) {
    // get hashed index
    int index = findIndex(d);
    if(index != -1) return false;

    index = hash(d);
    while(table[index].compare("") != 0)
      index = nextIndex(index);
    table[index] = d;
    used[index] = true;
    ++manyItems;

    if(manyItems > LOAD_FACTOR * max_cap) rehash();
    return true;
  }

  bool remove(T d) {
    int index = findIndex(d);
    if(index == -1) return false;
    table[index] = nullptr;
    --manyItems;
    return true;
  }

  void clear() {
    delete[] table;
    delete[] used;
    table = new T[DEFAULT_CAP]{};
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
