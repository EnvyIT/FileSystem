#pragma once
#include "Tree.h"

#include <string>

class FileSystem : public Tree {

public:

  void touch(const std::string& path, const std::string& filename); // create new file
  void mkdir(const std::string& path, const std::string& dirname); // create new directory
  void rm(const std::string& path, const std::string& filename); // remove file
  void rmdir(const std::string& path, const std::string& dirname); // remove directory
  void ls() const; // list file system contents

};

