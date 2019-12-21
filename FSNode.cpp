#include "FSNode.h"

#include <string>
#include <iostream>

using namespace std;

FSNode::FSNode(const string& name) : name_(name) {
}

void FSNode::print(std::ostream& os) const {
  os << "(" << name_ << ")" << endl;
}
