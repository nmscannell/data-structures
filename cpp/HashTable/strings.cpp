#include "LinearHash.h"
#include <string>
#include <iostream>

int main() {
  LinearHash<std::string> *table = new LinearHash<std::string>();
  table->add("hello");
  table->add("world");
  table->add("how");
  table->add("original");
  table->display();
  return 0;
}
