#include "FileSystem.h"
#include "Directory.h"
#include "File.h"

#include <string>
#include <iostream>


using namespace std;

static bool is_directory(const Node* node) {
  const auto directory = dynamic_cast<const Directory*>(node);
  return directory != nullptr;
}

static bool is_file(Node* const node) {
  const auto file = dynamic_cast<const File*>(node);
  return file != nullptr;
}

static string extract_last_substring(std::string const& source, size_t const length) {
  if (length >= source.size()) {
    return source;
  }
  return source.substr(source.size() - length);
}

static string get_tail(const string& path) {
  unsigned int length = 0;
  auto character = ' ';
  while (character != '/' && length < path.length()) {
    character = path[path.length() - length - 1];
    ++length;
  }
  if (character == '/') {
    --length;
  }
  return extract_last_substring(path, length);
}

void find(Node* node, const string& name, Node** result) {
  if (node != nullptr) {
    if (dynamic_cast<FSNode*>(node)->get_name() == name) {
      (*result) = node;
    }
    find(node->get_first_child(), name, result);
    find(node->get_next_sibling(), name, result);
  }
}


void FileSystem::touch(const std::string& path, const std::string& filename) {
  if (is_empty()) {
    cout << "ERROR - cannot create File - no Directory exists";
    return;
  }
  Node* result = nullptr;
  find(root_, get_tail(path), &result);
  if (!is_directory(result)) {
    cout << "ERROR - cannot touch inside a File!" << endl;
    return;
  }
  if (result != nullptr && result->get_first_child() == nullptr) {
    insert_child(result, new File(filename));
  } else if (result != nullptr) {
    auto search_node = result->get_first_child();
    while (search_node->get_next_sibling() != nullptr) {
      search_node = search_node->get_next_sibling();
    }
    insert_sibling(search_node, (new File(filename)));
  }
}

void FileSystem::mkdir(const std::string& path, const std::string& dirname) {
  if (path.empty()) {
    set_root(new Directory(dirname));
  } else {
    Node* result = nullptr;
    find(root_, get_tail(path), &result);
    if (result != nullptr && result->get_first_child() != nullptr) {
      auto search_node = result->get_first_child();
      if (search_node->get_next_sibling() != nullptr) {
        while (search_node->get_next_sibling() != nullptr) {
          search_node = search_node->get_next_sibling();
        }
      }
      insert_sibling(search_node, (new Directory(dirname)));
    }
    if (result != nullptr && result->get_first_child() == nullptr) {
      insert_child(result, new Directory(dirname));
    }
  }

}

void FileSystem::rm(const std::string& path, const std::string& filename) {
  Node* result = nullptr;
  find(root_, get_tail(path), &result);
  find(result, get_tail(filename), &result);
  if (!is_file(result)) {
    cout << "ERROR - cannot remove Directory with rm from " << path << "- Do you mean rmdir?" << endl;
    return;
  }
  delete_subtree(result);
}

void FileSystem::rmdir(const std::string& path, const std::string& dirname) {
  Node* result = root_;
  find(root_, get_tail(path), &result);
  find(result, get_tail(dirname), &result);
  if (!is_directory(result)) {
    cout << "ERROR - cannot remove File with rmdir from " << path << "- Do you mean rm?" << endl;
    return;
  }
  if (result->has_ancestors()) {
    cout << "ERROR - Directory " << dirname << " is not empty for path: " << path << endl;
    return;
  }
  if (is_root(result)) {
    delete_elements();
  } else {
    delete_subtree(result);
  }
}

void FileSystem::ls() const {
  print(cout);
}
