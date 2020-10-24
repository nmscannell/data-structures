#ifndef AVL_H
#define AVL_H

#include <queue>
#include <stdexcept>
#include <iostream>
#include <cmath>

template<class T>
class AVL {
  class Node {
    T data;
    int height; 
    Node *left, *right, *parent;
    friend class AVL;

    public:
      Node(const T &d, Node *l=nullptr, Node *r=nullptr, Node *p=nullptr) : data(d), height(1), left(l), right(r), parent(p) {}
      ~Node() {
        left = right = parent = nullptr;
      }
      int getHeight() {
        return height;
      }
    };

  Node *root;
  int manyItems;

  // Helper function to add a node to a BST
  void addHelper(Node *r, Node *n) {
    if(r == nullptr) return;
    if(n->data < r->data) {
      if(r->left != nullptr) {
	addHelper(r->left, n);
      } else {
	r->left = n;
	n->parent = r;
      }
    } else {
      if(r->right != nullptr) {
	addHelper(r->right, n);
      } else {
	r->right = n;
	n->parent = r;
      }
    }
  }

  // Helper function to fix violations that occur after adding
  void addFixViolation(Node *n) {
    int heightLeft, heightRight;
    Node *z = n;
    while(z != nullptr) {
    	if(z->left == nullptr) heightLeft = 0;
    	else heightLeft = z->left->getHeight();
    	if(z->right == nullptr) heightRight = 0;
    	else heightRight = z->right->getHeight();
	z->height = std::max(heightLeft, heightRight) + 1;
	std::cout << "z: " << z->data << " height: " << z->height << std::endl;
        if(std::abs(heightLeft-heightRight) > 1) {
          //need to rotate
          Node *y, *x;
	  if(n->data < z->data) y = z->left;
	  else y = z->right;
	  if(n->data < y->data) x = y->left;
	  else x = y->right;
	  std::cout << "y: " << y->data << " x: " << x->data << std::endl;
	  std::cout << "rotating" << std::endl;
	  rotate(x, y, z);
	}
        z = z->parent;
    }
  }

  void rotate(Node *x, Node *y, Node *z) {
    Node *a, *b, *c;
    if(x->data < y->data && x->data < z->data){
      a = x;
      b = y->data < z->data ? y : z;
      c = b == y ? z : y;
    } else if(y->data < x->data && y->data < z->data) {
      a = y;
      b = x->data < z->data ? x : z;
      c = b == x ? z : x;
    } else {
      a = z;
      b = x->data < y->data ? x : y;
      c = b == x ? y : x;
    }
    std::cout << "a: " << a->data << " b: " << b->data << " c: " << c->data << std::endl;
    if(a == b->parent) {
      std::cout << "left leaning" << std::endl;
      a->right = b->left;
      if(b->left != nullptr) b->left->parent = a;
      b->left = a;
      a->parent = b;
      a->height = std::max(a->left == nullptr ? 0 : a->left->height, a->right == nullptr ? 0 : a->right->height) + 1;
      b->height = std::max(a->height, c->height) + 1;
    } else if(c == b->parent) {
      std::cout << "right leaning" << std::endl;
      c->left = b->right;
      if(b->right != nullptr) b->right->parent = c;
      b->right = c;
      c->parent = b;
      c->height = std::max(c->left == nullptr ? 0 : c->left->height, c->right == nullptr ? 0 : c->right->height) + 1;
      b->height = std::max(a->height, c->height) + 1;
    } else {
      std::cout << "zigzag" << std::endl;
      a->right = b->left;
      if(b->left != nullptr) b->left->parent = a;
      c->left = b->right;
      if(b->right != nullptr) b->right->parent = c;
      b->left = a;
      a->parent = b;
      b->right = c;
      c->parent = b;
      a->height = std::max(a->left == nullptr ? 0 : a->left->height, a->right == nullptr ? 0 : a->right->height) + 1;
      c->height = std::max(c->left == nullptr ? 0 : c->left->height, c->right == nullptr ? 0 : c->right->height) + 1;
      b->height = std::max(a->height, c->height) + 1;
    } 

  }
  
