#ifndef REDBLACK_H
#define REDBLACK_H

#include <queue>
#include <stdexcept>
#include <iostream>

enum class Color {RED, BLACK};

template<class T>
class RedBlack {
  class Node {
    T data;
    Color c; 
    Node *left, *right, *parent;
    friend class RedBlack;

    public:
      Node(const T &d, Node *l=nullptr, Node *r=nullptr, Node *p=nullptr) : data(d), c(Color::RED), left(l), right(r), parent(p) {}
      ~Node() {
        left = right = parent = nullptr;
      }
    };

  Node *root;
  int manyItems;

  Node* getGP(Node *n) {
    return n->parent == nullptr ? nullptr : n->parent->parent;
  }

  Node* getSib(Node *n) {
    if(n->parent == nullptr) return nullptr;
    return n == n->parent->left ? n->parent->right : n->parent->left;
  }

  Node* getUncle(Node *n) {
    return n->parent == nullptr ? nullptr : getSib(n->parent);
  }

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
    // if n is the root, we just need to make it black
    if(n->parent == nullptr) {
      n->c = Color::BLACK;
    } 
    // otherwise, new node is red; if parent is red, there is a violation
    else if(n->parent->c == Color::RED) {
      Node *u = getUncle(n);
      Node *g = getGP(n);
      Node *p = n->parent;
      // if uncle is also red, we make parent and uncle black and grandparent red
      // then fix violations starting at grandparent
      if(u != nullptr && u->c == Color::RED) {
        p->c = Color::BLACK;
        u->c = Color::BLACK;
        g->c = Color::RED;
        addFixViolation(g);
      } else {
	// if uncle is black (but parent and n are red), we need to do rotations
	// if n is a right child and p is a left child, rotate left at p
	// then move down to n's left to fix violation
	if(n == p->right && p == g->left) {
	  rotateLeft(p);
          n = n->left;
        } 
	// if n is a left child and p is a right child, rotate right at p
	// then move down to n's right to fix violation
	else if(n == p->left && p == g->right) {
          rotateRight(p);
          n = n->right;
        }
        p = n->parent;
	g = getGP(n);
	// if n is a left child, rotate right at grandparent; otherwise, mirror
        if(n == p->left) {
	  rotateRight(g);
        } else {
          rotateLeft(g);
        }
        // parent must be black and grandparent red
        p->c = Color::BLACK;
        g->c = Color::RED;
      }	
    } 
  }

  // Helper function to rotate left at n when fixing violations
  // n's right child becomes its parent and n becomes a left child
  void rotateLeft(Node* n) {
    Node *r = n->right;
    Node *rL = r->left;
    Node *p = n->parent;
    r->left = n;
    n->parent = r;
    n->right = rL;
    if(rL != nullptr) rL->parent = n;
    if(p != nullptr) {
      if(n == p->left) p->left = r;
      else p->right = r;
    }
    r->parent = p;
  }

  //Helper function to rotate right at n when fixing violations
  // n's left child becomes its parent and n becomes a right child
  void rotateRight(Node *n) {
    Node *l = n->left;
    Node *lR = l->right;
    Node *p = n->parent;
    l->right = n;
    n->parent = l;
    n->left = lR;
    if(lR != nullptr) lR->parent = n;
    if(p != nullptr) {
      if(n == p->left) p->left = l;
      else p->right = l;
    }
    l->parent = p;
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
	  // need to make sure red-black properties hold or are fixed
	  if(n->c == Color::BLACK) {
	    if(rc->c == Color::RED) {
	      rc->c = Color::BLACK;
	    } else {
	      fixViolation(rc);
	    }
	  }
	}
	
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
	// need to make sure red-black properties hold or are fixed
	if(n->c == Color::BLACK) {
          if(lc->c == Color::RED) {
	    lc->c = Color::BLACK;
	  } else {
	    fixViolation(lc);
	  }
	}
	
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
    // if n is the root, there is nothing to fix
    if(n->parent == nullptr) return;
    Node *s = getSib(n);
    Node *p = n->parent;
    // if s is red, we need to make it black and the parent red, then rotate on parent
    if(s->c == Color::RED) {
      std::cout << "Case 1: sibling is red" << std::endl;
      p->c = Color::RED;
      s->c = Color::BLACK;
      if(n == p->left) {
	rotateLeft(p);
      } else {
	rotateRight(p);
      }
    }
    s = getSib(n);
    
    // Case 2: Parent, sibling, and sibling's children are all black
    // Simply make sibling red; if parent is not root, fix violations starting at parent
    if(p->c == Color::BLACK && s->c == Color::BLACK && 
        s->left != nullptr && s->left->c == Color::BLACK &&
        s->right != nullptr && s->right->c == Color::BLACK) {
      s->c = Color::RED;
      // if the parent is the root, we have nothing else to do
      if(p->parent == nullptr) return;
      fixViolation(p);
    } 
    // Case 3: Parent red, sibling and children are black
    // Swap sibling and parent colors
    else if(p->c == Color::RED && s->c == Color::BLACK && s->left != nullptr
	&& s->left->c == Color::BLACK && s->right != nullptr && s->right->c == Color::BLACK) {
      s->c = Color::RED;
      p->c = Color::BLACK;
    } 
    // Case 4: N is a left child, sibling's right is black and left is red
    // Make sibling red and left black, then rotate right on sibling
    else if(n == p->left && s->right != nullptr && s->right->c == Color::BLACK 
	&& s->left != nullptr && s->left->c == Color::RED) {
      s->c = Color::RED;
      s->left->c = Color::BLACK;
      rotateRight(s);
    } 
    // Case 5: Mirror of Case 4
    else if(n == p->right && s->right != nullptr && s->right->c == Color::RED
	&& s->left != nullptr && s->left->c == Color::BLACK) {
      s->c = Color::RED;
      s->right->c = Color::BLACK;
      rotateLeft(s);
    } 
    //Case 6: Sibling is black, p is arbitrary; N is a left child and sib's right is red
    // Swap sib and p colors, make sib's right black, rotate left at p
    // Or N is right child and sib's left is red
    // Swap sib and p colors, make sib's left black, rotate right at p
    s = getSib(n);
    p = n->parent;
    s->c = p->c;
    p->c = Color::BLACK;
    if(n == p->left) {
      s->right->c = Color::BLACK;
      rotateLeft(p);
    } else {
      s->left->c = Color::BLACK;
      rotateRight(p);
    } 
  }
  
  // Helper function to print nodes in-order
  void inOrder(Node *n) {
    if(n == nullptr) return;

    inOrder(n->left);
    std::cout << n->data << " " << static_cast<int>(n->c) << std::endl;
    inOrder(n->right);
  }
  
  // Helper function to print nodes by level
  void levelOrder(Node *n) {
    if(n == nullptr) return;

    std::queue<Node*> q;
    q.push(n);

    while(!q.empty()) {
      Node *tmp = q.front();
      std::cout << tmp->data << " " << static_cast<int>(tmp->c) << std::endl;
      q.pop();
      if(tmp->left != nullptr) q.push(tmp->left);
      if(tmp->right != nullptr) q.push(tmp->right);
    }
  }

  public:
    RedBlack() : root(nullptr), manyItems(0) {}
    
    ~RedBlack() {
      delete root;
      root = nullptr;
    }

    int size() {
      return manyItems;
    }

    bool add(const T &d) {
      if(contains(d)) return false;
      Node *n = new Node(d);
      if(root == nullptr) {
	root = n;
	root->c = Color::BLACK;
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
