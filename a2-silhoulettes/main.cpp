#include <Sihouettes_counter.h>
using namespace std;



int main(int argc, char *argv[])
{
    string filePath = "/home/kocmuk/Qt-projects/a2-silhouettes/2dyadi.jpg";
    Sihouettes_counter counter;
    int amount = counter.count(filePath);
    cout << "-------------result-----------" << endl;
    cout << " The amount of sihouelettes is: " << amount << endl;
    return 0;
}
