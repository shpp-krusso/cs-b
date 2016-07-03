#include <QCoreApplication>
#include <archiver.h>

int main(int argc, char *argv[])
{
    string pathOfOrigin = "/home/kocmuk/Qt-projects/huffman/files/test.txt";
    string pathOfArchive = pathOfOrigin + ".myzip";
    string pathOfUncompressedFile = pathOfOrigin + "_unziped";
    Archiver arch;
    arch.compress(pathOfOrigin, pathOfArchive);
    arch.uncompress(pathOfArchive, pathOfUncompressedFile);
    return 0;
}
