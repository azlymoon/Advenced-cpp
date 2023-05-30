#include <iostream>
#include <string>
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
    int n = 5;
    A* array_of_A = static_cast<A*> (operator new[] (n * sizeof(A)));
    A* tmp = static_cast<A*> (operator new[] (n * sizeof(A)));;
    A* array;

    for (int i = 0; i < n; i++) {
        new (array_of_A + i) A();
    }

    for (int i = 0; i < n; i++)
        tmp[i] = array_of_A[i];

    printf("%#X\n", array_of_A);
    printf("%#X\n", array);


    for (int i = 0; i < n; i++){
        cout << tmp[i].age() << " " << tmp[i].name() << endl;
    }

    return 0;

}