#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "IntList.h"

int main()
{
    IntList t;
    t.push_front(3);
    t.push_front(4);
    t.push_back(7);
    cout << t.empty() << endl;
    cout << t << endl;
    return 0;
}