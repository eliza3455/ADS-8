#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

template <typename T>
class Node {
 public:
  T word;
  int quantity;
  Node* left_point;
  Node* right_pointer;

  explicit Node(T value)
      : word(value), quantity(1), left_point(nullptr), right_pointer(nullptr) {}
};

template <typename T>
class BST {
 private:
  Node<T>* root;
  std::vector<Node<T>*> node_storage;

  void insert(Node<T>*& node, T word) {
    if (!node) {
      node = new Node<T>(word);
      node_storage.push_back(node);
      return;
    }
    if (word == node->word) {
      node->quantity++;
    } else if (word < node->word) {
      insert(node->left_point, word);
    } else {
      insert(node->right_pointer, word);
    }
  }

  int depth(Node<T>* node) const {
    if (!node) return -1;
    return 1 + std::max(depth(node->left_point), depth(node->right_pointer));
  }

  int search(Node<T>* node, T word) const {
    if (!node) return 0;
    if (word == node->word) return node->quantity;
    return word < node->word ? search(node->left_point, word)
                             : search(node->right_pointer, word);
  }

  void inOrder(Node<T>* node, std::vector<Node<T>*>& nodes) const {
    if (!node) return;
    std::stack<Node<T>*> stack;
    Node<T>* current = node;

    while (current || !stack.empty()) {
      while (current) {
        stack.push(current);
        current = current->left_point;
      }
      current = stack.top();
      stack.pop();
      nodes.push_back(current);
      current = current->right_pointer;
    }
  }

  void clear(Node<T>* node) {
    if (!node) return;
    clear(node->left_point);
    clear(node->right_pointer);
    delete node;
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }

  void insert(T word) { insert(root, word); }

  int search(T word) const { return search(root, word); }

  int depth() const { return depth(root); }

  void printSortedByFrequency() {
    std::vector<Node<T>*> nodes;
    inOrder(root, nodes);

    std::sort(nodes.begin(), nodes.end(),
              [](const Node<T>* a, const Node<T>* b) {
                return a->quantity > b->quantity;
              });

    std::ofstream out("freq.txt");
    for (const auto& node : nodes) {
      std::cout << node->word << ": " << node->quantity << "\n";
      if (out.is_open()) {
        out << node->word << ": " << node->quantity << "\n";
      }
    }
  }
};

#endif  // INCLUDE_BST_H_
