#include <QCoreApplication>
#include <archiver.h>

int main(int argc, char *argv[])
{
    string pathOfOrigin = "/home/kocmuk/Qt-projects/huffman/files/pic.jpg";
    string pathOfArchive = "/home/kocmuk/Qt-projects/huffman/files/pic.myzip";
    string pathOfUncompressedFile = "/home/kocmuk/Qt-projects/huffman/files/uncompressedPic.jpg";
    Archiver arch;
    arch.compress(pathOfOrigin, pathOfArchive);
    arch.uncompress(pathOfArchive, pathOfUncompressedFile);
    return 0;
}
