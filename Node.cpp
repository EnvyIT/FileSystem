#include "Node.h"

#include <iostream>

using namespace std;

Node::Node(Node* parent, Node* first_child, Node* next_sibling, Node* previous_sibling) : parent_(parent), first_child_(first_child), next_sibling_(next_sibling), previous_sibling_(previous_sibling) {
}

Node::~Node() {
  Node::set_first_child(nullptr);
  Node::set_next_sibling(nullptr);
  Node::set_parent(nullptr);
  Node::set_previous_sibling(nullptr);
}


