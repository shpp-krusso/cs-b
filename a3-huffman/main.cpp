#include <iostream>
#include <archiver.h>
using namespace std;

int main(int argc, char *argv[])
{ 
    string pathOfOrigin = "/home/kocmuk/Qt-projects/a3-huffman/test.txt";
    string pathOfArchive = "/home/kocmuk/Qt-projects/a3-huffman/test.myzip";
    Archiver arch = Archiver();

    arch.uncompess(pathOfArchive);
 

  return 0;
}
