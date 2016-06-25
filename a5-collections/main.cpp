#include <myvector.h>
#include <string>
#include <mylist.h>
#include <mypriorityqueue.h>

using namespace std;

int main(int argc, char *argv[]) {
    MyPriorityQueue<string> mpq;
    mpq.push("kjgafsd");
    mpq.push("kjsldjal");
    mpq.push("a;kjpaosf");


    while (!mpq.empty()) {
       cout << mpq.top() << endl;
       mpq.pop();
      }
        return 0;
}
