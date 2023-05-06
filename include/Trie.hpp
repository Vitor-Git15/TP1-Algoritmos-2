#ifndef TRIE
#define TRIE

#include <string>
#include <vector>
#include <queue>

class TrieNode{
public:
  int code;
  char character;
  TrieNode* parent; 
  std::vector<TrieNode *> children;

  TrieNode(int cd, char ch, TrieNode* p) : code(cd), character(ch), parent(p) {}

  ~TrieNode(){
    for (TrieNode *child : children){
      delete child;
    }
  }

};

class Dictionary
{
public:
  Dictionary() : root(new TrieNode((char) 0, 0, nullptr)) {}

  ~Dictionary(){
  delete root;
  }
  
  TrieNode* getRoot();

  void insert(TrieNode *curr, int code, char ch, bool isDescompress);

  TrieNode* find(TrieNode *curr, char ch);
  TrieNode* findString(const std::string& string);
  TrieNode* findCode(int code);

  std::string getStringToNode(TrieNode *curr);

private:
  TrieNode *root;
  std::vector<TrieNode*> codesAdd;
};

#endif