  // Helper function to remove a node
  Node* removeHelper(Node *n, const T &d) {
    if(n == nullptr) return nullptr;
    if(d < n->data) {
      n->left = removeHelper(n->left, d);
    } else if(d > n->data) {
      n->right = removeHelper(n->right, d);
    } else {
      // if the node being removed has only a right child or no children
      // replace node with right child
      if(n->left == nullptr) {
        Node *rc = n->right;
	if(rc != nullptr) {
	  rc->parent = n->parent;
	  if(n == n->parent->left) {
	    n->parent->left = rc;
	  } else {
	    n->parent->right = rc;
	  }
	}
	fixViolation(n->parent);
	delete n;
	n = nullptr;
	return rc;
      } 
      // if the node being removed has only a left child
      // replace node with left child
      else if(n->right == nullptr) {
	Node *lc = n->left;
	std::cout << d << " has one left child" << std::endl;
	lc->parent = n->parent;
	if(n == n->parent->left) {
	  n->parent->left = lc;
	} else {
          n->parent->right = lc;
	}
	fixViolation(n->parent);
	delete n;
	n = nullptr;
	return lc;
      } 
      // if the node being removed has two children, replace the node 
      // with its successor, then delete successor
      else {
	Node *tmp = n->right;
	while(tmp->left != nullptr) {
	  tmp = tmp->left;
	}
	n->data = tmp->data;
	n->right = removeHelper(n->right, tmp->data);
      }
    }
    return n;
  }

  // Helper function to fix a violation after removal
  void fixViolation(Node *n) {  
    int heightLeft, heightRight;
    Node *z = n;
    while(z != nullptr) {
    	if(z->left == nullptr) heightLeft = 0;
    	else heightLeft = z->left->getHeight();
    	if(z->right == nullptr) heightRight = 0;
    	else heightRight = z->right->getHeight();
	z->height = std::max(heightLeft, heightRight) + 1;
        if(std::abs(heightLeft-heightRight) > 1) {
          //need to rotate
          Node *y, *x;
	  y = heightLeft > heightRight ? z->left : z->right;
	  if(y->left->height != y->right->height){
            x = y->left->height > y->right->height ? y->left : y->right;
	  } else {
	    x = y == z->left ? y->left : y->right;
	  }
	  rotate(x, y, z);
	}
        z = z->parent;
    }
  }
  
  // Helper function to print nodes in-order
  void inOrder(Node *n) {
    if(n == nullptr) return;

    inOrder(n->left);
    std::cout << n->data << " " << static_cast<int>(n->height) << std::endl;
    inOrder(n->right);
  }
  
  // Helper function to print nodes by level
  void levelOrder(Node *n) {
    if(n == nullptr) return;

    std::queue<Node*> q;
    q.push(n);

    while(!q.empty()) {
      Node *tmp = q.front();
      std::cout << tmp->data << " " << static_cast<int>(tmp->height) << std::endl;
      q.pop();
      if(tmp->left != nullptr) q.push(tmp->left);
      if(tmp->right != nullptr) q.push(tmp->right);
    }
  }

  public:
    AVL() : root(nullptr), manyItems(0) {}
    
    ~AVL() {
      delete root;
      root = nullptr;
    }

    int size() {
      return manyItems;
    }

    bool add(const T &d) {
      if(contains(d)) return false;
      std::cout << "Adding: " << d << std::endl;
      Node *n = new Node(d);
      if(root == nullptr) {
	root = n;
      } else {
	addHelper(root, n);
	addFixViolation(n);
	// need to find new root
	root = n;
	while(root->parent != nullptr) {
          root = root->parent;
	}
      }
      ++manyItems;
      return true;
    }

    bool remove(const T &d) {
      if(!contains(d)) return false;
      root = removeHelper(root, d);
      // need to find new root
      while(root->parent != nullptr) {
	root = root->parent;
      }
      --manyItems;
      return true;
    }

    bool contains(const T &d) {
      Node *n = root;
      while(n != nullptr) {
	if(d < n->data) n = n->left;
	else if(d == n->data) return true;
	else n = n->right;
      }
      return false;
    }
    
    void display() {
      std::cout << "Level order: " << std::endl;
      levelOrder(root);
      std::cout << "In-Order:" << std::endl;
      inOrder(root);
    }
};

#endif
