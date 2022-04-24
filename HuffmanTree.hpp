//Driver: Anh Luu 50% contribution
//Navigator: Fiorella Andrea Ratti Tamayo 50% contribution
#ifndef HUFFMANTREE_HPP
#define HUFFMANTREE_HPP

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <map>

class HuffmanTree : HuffmanTreeBase {
  private:
    size_t n;
    HuffmanNode* root;
  public:
  
    std::string compress(const std::string inputStr) override;
    std::string serializeTree() const override;
    std::string decompress(const std::string inputCode, const std::string serializedTree) override;
    
    void findCode(const HuffmanNode* node, std::map<char, std::string>& codeMap, std::string code) {
    if (node == nullptr) //check if node is empty
      return;
    if(node->isLeaf())
      codeMap[node->getCharacter()] = code;
    
    findCode(node->left, codeMap, code + "0"); //when traversal goes left, add a 0 to the code
    findCode(node->right, codeMap, code + "1"); //when traversal goes right, add a 1 to the code
    
    }
    
    //recursive function 
    void serialize(const HuffmanNode* node, std::string& outString) const {
      if (node == nullptr) //check if node is empty
        return;
        
      serialize(node->left, outString);
      serialize(node->right, outString);
      
      if (node->isLeaf())
        outString = outString + "L" + node->getCharacter(); // if the node ais a leaf then we add a L plus the character to the serialize tree string
      if (node->isBranch())
        outString += "B"; //if it is a branch (internal node) then we add a B to the serialize tree string
    }

};

#endif /*HUFFMANTREE_HPP*/