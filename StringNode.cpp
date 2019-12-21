#include "StringNode.h"

#include <iostream>

using namespace std;

StringNode::StringNode(const std::string& value) : value_(value) {
  cout << "StringNode constructed (" << value << ")" << endl;
}

StringNode::~StringNode() {
  cout << "~StringNode destructed (" << value_ << ")" << endl;
}

void StringNode::print(std::ostream& os) const {
  os << "(" << value_ << ")" << endl;
}

std::ostream& operator<<(std::ostream& os, const StringNode& string_node) {
  string_node.print(os);
  return os;
}
