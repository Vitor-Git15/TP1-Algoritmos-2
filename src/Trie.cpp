#include "Trie.hpp"

#include <iostream>
TrieNode* Dictionary::getRoot(){
  return this->root;
}

void Dictionary::insert(TrieNode *curr, int code, char ch, bool isDescompress){
  TrieNode* newNode = new TrieNode(code, ch, curr);
  curr->children.push_back(newNode);
  if(isDescompress)
    this->codesAdd.push_back(newNode);
}

TrieNode* Dictionary::find(TrieNode *curr, char ch){

  for (TrieNode *child : curr->children){
    if (child->character == ch){
      return child;
    }
  }
  return curr;
}

TrieNode* Dictionary::findString(const std::string& string){

  TrieNode *curr;
  curr = this->getRoot();

  for (char ch : string){
    curr = this->find(curr, ch);
  }
  return curr;
}

TrieNode* Dictionary::findCode(int code){
  if(code == 0)
    return this->getRoot();
    
  int treeSize = this->codesAdd.size();
  if(treeSize < code)
    return nullptr;

  return this->codesAdd[code - 1];
}

std::string Dictionary::getStringToNode(TrieNode *curr){
  std::string buffer;
  buffer = "";

  while(curr != this->getRoot()){
    buffer = curr->character + buffer;
    curr = curr->parent;
  }

  return buffer;
}