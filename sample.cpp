#include <iostream>
using namespace std;

class Counter {
public:
    static int count;  
    Counter() {
        count++;  
    }

    static void displayCount() {  
        cout << "Total Counters: " << count << endl;
    }
};


int Counter::count = 0;

int main() {
    Counter a;
    Counter b;
    Counter c;

    
    Counter::displayCount();

    return 0;
}
