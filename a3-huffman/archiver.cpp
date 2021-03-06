#include "archiver.h"

Archiver::Archiver() {}

/* Returns map that keep frequency of every char in the file*/
map<char, int>* Archiver :: buildFreqTable(string& pathOfOrigin)
{
    ifstream inFile;
    inFile.open(pathOfOrigin.c_str(), ios :: out | ios :: binary);
    map<char, int>* frequencyMap = new map<char, int>;
    char c;
    while (!inFile.eof())
    {
        c = inFile.get();
        (*frequencyMap)[c]++;
    }
    inFile.close();
    return frequencyMap;
}


/* Return a list of nodes, every element contains one element from the map*/
MyPriorityQueue<Archiver :: Node*>* Archiver :: buildLeaves(map<char, int>* freqMap)
{
    MyPriorityQueue<Node*>* leaves = new MyPriorityQueue<Node*>;
    map<char, int> :: iterator iter;
    for (iter = freqMap->begin(); iter != freqMap->end(); iter++)
    {
        Node* leaf = new Node(iter->first, iter->second);
        leaves->push(leaf);
    }

    return leaves;
}

/* Returns a root of huffman tree. Leafs are stored according to its frequency */
Archiver :: Node* Archiver::buildHuffmanTree(map<char, int>* freqTable)
{
    MyPriorityQueue <Node*>* leaves = buildLeaves(freqTable);
    Node* root;
    while (leaves->size() > 1)
    {
        Node* leftChild = leaves->top();
        leaves->pop();
        Node* rightChild = leaves->top();
        leaves->pop();
        Node* parent = new Node(leftChild, rightChild);
        leaves->push(parent);
    }
    root = leaves->top();
    delete leaves;
    return root;
}

/*
 * @param symbolsCodeTable - the table char-> its code in huffman tree
 * @param root - root of huffman tree
 * @param codeOfOneSymbol - code of leaf, that keep current data*/
void Archiver :: buildSymbolsCodeTable(Node* root, map<char, string>* symbolsCodeTable, string& codeOneSymbol)
{
    if (root->left)
    {
        codeOneSymbol += "0";
        buildSymbolsCodeTable(root->left, symbolsCodeTable, codeOneSymbol);
    }
    if (root->right)
    {
        codeOneSymbol += "1";
        buildSymbolsCodeTable(root->right, symbolsCodeTable, codeOneSymbol);
    }
    if (!root->left && !root->right)
    {
        (*symbolsCodeTable)[root->value] = codeOneSymbol;
    }
    codeOneSymbol = codeOneSymbol.substr(0, codeOneSymbol.length() - 1);
}

void Archiver :: getEncryptedTree(Node *root, string& encryptedTree)
{
    if (root->left)
    {
        encryptedTree += "0";
        getEncryptedTree(root->left, encryptedTree);
    }
    if (root->right)
    {
        getEncryptedTree(root->right, encryptedTree);
    }
    if (!root->left || !root->right)
    {
        encryptedTree += "1";
        for (unsigned i = 0; i < 8; i++)
        {
            char ch = root->value;
            if (ch & 1 << (7  -  i))
            {
                encryptedTree += "1";
            }
            else
            {
                encryptedTree += "0";
            }
        }
    }
}

/* Return string data on which every char is encoded according to huffman code*/
string Archiver :: getEncryptedData(string& pathOfOrigin, map<char, string>* codeTable)
{
    string encryptedData;
    encryptedData = "";
    ifstream inFile;
    inFile.open(pathOfOrigin.c_str(), ios :: out | ios :: binary);
    char c;
    while (!inFile.eof())
    {
        c = inFile.get();
        encryptedData += (*codeTable)[c];
    }
    inFile.close();
    return encryptedData;
}

void Archiver :: writeToFile(string& pathOfArchive, string& encryptedTree, string& encryptedData)
{
    ofstream fileOut(pathOfArchive.c_str(), ios::binary);
    int sizeOfTree = encryptedTree.length();
    int sizeOfData = encryptedData.length();

    fileOut << sizeOfTree;
    int position = 0;
    char byte = 0;
    for (unsigned i = 0; i < encryptedTree.length(); i++)
    {
        if ((encryptedTree)[i] == '1')
        {
            byte = byte | (1 << (7 - position));
        }
        else
        {
            byte = byte | (0 << (7 - position));
        }
        position++;
        if (position == 8)
        {
            position = 0;
            fileOut.put(byte);
            byte = 0;
        }
    }
    if (position)
    {
        fileOut.put(byte);
    }

    fileOut << sizeOfData;
    position = byte = 0;
    for (unsigned i = 0; i < encryptedData.size(); i++)
    {
        if (encryptedData[i] == '1')
        {
            byte = byte | (1 << (7 - position));
        }
        else
        {
            byte = byte | (0 << (7 - position));
        }
        position++;
        if (position == 8)
        {
            position = 0;
            fileOut.put(byte);
            byte = 0;
        }
    }
    if (position)
    {
        fileOut.put(byte);
    }
    fileOut.close();
}

