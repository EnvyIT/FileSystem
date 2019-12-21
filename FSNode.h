#pragma once
#include "Node.h"

#include <string>

class FSNode : public Node {

protected:
  std::string name_;

public:
  explicit FSNode(const std::string& name = "");
  virtual FSNode* clone() const override {
    return new FSNode(name_);
  }
  virtual std::string get_name() const {
    return name_;
  }
  virtual void print(std::ostream& os) const override;
};


