#include <iostream>
#include <string>

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
    os << "name: " << pr.name() << std::endl;
    os << "quantity: " << pr.quantity() << std::endl;
    os << "price: " << pr.price() << std::endl;
    return os;
}

}  // namespace product

template<typename T>
void test_my_vector(T a, T b){
    containers::my_vector<T> v;
    std::cout << "v.size: " <<  v.size() << " v.capacity: " << v.capacity() << " v.empty: " << v.empty() << std::endl;

    v.push_back(a);
    v.push_back(b);
    std::cout << v << std::endl;
    std::cout << v[0] << std::endl;
    containers::my_vector<T> g = v;
    std::cout << "v.size: " <<  v.size() << " v.capacity: " << v.capacity() << " v.empty: " << v.empty() << std::endl;

    v.pop_back();
    std::cout << "v.size: " <<  v.size() << " v.capacity: " << v.capacity() << " v.empty: " << v.empty() << std::endl;

    v.clear();
    std::cout << "v.size: " <<  v.size() << " v.capacity: " << v.capacity() << " v.empty: " << v.empty() << std::endl;

    std::cout << "g.size: " <<  g.size() << " g.capacity: " << g.capacity() << " g.empty: " << g.empty() << std::endl;
    g.resize(20);
    std::cout << "g.size: " <<  g.size() << " g.capacity: " << g.capacity() << " g.empty: " << g.empty() << std::endl;

    g.reserve(100);
    std::cout << "g.size: " <<  g.size() << " g.capacity: " << g.capacity() << " g.empty: " << g.empty() << std::endl;

    containers::my_vector<T> c(10);
    std::cout << "c.size: " <<  c.size() << " c.capacity: " << c.capacity() << " c.empty: " << c.empty() << std::endl;

    c = g;
    std::cout << "c.size: " <<  c.size() << " c.capacity: " << c.capacity() << " c.empty: " << c.empty() << std::endl;

}

int main() {
	containers::my_vector<int> v;
	v.push_back(2);
	const int n{3};
	v.push_back(n);
	std::cout << v << std::endl;

    test_my_vector<int>(5, 10);
    test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));

    return 0;
}
