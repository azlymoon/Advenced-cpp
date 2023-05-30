#ifndef MY_VECTOR_IMPL_H_
#define MY_VECTOR_IMPL_H_
#include "my_vector.h"

namespace containers {

    template<typename T>
    my_vector<T>::my_vector() {
        capacity_ = 2;
        size_ = 0;
        array_ = static_cast<T*>(operator new[] (capacity_ * sizeof(T)));
    }

    template<typename T>
    my_vector<T>::my_vector(std::size_t n) {
        capacity_ = n;
        size_ = 0;
        array_ = static_cast<T*>(operator new[] (capacity_ * sizeof(T)));
        for (std::size_t i = 0; i < capacity_; i++){
            new (array_ + size_) T();
            size_ += 1;
        }
    }

    template<typename T>
    my_vector<T>::my_vector(my_vector<T> &other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        array_ = static_cast<T*>(operator new[] (capacity_ * sizeof(T)));
        for (std::size_t i = 0; i < size_; i++) {
            array_[i] = other.array_[i];
        }
    }

    template<typename T>
    my_vector<T>::~my_vector() {
        operator delete[] (array_, capacity_ * sizeof(T));
    }

    template<typename T>
    std::size_t my_vector<T>::size() const {
        return size_;
    }

    template<typename T>
    std::size_t my_vector<T>::capacity() const {
        return capacity_;
    }

    template<typename T>
    bool my_vector<T>::empty() const {
        if (size_ == 0) {
            return true;
        } else {
            return false;
        }
    }

    template<typename T>
    void my_vector<T>::reserve(std::size_t n) {
        if (n > capacity_) {
            T* tmp_data = static_cast<T*> (operator new[] (n * sizeof(T)));
            for (std::size_t i = 0; i < size_; i++)
                tmp_data[i] = array_[i];
            operator delete[] (array_, capacity_ * sizeof(T));
            array_ = tmp_data;
            capacity_ = n;
        }
    }

    template<typename T>
    void my_vector<T>::resize(std::size_t n) {
        if (n > capacity_) {
            std::size_t new_capacity = (n > capacity_ * 2 ? n : capacity_ * 2);
            this->reserve(new_capacity);
            for (std::size_t i = size_; i < n; i++) {
                new(array_ + i) T();
            }
        }
        size_ = n;
    }

    template<typename T>
    my_vector<T> &my_vector<T>::operator=(const my_vector<T> &other) {
        if (&other == this)
            return *this;

        operator delete[] (array_, capacity_ * sizeof(T));
        size_ = other.size_;
        capacity_ = other.capacity_;
        array_ = static_cast<T*>(operator new[] (capacity_ * sizeof(T)));
        for (std::size_t i = 0; i < capacity_; i++) {
            new (array_ + i) T();
        }
        return *this;
    }

    template<typename T>
    void my_vector<T>::push_back(const T& t) {
        resize(size_ + 1);
        array_[size_ - 1] = t;
    }

    template<typename T>
    void my_vector<T>::pop_back() {
        resize(size_ - 1);
    }

    template<typename T>
    void my_vector<T>::clear() {
        resize(0);
    }

    template<typename T>
    T &my_vector<T>::operator[](std::size_t index) {
        return array_[index];
    }

    template<typename T>
    const T &my_vector<T>::operator[](std::size_t index) const {
        return array_[index];
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, my_vector<T> const& vec) {
        for (std::size_t i = 0; i < vec.size() - 1; i++) {
            os << vec[i] << ' ';
        }
        os << vec[vec.size() - 1];
        return os;
    }
}

#endif // MY_VECTOR_IMPL_H_