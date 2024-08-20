#include <iostream>
using namespace std;

int main() {
    int* num = new int;
    *num = 10;
    cout << "Value" << *num << endl;
    delete num;
    return 0;
}
