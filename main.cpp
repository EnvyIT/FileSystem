#include <iostream>

#include "Tree.h"
#include "StringNode.h"
#include "FileSystem.h"


using namespace std;

static Tree* tree = nullptr;

static void print_tree(Tree* tree) {
  const auto count = tree->get_node_count();
  cout << "Nodes: " << count << endl;
  tree->print(cout);
}

static void print_test_header(const string& heading) {
  cout << "\n---- ---- ----" << heading << "---- ---- ----" << endl;
}

static void tear_down() {
  cout << "Destroying global tree calling tear_down() ..." << endl;
  delete tree;
  tree = nullptr;
}

static void setup() {
  tree = new Tree();
  const auto root = new StringNode("1");
  const auto two = new StringNode("2");
  const auto three = new StringNode("3");
  const auto four = new StringNode("4");
  const auto five = new StringNode("5");
  const auto six = new StringNode("6");
  const auto seven = new StringNode("7");
  const auto eight = new StringNode("8");
  const auto nine = new StringNode("9");
  const auto ten = new StringNode("10");
  tree->set_root(root);
  tree->insert_child(root, two);
  tree->insert_sibling(two, three);
  tree->insert_sibling(three, four);
  tree->insert_child(three, seven);
  tree->insert_sibling(seven, eight);
  tree->insert_sibling(eight, nine);
  tree->insert_sibling(nine, ten);
  tree->insert_child(two, five);
  tree->insert_sibling(five, six);
}


static void tree_tests() {
  print_test_header("TREE DYNAMIC TESTS");
  setup();
  print_tree(tree);
  tree->delete_elements();
  print_tree(tree);
  tear_down();
}

static void tree_static_tests() {
  print_test_header("TREE STATIC TESTS");
  Tree static_tree;
  StringNode root("1");
  StringNode two("2");
  StringNode three("3");
  StringNode four("4");
  StringNode five("5");
  StringNode six("6");
  StringNode seven("7");
  StringNode eight("8");
  StringNode nine("9");
  StringNode ten("10");
  static_tree.set_root(&root);
  two.set_next_sibling(&three);
  three.set_next_sibling(&four);
  three.set_first_child(&seven);
  seven.set_next_sibling(&eight);
  eight.set_next_sibling(&nine);
  nine.set_next_sibling(&ten);
  two.set_first_child(&five);
  five.set_next_sibling(&six);
  static_tree.insert_child(&root, &two);
  print_tree(&static_tree);
}

static void tree_delete_subtree_tests() {
  print_test_header("TREE DELETE SUBTREE TESTS");
  setup();
  const auto three = tree->get_root()->get_first_child()->get_next_sibling(); //Node (3)
  print_tree(tree);
  cout << "Deleting subtree from Node (3) ... " << endl;
  tree->delete_subtree(three);
  print_tree(tree);
  cout << "Calling tree.delete_elements() ... " << endl;
  tree->delete_elements();
  print_tree(tree);
  tear_down();
}

static void tree_clear_tests() {
  print_test_header("TREE CLEAR TESTS");
  setup();
  print_tree(tree);
  cout << "Calling tree.clear() ... " << endl;
  tree->clear();
  print_tree(tree);
  cout << "Calling tree.delete_elements() ... " << endl;
  tree->delete_elements();
  tear_down();
}


static void tree_copy_ctor_tests() {
  print_test_header("TREE COPY CTOR TESTS");
  setup();
  auto tree_copy(*tree);
  const auto three = tree->get_root()->get_first_child()->get_next_sibling(); //Node (3)
  cout << "Printing origin of tree ..." << endl;
  print_tree(tree);
  cout << "Deleting subtree from origin Tree -> Deleting from Node (3) ... " << endl;
  tree->delete_subtree(three);
  cout << "Origin Tree after subtree deletion" << endl;
  print_tree(tree);
  cout << "Printing copy of tree ..." << endl;
  print_tree(&tree_copy);
  cout << "Calling tree_copy.delete_elements() ... " << endl;
  tree_copy.delete_elements();
  cout << "Calling tree.delete_elements() ... " << endl;
  tree->delete_elements();
  tear_down();
}

static void tree_assignment_tests() {
  print_test_header("TREE ASSIGNMENT OPERATOR TESTS");
  setup();
  Tree tree_copy;
  tree_copy = *tree;
  cout << "Printing origin of tree ..." << endl;
  print_tree(tree);
  const auto three = tree_copy.get_root()->get_first_child()->get_next_sibling();
  cout << "Deleting subtree from Copy Tree -> Deleting from Node (3) ... " << endl;
  tree_copy.delete_subtree(three);
  cout << "Tree copy after subtree deletion" << endl;
  print_tree(&tree_copy);
  cout << "Printing origin tree..." << endl;
  print_tree(tree);
  cout << "Calling tree_copy.delete_elements() ... " << endl;
  tree_copy.delete_elements();
  cout << "Calling tree.delete_elements() ... " << endl;
  tree->delete_elements();
  tear_down();
}

static void file_system_tests() {
  print_test_header("FILE SYSTEM TESTS");
  auto *file_system = new FileSystem();
  file_system->mkdir("", "root");
  file_system->touch("root", "ReadMe.txt");
  file_system->mkdir("root", "bin");
  file_system->mkdir("root/bin", "compiled");
  file_system->touch("root/bin", "a.out");
  file_system->touch("root/bin", "b.out");
  file_system->touch("root/bin/compiled", "c.exe");
  file_system->touch("root/ReadMe.txt", "c.exe");// -> ERROR: cannot use touch inside a File
  file_system->ls();
  file_system->rm("root/bin", "a.out");
  file_system->rm("", "root/bin");// ERROR - cannot remove Directory with rm
  file_system->rmdir("", "root"); // -> ERROR: Directory is not empty
  file_system->ls();
  file_system->rm("root/bin", "b.out");
  file_system->ls();
  file_system->rmdir("root/bin", "compiled");// ERROR - compiled is Directory and not empty - contains c.exe
  file_system->ls();
  file_system->rm("root/bin/compiled", "c.exe");
  file_system->ls();
  file_system->rmdir("root/bin", "compiled");
  file_system->ls();
  file_system->rmdir("root", "bin");
  file_system->ls();
  file_system->rm("root", "ReadMe.txt");
  file_system->ls();
  file_system->rmdir("", "root");
  file_system->ls();
  delete file_system;
}

int main() {
  tree_tests();
  tree_static_tests();
  tree_delete_subtree_tests();
  tree_clear_tests();
  tree_copy_ctor_tests();
  tree_assignment_tests();
  file_system_tests();
  return 0;
}