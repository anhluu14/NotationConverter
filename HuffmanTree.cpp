//Driver: Anh Luu 50% contribution
//Navigator: Fiorella Andrea Ratti Tamayo 50% contribution
#include <map>
#include <iostream>
#include <stack>
#include "HuffmanTree.hpp"
//compress function - compress the input string using the Huffman code method
std::string HuffmanTree::compress(const std::string inputStr) {
  std::map<char, size_t> char_m;
  std::map<char, size_t>::iterator i;
  
  size_t count[256] = {0};
  
  //reading characters, counting their frequencies, and storing those frequencies in the array.
  for (int i = 0; inputStr[i] != '\0'; i++) {
    count[(size_t)inputStr[i]]++;
  }
  for(int i = 0; i < 256; i++) {
    if(count[i] != 0){
      char_m.insert(std::pair<char,size_t>((char)i, count[i]));   
    }
  }
  
  //creating Heap Priority Queue and populate the heap.
  HeapQueue<HuffmanNode*, HuffmanNode::Compare> pq;
  for (i = char_m.begin(); i != char_m.end(); ++i) {
    HuffmanNode* node = new HuffmanNode(i->first, i->second);
    n++;
    pq.insert(node);
  }
  
  //huffman tree creating from PQ
  while (pq.size() != 1){
    HuffmanNode* u1 = pq.min();
    pq.removeMin();
    HuffmanNode* u2 = pq.min();
    pq.removeMin();
    size_t freqT = (u1->getFrequency() + u2->getFrequency());
    HuffmanNode* parentN1N2 = new HuffmanNode('\0', freqT, nullptr, u1, u2);
    u1->parent = parentN1N2;
    u2->parent = parentN1N2;
    pq.insert(parentN1N2);
  }
  
  //assign root private var.
  root = pq.min();
  
  //encoding of each character in the string
  //map for the Huffman Coding for each characters
  std::map<char, std::string> codeMap;
  std::string code = "";
  std::string output = "";
  
  for (i = char_m.begin(); i != char_m.end(); ++i) {
    findCode(pq.min(), codeMap, code);
  }
    
  for (auto i : inputStr) {
    output += codeMap[i];
  }
  return output;
}

//tree serialization function
std::string HuffmanTree::serializeTree() const {
  if (root == nullptr) {
    return "";
  }
  
  std::string output = "";
  serialize(root, output);
  return output;
}

//tree decompression function 
std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree) {
  std::string output = "";
  std::stack<HuffmanNode*> S;
  
  //reconstruct the tree from serializedTree string and a stack
    bool flag = false; //a flag variable to check if the character is an "L" or not
    for(auto character : serializedTree) {
      if (!flag && character == 'L') { //when read an L in the string place the next character in a node and onto the stack.
        flag = true;
        continue;
        } else if (flag) {
        HuffmanNode* huffNode = new HuffmanNode(character, 0);
        S.push(huffNode);
        flag = false;
        } else if (!flag && character == 'B') { //when read a B pop the last two nodes off and create a parent that we push back on.
          HuffmanNode* right = S.top();
          S.pop();
          HuffmanNode* left = S.top();
          S.pop();
          HuffmanNode* branch = new HuffmanNode('\0', 0, nullptr, left, right);
          S.push(branch);
          right->parent = branch;
          left->parent = branch;
      }
    }
  
  //copy the remained stack to be the root of the newly constructed Huffman Tree & clean up using pop function.
  HuffmanNode* root = S.top();
  S.pop();
  
  //reconstructing the text from the code using the built huffman tree
  HuffmanNode* cur = root;
  for (auto character : inputCode) {
    if (character == '0')
      cur = cur->left;
    else
      cur = cur->right;
    
    //once it hits the leaf, it is ful character, we add the char to output then start over from the root.
    if (cur->isLeaf()) {
      output += cur->getCharacter();
      cur = root;
    }
  }   
  return output;
}