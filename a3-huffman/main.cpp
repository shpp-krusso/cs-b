#include <QCoreApplication>
#include <archiver.h>

int main(int argc, char *argv[])
{
    cout << "If you want to compress the file enter -zip" << endl <<
            "If you want to uncompress the file enter -unzip" << endl << "Enter your choice:";
    string command;
    cin >> command;
    if (command == "-zip") {
        cout << "Enter path of the origin..." << endl << "Enter the path:";
        string pathOfOrigin;
        cin >> pathOfOrigin;
        string pathOfArchive = pathOfOrigin + ".myzip";
        Archiver arch;
        arch.compress(pathOfOrigin, pathOfArchive);
        cout << "Done!" << endl;
    }
    if (command == "-unzip") {
        cout << "Enter path of the archive .myzip ..." << endl;
        string pathOfArchive;
        cin >> pathOfArchive;
        string pathOfUncompressedFile = pathOfArchive + "_unzipped";
        Archiver arch;
        arch.uncompress(pathOfArchive, pathOfUncompressedFile);
        cout << "Done!" << endl;
    } else {
        cout << "The command is not supported! Please, enter a right command." << endl;
    }

    return 0;
}
