#include "archiver.h"
using namespace std;
Archiver::Archiver() {

}

map <char, int>* Archiver :: getSymbolsFreq(string filePath) {
    ifstream inFile;
    inFile.open(filePath.c_str(), ios :: out | ios :: binary);
    map <char, int>* frequencyMap = new map <char, int>;
    char c;
    while (!inFile.eof()) {
        c = inFile.get();
        (*frequencyMap)[c]++;
    }
    inFile.close();
    cout <<" --------frequencyMap---------------" << endl;
    map<char, int> :: iterator iter;
    for (iter = frequencyMap->begin();iter !=  frequencyMap->end(); iter++) {
        cout << iter->first << " - " << iter->second << endl;
    }
    cout << endl;
    return frequencyMap;
}

list<Node*>& Archiver :: orderedNodeInsert(Node* node, list<Node*> &sortedList) {
    bool isInserted = false;
    if (sortedList.empty()) {
        sortedList.push_back(node);
        isInserted = true;
    }
    else {
        list <Node*> :: iterator iter;
        for (iter = sortedList.begin(); iter != sortedList.end(); iter++) {
            if (node->freq < (*iter)->freq) {
                sortedList.insert(iter, node);
                isInserted = true;
                break;
            }
        }
        if (!isInserted) {
            sortedList.push_back(node);
        }
    }
    return sortedList;
}

list<Node*>* Archiver :: buildLeaves(map<char, int> &freqMap) {
    list<Node*>* leaves = new list<Node*>;
    map<char, int> :: iterator iter;
    for (iter = freqMap.begin(); iter != freqMap.end(); iter++) {
        Node* leaf = new Node(iter->first, iter->second);
        orderedNodeInsert(leaf, *leaves);
    }
    cout << "---------------LEAVES----------------------" << endl;
    list<Node*> :: iterator it;
    for (it = leaves->begin(); it != leaves->end(); it++) {
        cout << (*it)->value << " " << (*it)->freq << endl;
    }
    return leaves;
}

Node* Archiver :: buildTree(list<Node*> * nodeList) {
    list<Node*> :: iterator iter;
    Node* root;
    while (nodeList->size() > 1) {
        for (iter = nodeList->begin(); iter != nodeList->end(); iter++) {
            Node *left = *iter;
            iter++;
            Node *right = *iter;
            root = new Node(left, right);
            nodeList->pop_front();
            nodeList->pop_front();
            *nodeList = orderedNodeInsert(root, *nodeList);
            break;
        }
    }
    return root;
}

void Archiver::printTree(Node* root, unsigned k) { // вывод дерева в консоль
    if(root != 0){
        printTree(root->left, k + 3);
        for(unsigned i = 0; i < k; i++){
            cout << " ";
        }
        if(root->value) cout << root->freq << " (" << root->value << ")" << endl;
        else cout << root->freq << endl;
        printTree(root->right, k + 3);
    }
}

void Archiver :: buildSymbolsCodeTable(Node* root, map<char, string>* symbolsCodeTable, vector <char> &codeOneSymbol) {
    if (root->left && root->right) {
        codeOneSymbol.push_back(0);
        buildSymbolsCodeTable(root->left, symbolsCodeTable, codeOneSymbol);
        codeOneSymbol.push_back(1);
        buildSymbolsCodeTable(root->right, symbolsCodeTable, codeOneSymbol);
    } else {
        string tmp(codeOneSymbol.begin(), codeOneSymbol.end());
        (*symbolsCodeTable)[root->value] = tmp;
    }
    codeOneSymbol.pop_back();
}

void Archiver :: printCodeTable(map<char, string> * symbolsCodeTable) {
    map<char, string> :: iterator iter;
    cout << "--------------Table Code---------------" << endl;
    for (iter = symbolsCodeTable->begin(); iter != symbolsCodeTable->end(); iter++) {
        cout << (*iter).first << " " << (*iter).second << endl;
    }
}

string Archiver :: getEncryptedData(string filePath, map<char, string> *symbolsCodeTable) {
    string encryptedData = "";
    ifstream inFile;
    inFile.open(filePath.c_str(), ios :: out | ios :: binary);
    char c;
    while (!inFile.eof()) {
        c = inFile.get();
        encryptedData += (*symbolsCodeTable)[c];
    }
    inFile.close();
    cout << "------------Encrypted DATA --------------------" << endl;
    cout  << encryptedData << endl;
    return encryptedData;
}

void Archiver :: getEncryptedTree(Node *root, string &encryptedTree) {
    if (root->left || root->right) {
        encryptedTree += "0";
        getEncryptedTree(root->left, encryptedTree);
    }
    if (root->right) {
        getEncryptedTree(root->right, encryptedTree);
    }
    if (!root->left || !root->right) {
        encryptedTree += "1";
        for (unsigned i = 0; i < 8; i++) {
            char ch = root->value;
            if (ch & 1 << (7  -  i)) {
                encryptedTree += "1";
            }
            else {
                encryptedTree += "0";
            }
        }
    }
}

