#include "IntVector.h"
#include <stdexcept>
#include <iostream>

IntVector::IntVector() : maxCap(DEFAULT_CAP), manyItems(0) {
  data = new int[maxCap]{};
}

IntVector::IntVector(int capacity) : maxCap(capacity), manyItems(0) {
  data = new int[maxCap]{};
}

IntVector::~IntVector() {
  delete[] data;
  data = nullptr;
}

void IntVector::resize() {
  maxCap *= 2;
  int *arr{ new int[maxCap] {} };

  for(int i{0}; i < manyItems; ++i)
    arr[i] = data[i];

  delete[] data;
  data = arr;
}

int IntVector::size() {
  return manyItems;
}

int IntVector::get(int index) {
  if(index >= manyItems) throw std::invalid_argument("index out of range");
  return data[index];
}

int IntVector::front() {
  if(manyItems == 0) {
    std::cout << "vector is empty" << std::endl;
    return -1;
  }
  return data[0];
}

int IntVector::back() {
  if(manyItems == 0) {
    std::cout << "vector is empty" << std::endl;
    return -1;
  }
  return data[manyItems-1];
}

void IntVector::remove(int elem) {
  int i{0};
  for(; i < manyItems && data[i] != elem; ++i);
  
  if(i == manyItems) {
    std::cout << "element not in vector" << std::endl;
    return;
  }

  for(; i < manyItems; ++i)
    data[i] = data[i+1];

  --manyItems;
}

void IntVector::removeLast() {
  if(manyItems == 0) {
    std::cout << "vector is empty" << std::endl;
    return;
  }
  --manyItems;
}

void IntVector::removeFirst() {
  remove(data[0]);
}

void IntVector::add(int elem) {
  if(manyItems == maxCap) resize();

  data[manyItems] = elem;
  ++manyItems;
}

void IntVector::insert(int index, int elem) {
  if(manyItems == maxCap) resize();
  // need to shift starting from back, including index
  for(int i{manyItems}; i > index; --i)
    data[i] = data[i-1];

  data[index] = elem;
  ++manyItems;
}

void IntVector::set(int index, int elem) {
  if(index >= manyItems) throw std::invalid_argument("index out of range");

  data[index] = elem;
}

void IntVector::clear() {
  manyItems = 0;
}

void IntVector::display() {
  std::cout << "Contents of the vector: " << std::endl;
  for(int i = 0; i < manyItems; ++i) {
    std::cout << data[i];
    if(i < manyItems-1) std::cout << ", ";
  }
  std::cout << std::endl;
}
