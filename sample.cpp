#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string name;     
    int age;         
public:
    void setName(string n) {
        name = n;  
    }

    string getName() const {
        return name;  
    }

    void setAge(int a) {
        if (a > 0) { 
            age = a;
        } else {
            cout << "Invalid age!" << endl;
        }
    }

    int getAge() const {
        return age;  
    }

    void displayInfo() const {
        cout << "Name: " << getName() << ", Age: " << getAge() << endl;
    }
};

int main() {
    Person person1;
    person1.setName("John");
    person1.setAge(25);
    cout << "Person Info:" << endl;
    person1.displayInfo();

    return 0;
}


