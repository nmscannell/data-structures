#include "IntVector.h"
#include <iostream>

int main() {
  IntVector *v = new IntVector();
  std::cout << "adding 5, 3, 2" << std::endl;
  v->add(5);
  v->add(3);
  v->add(2);
  v->display();
  std::cout<< "inserting 8 at 1"<< std::endl;
  v->insert(1, 8);
  v->display();
  std::cout << "replacing index 2 with 9" << std::endl;
  v->set(2, 9);
  v->display();
  std::cout << "getting front: " << v->front() << std::endl;
  std::cout << "getting back: " << v->back() << std::endl;
  std::cout << "remove element not in vector: " <<  std::endl;
  v->remove(4);
  v->display();
  std::cout << "adding enough to resize: " << std::endl;
  for(int i = 0; i < 10; ++i)
    v->add(i);
  v->display();
  std::cout << "size: " << v->size() << std::endl;
  v->removeFirst();
  v->removeFirst();
  v->display();
  delete v;
  return 0;
}
