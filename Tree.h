#pragma once

#include <ostream>

#include "Node.h"


class Tree {

protected:
  Node* root_{ nullptr };
  Node* saved_root_{ nullptr };

public:
  Tree();
  Tree(const Tree& other);
  Tree& operator=(const Tree& other);
  virtual ~Tree();

  virtual Node* get_root() const {
    return root_;
  }
  virtual void set_root(Node* node) {
    root_ = node;
  }
  virtual void set_saved_root(Node* node) {
    saved_root_ = node;
  }
  virtual bool is_empty() const {
    return root_ == nullptr;
  }
  virtual bool is_root(const Node* node) const {
    return node == root_;
  }

  virtual int get_node_count() const;
  virtual void insert_child(Node* parent, Node* child);
  virtual void insert_sibling(Node* node, Node* next_sibling);
  virtual void delete_subtree(Node* node);
  virtual void clear();
  virtual void delete_elements();
  virtual void print(std::ostream& os) const;
  friend std::ostream& operator<<(std::ostream& os, const Tree& tree);
};

