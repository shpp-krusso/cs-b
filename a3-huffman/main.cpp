#include <QCoreApplication>
#include <archiver.h>

int main(int argc, char *argv[])
{
    string pathOfOrigin = "/home/kocmuk/Qt-projects/huffman/files/2dyadi.jpg";
    string pathOfArchive = pathOfOrigin + ".myzip";
    string pathOfUncompressedFile = pathOfOrigin + "_unzipped";
    Archiver arch;
    arch.compress(pathOfOrigin, pathOfArchive);
    arch.uncompress(pathOfArchive, pathOfUncompressedFile);
    return 0;
}
