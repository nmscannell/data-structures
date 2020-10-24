#include "IntBST.h"
#include <iostream>
#include "AVL.h"

int main() {
  /*IntBST *tree = new IntBST();
  tree->add(5);
  tree->add(2);
  tree->add(12);
  tree->add(8);
  std::cout << "tree contains 12: " << tree->contains(12) << std::endl;
  std::cout << "tree contains 3: " << tree->contains(3) << std::endl;
  tree->add(9);
  tree->add(4);
  tree->add(3);
  tree->displayPre();
  tree->displayPost();
  tree->displayInOrder();
  tree->remove(8);
  tree->displayInOrder();
  tree->remove(5);
  tree->displayInOrder();
  delete tree;
*/
  AVL<int> *t = new AVL<int>();
  t->add(6);
  t->display();
  t->add(3);
  t->add(8);
  t->display();
  t->add(4);
  t->add(5);
  t->display();
  t->add(15);
  t->add(20);
  t->display();
  std::cout << "Size: " << t->size() << std::endl;
  t->add(25);
  t->add(22);
  t->display();
  t->add(18);
  t->add(19);
  t->display();
  std::cout << "Size: " << t->size() << std::endl;
  for(int i = 30; i < 50; i += 5) {
    t->add(i);
  }
  t->display();
  t->remove(3);
  t->remove(5);
  t->display();
  t->remove(6);
  t->remove(8);
  t->display();
  t->remove(19);
  t->display();
  t->remove(15);
  t->display();
  t->remove(18);
  t->display();
  t->remove(20);
  t->display();
  delete t;
  return 0;
}
