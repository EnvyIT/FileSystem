#pragma once
#include "FSNode.h"

class Directory : public FSNode {

public:
  explicit Directory(const std::string& name = "");
  virtual Directory* clone() const override {
    return new Directory(name_);
  }
};

