#include "Heap.h"
#include <iostream>

int main() {
  Heap<int> *h = new Heap<int>(true);
  h->insert(5);
  h->display();
  h->insert(2);
  h->display();
  h->insert(4);
  h->insert(7);
  h->display();
  delete h;
}
