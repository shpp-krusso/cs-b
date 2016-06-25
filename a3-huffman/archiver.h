#ifndef ARCHIVER_H
#define ARCHIVER_H

#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <node.h>
#include <list>
#include <vector>
#include <deque>
#include <bitset>
using namespace std;

class Archiver {
public:
    Archiver();
    void compress(string filePath);
    void uncompess(string filePath);
private:
    map <char, int> * getSymbolsFreq(string filePath);
    list<Node*>& orderedNodeInsert(Node* node, list<Node*> &huffTree);
    list<Node*>* buildLeaves(map<char, int> &freqMap);
    Node* buildTree(list<Node*> * nodeList);
    void printTree(Node* root, unsigned k);
    map<char, string>* buildSymbCodeTable(Node* root);
    void buildSymbolsCodeTable(Node* root, map<char, string >* symbolsCodeTable, vector <char> &codeOneSymbol);
    void printCodeTable(map<char, string> * symbolsCodeTable);
    string getEncryptedData(string filePath, map<char, string> *symbolsCodeTable);
    void getEncryptedTree(Node* root, string &encryptedTree);
    void writeInFile(string &encryptedTree, string &encryptedData);
    deque<char>* getFinalCode(string &encryptedTree, string &encryptedData);
    deque<char> addStringtoByteDeque(string s, deque<char> &deq);
    deque<char>* readFile(string filePath);
    Node* getTree(deque<char>* encodedFile);
    Node* buildTreeFromEncodedTree(deque<bool> &encodedTree);


};

#endif // ARCHIVER_H
