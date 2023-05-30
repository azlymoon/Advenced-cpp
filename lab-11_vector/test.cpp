#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class A {
private:
    int age_;
    string name_;

public:
    A() {
        age_ = 10;
        name_ = "Foo";
    }

    int age() const { return age_;}
    string name() const {return name_; }
};

int main(){
    int n = 16;
    cout << sqrt(n) << endl;
    cout << pow(2, (n % 2 == 0 ? (size_t)sqrt(n) : (size_t)sqrt(n) + 1));
    return 0;

}