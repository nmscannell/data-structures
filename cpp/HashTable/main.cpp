#include "IntLinearHash.h"

int main() {
  IntLinearHash *table = new IntLinearHash();
  table->display();
  table->add(5);
  table->add(8);
  table->display();
  table->add(25);
  table->add(18);
  table->display();
  table->add(35);
  table->add(33);
  table->display();
  table->add(75);
  table->remove(5);
  std::cout << table->contains(5) << std::endl;
  table->add(85);
  table->display();
  return 0;
}
