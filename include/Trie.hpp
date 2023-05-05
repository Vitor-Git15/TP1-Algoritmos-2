#ifndef TRIE
#define TRIE

#include <string>
#include <vector>
#include <queue>

class TrieNode{
public:
  unsigned int code;
  unsigned char character;
  TrieNode* parent; 
  std::vector<TrieNode *> children;

  TrieNode(unsigned int cd, unsigned char ch, TrieNode* p) : code(cd), character(ch), parent(p) {}

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

  void insert(TrieNode *curr, unsigned int code, unsigned char ch, bool isDescompress);

  TrieNode* find(TrieNode *curr, unsigned char ch);
  TrieNode* findString(const std::string& string);
  TrieNode* findCode(unsigned int code);

  void accessAllNodes(TrieNode* curr, std::queue<TrieNode*>* to_visit);
  std::string getStringToNode(TrieNode *curr);

private:
  TrieNode *root;
  std::vector<TrieNode*> codesAdd;
};

#endif
