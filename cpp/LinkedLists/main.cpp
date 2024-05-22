#include "SinglyLinkedList.h"
#include <iostream>

int main() {
  SinglyLinkedList<int> *l = new SinglyLinkedList<int>();

  try {
    l->back();
  } catch (std::runtime_error&) {
    std::cout << "back throws exception on an empty list" << std::endl;
  }

  try {
    l->front();
  } catch (std::runtime_error&) {
    std::cout << "front throws exception on an empty list" << std::endl;
  }

  int val = 5;
  std::cout << "Adding 5, 3, 8 to list:" << std::endl;
  l->add(val);
  l->add(val=3);
  l->add(val=8);
  l->display();
  std::cout << "Front returns: " << l->front() << std::endl;
  std::cout << "Back returns: " << l->back() << std::endl;

  std::cout << "\nRemoving 4: " << std::endl;
  l->remove(val=4);
  l->display();

  std::cout << "\nRemoving 5: " << std::endl;
  l->remove(val=5);
  l->display();
  l.reverse();
  l.display();
  delete l;
  return 0;
}
