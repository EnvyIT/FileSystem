#pragma once

#include <ostream>
#include <string>

#include "Node.h"

class StringNode : public Node {

private:
  std::string value_;

public:
  explicit StringNode(const std::string& value = "");
  virtual ~StringNode();

  void print(std::ostream& os) const override;

  StringNode* clone() const override {
    return new StringNode(value_);
  }
  friend std::ostream& operator<<(std::ostream& os, const StringNode& string_node);
};


