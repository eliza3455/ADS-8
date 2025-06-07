// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

BST<std::string> makeTree(const char* filename) {
    BST<std::string> Tree;
    std::ifstream file(filename);
    std::string strfile = "";
    char ch;
    while (file.get(ch)) {
        strfile += ch;
    }
    int length = strfile.length();
    for (int i = 0; i < length; i++) {
        if (strfile[i] >= 'A' && strfile[i] <= 'Z') {
            strfile[i] += ' ';
        }
    }
    bool inWord = false;
    std::string temp = "";
    for (int i = 0; i < length; i++) {
  
        if (strfile[i] >= 'a' && strfile[i] <= 'z') {
            inWord = true;
            temp += strfile[i];
        } else {
            inWord = false;
            Tree.add(temp);
            temp = "";
        }
    }
    if (temp != "")
        Tree.add(temp);
    file.close();
    return Tree;
}

int main() {
    char const* filename = "war_peace.txt";
    BST<std::string> tree = makeTree(filename);
    int depth1 = tree.depth();
    int depth2 = tree.search("pierre");
    std::cout << depth1 << std::endl;
    std::cout << depth2 << std::endl;
	return 0;
}
