#include "Tree.h"

#include <iostream>

#include "Node.h"
#include "StringNode.h"

using namespace std;


static void delete_node(Node* node) {
  if (node != nullptr) {
    delete_node(node->get_first_child());
    delete_node(node->get_next_sibling());
    delete node;
  }
}

static void count_nodes(const Node* node, int& count) {
  if (node != nullptr) {
    count_nodes(node->get_first_child(), count);
    count_nodes(node->get_next_sibling(), count);
    ++count;
  }
}

static void print_level(const int level) {
  for (int i = 0; i < level * 5; i++) {
    cout << " ";
  }
}

static void print_node(std::ostream& os, const Node* node, const int level) {
  if (node != nullptr) {
    print_level(level);
    node->print(os);
    print_node(os, node->get_first_child(), level + 1);
    print_node(os, node->get_next_sibling(), level);
  }
}

static void try_clone(Node* node, const Node* other) {
  if (node != nullptr && other != nullptr && other->get_first_child() != nullptr) {
    node->set_first_child(other->get_first_child()->clone());
  }
  if (node != nullptr && other != nullptr && other->get_next_sibling() != nullptr) {
    node->set_next_sibling(other->get_next_sibling()->clone());
  }
}


static void clone_tree(Node* node, const Node* other) {
  try_clone(node, other);
  if (node != nullptr && other != nullptr) {
    clone_tree(node->get_first_child(), other->get_first_child());
    clone_tree(node->get_next_sibling(), other->get_next_sibling());
  }
}

Tree::Tree() {
  cout << "Tree constructed" << endl;
}

static void set_ancestors(Node* node, Node* parent, Node* previous_sibling) {
  if (node != nullptr) {
    node->set_parent(parent);
    node->set_previous_sibling(previous_sibling);
    set_ancestors(node->get_first_child(), node, nullptr);
    set_ancestors(node->get_next_sibling(), nullptr, node);
  }
}

Tree::Tree(const Tree& other) {
  cout << "Tree copied" << endl;
  delete_node(root_);
  root_ = other.get_root()->clone();
  clone_tree(root_, other.root_);
  set_ancestors(root_, nullptr, nullptr);
}

Tree& Tree::operator=(const Tree& other) {
  cout << "Tree assigned" << endl;
  if (this == &other) {
    return *this;
  }
  delete_node(root_);
  root_ = other.get_root()->clone();
  clone_tree(root_, other.root_);
  set_ancestors(root_, nullptr, nullptr);
  return *this;
}

Tree::~Tree() {
  cout << "~Tree destructed" << endl;
}

int Tree::get_node_count() const {
  auto count = 0;
  count_nodes(root_, count);
  return count;
}

void Tree::insert_child(Node* parent, Node* child) {
  if (parent != nullptr && child != nullptr && parent->get_first_child() == nullptr
      && child->get_parent() == nullptr) {
    child->set_parent(parent);
    parent->set_first_child(child);
  } else {
    cout << "ERROR inserting parent Node: " << parent << "to child: " << child << " - Either Node was null or has already a parent / child relation" << endl;
  }
}

void Tree::insert_sibling(Node* node, Node* next_sibling) {
  if (node != nullptr && next_sibling != nullptr && node->get_next_sibling() == nullptr && next_sibling->get_previous_sibling() == nullptr) {
    node->set_next_sibling(next_sibling);
    next_sibling->set_previous_sibling(node);
  } else {
    cout << "ERROR inserting Node " << node << "to sibling  " << next_sibling << " - Either Node was null or has already a next / previous relation" << endl;
  }
}

static void rewire(Node* node) {
  auto saved_previous = node->get_previous_sibling();
  auto saved_parent = node->get_parent();
  node->set_previous_sibling(nullptr);
  node->set_parent(nullptr);
  if (saved_previous != nullptr) {
    saved_previous->set_next_sibling(node->get_next_sibling());
  }
  if (saved_parent != nullptr) {
    saved_parent->set_first_child(node->get_first_child());
  }
  if (node->get_next_sibling() != nullptr) {
    node->get_next_sibling()->set_previous_sibling(saved_previous);
  }
  node->set_next_sibling(nullptr);
  if (node->get_first_child() != nullptr) {
    node->get_first_child()->set_parent(saved_parent);
  }
  node->set_first_child(nullptr);
}

void Tree::delete_subtree(Node* node) {
  if (node != nullptr) {
    delete_node(node->get_first_child());
    node->set_first_child(nullptr);
    rewire(node);
    delete node;
  }
}

void Tree::clear() {
  if (saved_root_ != nullptr) {
    delete saved_root_;
    saved_root_ = nullptr;
  }
  set_saved_root(get_root());
  set_root(nullptr);
}

void Tree::delete_elements() {
  delete_node(root_);
  set_root(nullptr);
  delete_node(saved_root_);
  set_saved_root(nullptr);
}


void Tree::print(std::ostream& os) const {
  if (is_empty()) {
    os << "Tree is empty" << endl;
  } else {
    const auto level = 0;
    print_node(os, root_, level);
  }
}

std::ostream& operator<<(std::ostream& os, const Tree& tree) {
  tree.print(os);
  return os;
}