void Archiver :: deleteHuffmanTree(Archiver :: Node* root)
{
    if (!root->left)
    {
        deleteHuffmanTree(root->left);
    }
    if (!root->right)
    {
        deleteHuffmanTree(root->right);
    }
    delete root;
}

void Archiver::freeMemoryAfterCompression(map<char, int> *freqTable, Archiver::Node *root)
{
    delete freqTable;
    deleteHuffmanTree(root);
}

void Archiver::compress(string& pathOfOrigin, string& pathOfArchive)
{
    map<char, int>* freqTable = buildFreqTable(pathOfOrigin);
    Node* root = buildHuffmanTree(freqTable);
    map<char, string> codeTable;
    string codeOfSymbol = "";
    buildSymbolsCodeTable(root, &codeTable, codeOfSymbol);
    string encryptedTree = "";
    getEncryptedTree(root, encryptedTree);
    string encryptedData = getEncryptedData(pathOfOrigin, &codeTable);
    writeToFile(pathOfArchive, encryptedTree, encryptedData);
    freeMemoryAfterCompression(freqTable, root);
}

char Archiver :: getCharFromByte(char* ptr)
{
    char ch = 0;
    for (int i = 0; i < 8; i++)
    {
        if (*ptr - '0')
        {
            ch = ch | 1 << (7 - i);
        }
        else
        {
            ch = ch | 0 << (7 - i);
        }
        ptr++;
    }
    return ch;
}

/* Decodes every char */
Archiver :: Node* Archiver :: getDecodedTree(char* &ptr)
{
    if ((*ptr) - '0')
    {
        ptr++;
        char c = 0;
        for(int i = 0; i < 8; i++)
        {
            if((*ptr - '0'))
            {
                c = c | 1 << (7 - i);
                ptr++;
            }
            else
            {
                c = c | 0 << (7 - i);
                ptr++;
            }
        }
        ptr--;
        return new Node(c);
    }
    else
    {
        ptr++;
        Node* left = getDecodedTree(ptr);
        ptr++;
        Node* right = getDecodedTree(ptr);
        return new Node(left, right);
    }
}

/* Return root of huffman tree*/
Archiver :: Node* Archiver :: getTree(ifstream &inFile)
{
    int sizeOfTree;
    inFile >> sizeOfTree;
    string tree = "";

    while(sizeOfTree)
    {
        char c;
        inFile.get(c);
        for (int i = 0; i < 8; i++)
        {
            tree += c & (1 << (7 - i)) ? '1' : '0';
            sizeOfTree--;
            if(!sizeOfTree)
            {
                break;
            }
        }
    }
    char* ptr = &tree[0];
    Node* root = getDecodedTree(ptr);
    return root;
}


/* Return data from encoded file*/
string Archiver :: getData(Node* root, ifstream &inFile, string& pathOfUncompressedFile)
{
    ofstream onFile(pathOfUncompressedFile.c_str());
    int sizeOfData;
    inFile >> sizeOfData;
    string encodedData = "";
    int k = sizeOfData--;
    while(k)
    {
        char c;
        inFile.get(c);
        for (int i = 0; i < 8; i++)
        {
            encodedData += c & (1 << (7 - i)) ? '1' : '0';
            k--;
            if(!k)
            {
                break;
            }
        }
    }
    Node* tempPtr = root;
    string data = "";
    for (int i = 0; i < sizeOfData; i++)
    {
        if (encodedData[i] - '0')
        {
            tempPtr = tempPtr->right;
        }
        else
        {
            tempPtr = tempPtr->left;
        }
        if (!tempPtr->left && !tempPtr->right)
        {
            data += tempPtr->value;
            onFile.put(tempPtr->value);
            tempPtr = root;
        }
    }
    return data;
}

/* Get uncomressed file from archive*/
void Archiver :: uncompress(string& pathOfArchive, string& pathOfUncompressedFile)
{
    ifstream inFile;
    inFile.open(pathOfArchive.c_str(), ios :: out | ios :: binary);
    Node* root = getTree(inFile);
    string data = getData(root, inFile, pathOfUncompressedFile);
    deleteHuffmanTree(root);
}

