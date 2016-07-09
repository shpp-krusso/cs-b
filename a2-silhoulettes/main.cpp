#include <Silhouettes_counter.h>
using namespace std;



int main(int argc, char *argv[])
{
    string filePath;
    cout << "Enter the path of image:";
    cin >> filePath;
    Silhouettes_counter counter;
    int amount = counter.count(filePath);
    cout << "-------------result-----------" << endl;
    cout << " The amount of sihouelettes is: " << amount << endl;
    return 0;
}
