#include "File.h"

#include <string>
#include <iostream>

using namespace std;

File::File(const string& name, const string& contents) :FSNode(name), contents_(contents) {
}

