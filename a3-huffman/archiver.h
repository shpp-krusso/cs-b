#ifndef ARCHIVER_H
#define ARCHIVER_H
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <list>
using namespace std;

class Archiver
{
public:
    Archiver();
    void compress(string pathOfOrigin, string pathOfArchive);
    void uncompress(string pathOfArchive, string pathOfUncompressedFile);

private:
    struct Node {
        char value;
        int freq;
        Node* left;
        Node* right;
        Node(char value, int freq = 0) {
            this->value = value;
            this ->freq = freq;
            left = 0;
            right = 0;
        }

        Node(Node *left, Node *right) {
            freq = left->freq + right->freq;
            value = 0;
            this->left = left;
            this->right = right;
        }
    };
    map<char, int>* buildFreqTable(string pathOfOrigin);
    Node *buildHuffmansTree(map <char, int>* freqTable);
    void buildSymbolsCodeTable(Node* root, map<char, string>* symbolsCodeTable, string &codeOneSymbol);
    string* getEncryptedData(string pathOfOrigin, map<char, string> *codeTable);
    void writeToFile(string pathOfArchive, string* encryptedTree, string* encryptedData);
    void garbageCollector(map <char, int>* freqTable, Node* root, map<char, string>* codeTable,string* encryptedData, string* encryptedTree);
    list<Node*>& orderedNodeInsert(Node* node, list<Node*> &sortedList);
    list<Node*>* buildLeaves(map<char, int> *freqMap);
    void getEncryptedTree(Node *root, string *encryptedTree);
    void deleteHuffmansTree(Node* root);
    void writeToFile(string pathOfUncompressedFile, string data);
    Node* getTree(ifstream &inFile);
    string getData(Node* root, ifstream &inFile, string pathOfUncompressedFile);
    Node* getDecodedTree(char*& ptr);
    char getCharFromByte(char*& ptr);


};


#endif // ARCHIVER_H
