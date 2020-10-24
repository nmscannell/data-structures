#ifndef INTVECTOR_H
#define INTVECTOR_H

class IntVector {
  int manyItems;
  int *data;
  const int DEFAULT_CAP = 10;
  int maxCap;

  void resize();

public:
  IntVector();
  IntVector(int capacity);
  ~IntVector();

  int size();
  int get(int index);
  int front();
  int back();
  void remove(int elem); //search for and remove elem
  void removeLast();
  void removeFirst();
  void add(int elem); //add at end
  void insert(int index, int elem); //shift elems and insert at index
  void set(int index, int elem); //overwrite data at index
  void clear();
  void display();
};

#endif
