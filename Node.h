#pragma once

#include <ostream>

class Node {

private:
  Node* parent_;
  Node* first_child_;
  Node* next_sibling_;
  Node* previous_sibling_;
public:
  explicit Node(Node* parent = nullptr, Node* first_child = nullptr, Node* next_sibling = nullptr, Node* previous_sibling = nullptr);
  virtual ~Node();

  virtual Node* get_first_child() const {
    return first_child_;
  }
  virtual Node* get_next_sibling() const {
    return next_sibling_;
  }
  virtual Node* get_previous_sibling() const {
    return previous_sibling_;
  }
  virtual Node* get_parent() const {
    return parent_;
  }
  virtual void set_first_child(Node* node) {
    first_child_ = node;
  }
  virtual void set_next_sibling(Node* node) {
    next_sibling_ = node;
  }
  virtual void set_previous_sibling(Node* node) {
    previous_sibling_ = node;
  }
  virtual void set_parent(Node* node) {
    parent_ = node;
  }
  virtual bool has_ancestors() const {
    return next_sibling_ != nullptr || first_child_ != nullptr;
  };
  virtual Node* clone() const = 0;

  virtual void print(std::ostream& os) const = 0;
};

