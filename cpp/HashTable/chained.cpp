#include "ChainedHash.h"
#include <iostream>

int main() {
  ChainedHash<int> *table = new ChainedHash<int>();
  table->add(5);
  table->add(35);
  table->add(75);
  table->add(8);
  table->add(2);
  table->add(18);
  table->display();
  table->remove(5);
  table->remove(2);
  table->display();

  return 0;
}
