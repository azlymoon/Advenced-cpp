#include <iostream>
#include <string>
#include <cassert>

#include "my_vector.h"

namespace product {

class Product {
public:
    Product(const char* name, int quantity, double price) {
        name_ = name;
        quantity_ = quantity;
        price_ = price;
    }

    Product() {
        name_ = "Banana";
        quantity_ = 100;
        price_ = 13;
    }

    std::string name() const{
        return name_;
    }

    int quantity() const {
        return quantity_;
    }

    double price() const {
        return price_;
    }

private:
    std::string name_;
    int quantity_;
    double price_;
};

std::ostream &operator<<(std::ostream& os, const product::Product& pr) {
    os << "Product: " << pr.name() << ' ' << pr.quantity() << ' ' << pr.price();
    return os;
}

}  // namespace product

template<typename T>
void test_my_vector(T a, T b){
    containers::my_vector<T> v;
    assert(v.empty());
    assert(v.capacity() == 1);

    v.push_back(a);
    v.push_back(b);
    std::cout << v.capacity() << std::endl;
    assert(v.size() == 2);
    assert(v.capacity() == 2);
    containers::my_vector<T> g = v;
//    std::cout << v << std::endl;
//    std::cout << g << std::endl;

    assert(g.size() == 2);
    assert(g.capacity() == 2);

    v.pop_back();
    assert(v.size() == 1);
    assert(v.capacity() == 2);

    v.clear();
    assert(v.empty());
    assert(v.capacity() == 2);

    g.resize(20);
    assert(g.size() == 20);

    g.reserve(100);
    assert(g.capacity() == 128);

    containers::my_vector<T> c(10);
    assert(c.size() == 10);
    assert(c.capacity() == 16);
    assert(!c.empty());

//    containers::my_vector<T> c;
    c = g;
    assert(c.size() == 20);
    assert(c.capacity() == 128);

    containers::my_vector<T> v2;
    v2.push_back(a);
    v2.push_back(b);
    containers::my_vector<T> v3(v2);
    assert(v3.size() == 2);
    assert(v3.capacity() == 2);
    v2.clear();
    std::cout << v2.empty() << std::endl;
    std::cout << v3 << std::endl;
}

int main() {
	containers::my_vector<int> v;
	v.push_back(2);
	const int n{3};
	v.push_back(n);
	std::cout << v << std::endl;

//    test_my_vector<int>(5, 10);
    test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));

    return 0;
}
