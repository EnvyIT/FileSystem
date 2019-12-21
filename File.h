#pragma once
#include "FSNode.h"

#include <string>

class File : public FSNode {

private:
  std::string contents_;
public:
  explicit File(const std::string& name = "", const std::string& contents = "");
  virtual File* clone() const override {
    return new File(contents_);
  }
};

