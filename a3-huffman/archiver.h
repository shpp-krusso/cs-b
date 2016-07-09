#ifndef ARCHIVER_H
#define ARCHIVER_H
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <list>
#include "mypriorityqueue.h"
using namespace std;

class Archiver
{
public:
    Archiver();
    void compress(string& pathOfOrigin, string& pathOfArchive);
    void uncompress(string& pathOfArchive, string& pathOfUncompressedFile);

    struct Node
    {
        char value;
        int freq;
        Node* left;
        Node* right;
        Node(char value, int freq = 0)
        {
            this->value = value;
            this ->freq = freq;
            left = 0;
            right = 0;
        }

        Node()
        {
            value = 0;
            freq = 0;
            left = 0;
            right= 0;
        }

        Node(Node *left, Node *right)
        {
            this->freq = left->freq + right->freq;
            value = 0;
            this->left = left;
            this->right = right;
        }

        bool operator<(const Node* node)
        {
            return this->freq < node->freq;
        }

        bool operator<=(const Node* node)
        {
            return this->freq <= node->freq;
        }

        bool operator>(const Node* node)
        {
            return this->freq > node->freq;
        }

        bool operator>=(const Node* node)
        {
            return this->freq >= node->freq;
        }
    };
private:
    map<char, int>* buildFreqTable(string &pathOfOrigin);
    Node* buildHuffmanTree(map <char, int>* freqTable);
    void buildSymbolsCodeTable(Node* root, map<char, string>* symbolsCodeTable, string &codeOneSymbol);
    string getEncryptedData(string& pathOfOrigin, map<char, string>* codeTable);
    void writeToFile(string& pathOfArchive, string &encryptedTree, string& encryptedData);
    void freeMemoryAfterCompression(map <char, int>* freqTable, Node* root);
    list<Node*>* orderedNodeInsert(Node* node, list<Node*>* sortedList);
    MyPriorityQueue<Node*>* buildLeaves(map<char, int>* freqMap);
    void getEncryptedTree(Node *root, string& encryptedTree);
    void deleteHuffmanTree(Node* root);
    Node* getTree(ifstream& inFile);
    string getData(Node* root, ifstream& inFile, string &pathOfUncompressedFile);
    Node* getDecodedTree(char* &ptr);
    char getCharFromByte(char* ptr);
};


#endif // ARCHIVER_H