void Archiver :: writeInFile(string &encryptedTree, string &encryptedData) {
    string pathOutputFile = "/home/kocmuk/Qt-projects/a3-huffman/test.myzip";
    ofstream fileOut(pathOutputFile.c_str(), ios::binary);
    int sizeOfTree = 0;
    int sizeOfData = 0;
    fileOut.write(reinterpret_cast<char*>(&sizeOfTree), sizeof(int));
    fileOut.write(reinterpret_cast<char*>(&sizeOfData), sizeof(int));
    int position = 0;
    char byte = 0;
    for (unsigned i = 0; i < encryptedTree.size(); i++) {
        if (encryptedTree[i]) {
            byte = byte | (1 << (7 - position));
            cout << "1";
        }
        else {
            byte = byte | (0 << (7 - position));
            cout << "0";
        }
        position++;
        if (position == 8) {
            cout << "!";
            position = 0;
            fileOut.put(byte);
            byte = 0;
        }
    }
    if (position) {
        fileOut.put(byte);
    }
    position = byte = 0;
    for (unsigned i = 0; i < encryptedData.size(); i++) {
        if (encryptedData[i] == '1') {
            byte = byte | (1 << (7 - position));
        }
        else {
            byte = byte | (0 << (7 - position));
        }
        position++;
        if (position == 8) {
            position = 0;
            fileOut.put(byte);
            byte = 0;
        }
    }
    if (position) {
        fileOut.put(byte);
    }
    fileOut.close();
}
deque<char> Archiver :: addStringtoByteDeque(string s, deque<char> &deq) {
    int position = 0;
    char byte;
    for (unsigned i = 0; i < s.size(); i++) {
        if (s[i]) {
            byte = byte |(1 << (7 - position));
        } else {
            byte = byte | (0 << (7 - position));
        }
        position++;
        if (position == 8) {
            position = 0;
            deq.push_back(byte);
        }
    }
    while (position) {
        byte = byte | (0 << (7 - position));
        position++;
        if (position == 8) {
            position = 0;
            deq.push_back(byte);
        }
    }
    return deq;
}

//deque<char>* Archiver :: getFinalCode(string &encryptedTree, string &encryptedData) {
//    deque<char>* finalCode = new deque<char>;
//    bitset<32>
//     treeSize = "" + encryptedTree.size();
//    *finalCode = addStringtoByteDeque(treeSize, *finalCode);
//    *finalCode = addStringtoByteDeque(encryptedTree, *finalCode);
//    string dataSize = "" + encryptedData.size();
//    *finalCode = addStringtoByteDeque(dataSize, *finalCode);
//    *finalCode = addStringtoByteDeque(encryptedData, *finalCode);
//    return finalCode;
//}

//void Archiver :: writeInFile(string &encryptedTree, string &encryptedData) {
//    deque<char> *finalCode = getFinalCode(encryptedTree, encryptedData);
//    string pathOutputFile = "/home/kocmuk/Qt-projects/a3-huffman/test.myzip";
//    ofstream outFile(pathOutputFile.c_str());
//    while (finalCode->size()) {
//        char c = finalCode->front();
//        finalCode->pop_front();
//        outFile.put(c);
//    }
//    outFile.close();
//}

void Archiver :: compress(string filePath ) {
    map<char, int> *freqMap;
    freqMap = getSymbolsFreq(filePath);
    list<Node*> *nodeList = buildLeaves(*freqMap);
    Node* root = buildTree(nodeList);
    cout << "--------------------TREE#1---------------------------" <<  endl;
    printTree(root, 0);
    map<char, string >* symbolsCodeTable = new map<char, string >;
    vector<char> codeOneSymbol;
    buildSymbolsCodeTable(root, symbolsCodeTable, codeOneSymbol);
    printCodeTable(symbolsCodeTable);
    string encryptedData = getEncryptedData(filePath, symbolsCodeTable);
    string encryptedTree = "";
    getEncryptedTree(root, encryptedTree);
    cout << "-----------------------Encrypted TREE----------" << endl;
    cout << encryptedTree << endl;
//    writeInFile(encryptedTree, encryptedData);
}

deque<char>* Archiver :: readFile(string filePath) {
    deque<char>* encodedFile = new deque<char>;
    ifstream inFile(filePath.c_str());
    char c;
    while (!inFile.eof()) {
        c = inFile.get();
        encodedFile->push_back(c);
    }
    return encodedFile;
}

Node* buildTreeFromEncodedTree(deque<bool> &encodedTree) {

}

Node* Archiver :: getTree(deque<char>* encodedFile) {
    int treeSize = 0;
    for (unsigned i = 0; i < sizeof(string); i++) {
        char c = encodedFile->front();
        int tmp = c - '0';
        treeSize = treeSize*10 + tmp;
        encodedFile->pop_front();
    }
    cout << "treeSize " << treeSize << endl;
    deque<bool> encodedTree;
    for (int i = 0; i < treeSize/8; i++) {
        char byte = encodedFile->front();
        encodedFile->pop_front();
        for (unsigned j = 0; j < 8; j++) {
            bool tmp = false;
            if (byte & (1 <(7 - j))) {
                tmp = true;
            }
            encodedTree.push_back(tmp);
        }
    }
    if (treeSize % 8) {
        char byte = encodedFile->front();
        encodedFile->pop_front();
        for (int j = 0; j < treeSize % 8; j++) {
            bool tmp = false;
            if (byte & (1 <(7 - j))) {
                tmp = true;
            }
            encodedTree.push_back(tmp);
        }
    }
    cout << "-------------encoded tree 2--------------" << endl;
    for (int i = 0; i < encodedTree.size(); i++) {
        cout << encodedTree[i] << " ";
    }
    cout << endl;
//    Node* root = buildTreeFromEncodedTree(encodedTree);
//    return root;
}

void Archiver :: uncompess(string filePath) {
    deque<char>* encodedFile;
    encodedFile = readFile(filePath);
    Node* root = getTree(encodedFile);

}
