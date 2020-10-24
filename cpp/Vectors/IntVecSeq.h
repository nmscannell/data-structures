#ifndef INTVECTOR_H
#define INTVECTOR_H

class IntVector {
  int manyItems;
  int *data;
  int *currentIndex;
  bool isCurrent;
  const int DEFAULT_CAP;
  int maxCap;

  void resize();

public:
  IntVector();
  IntVector(int capacity);
  ~IntVector();

  int size();
  void start();
  void advance();
  int getCurrent();
  void removeCurrent();
  void addAfter();

};

#endif
