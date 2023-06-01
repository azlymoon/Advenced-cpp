//#ifndef MY_VECTOR_IMPL_H_
//#define MY_VECTOR_IMPL_H_
#include <cmath>
#include <cstdint>

namespace containers {

    template<typename T>
    T* my_vector<T>::allocate(std::size_t n) {
        auto* data = new std::uint8_t[n * sizeof(T)];
        return reinterpret_cast<T*>(data);
    }

    template<typename T>
    std::size_t my_vector<T>::cpl2(std::size_t x) {
        std::size_t tmp = 1;
        while (tmp < x) {
            tmp *= 2;
        }
        return tmp;
    }

    template<typename T>
    void my_vector<T>::destroy_items(std::size_t from, std::size_t to) noexcept {
        for (std::size_t i = from; i < to; i++)
            array_[i].~T();
    }

    template<typename T>
    void my_vector<T>::destroy_data() noexcept {
        destroy_items(0, size_);
        auto* data = (std::uint8_t*)array_;
        delete[] data;
    }

    template<typename T>
    my_vector<T>::my_vector() noexcept {
        size_ = 0;
        capacity_ = cpl2(size_);
        array_ = allocate(capacity_);
    }

    template<typename T>
    my_vector<T>::my_vector(std::size_t n) {
        size_ = n;
        capacity_ = cpl2(size_);
        array_ = allocate(capacity_);
        for (std::size_t i = 0; i < size_; i++){
            new (array_ + i) T();
        }
    }

    template<typename T>
    my_vector<T>::my_vector(const my_vector<T> &other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        array_ = allocate(capacity_);
        for (std::size_t i = 0; i < size_; i++) {
            new (array_ + i) T(other.array_[i]);
        }
    }

    template<typename T>
    my_vector<T>::~my_vector() {
          destroy_data();
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
        if (n <= capacity_)
            return;

        std::size_t new_capacity = cpl2(n);
        T* tmp_data = allocate(new_capacity);
        for (std::size_t i = 0; i < size_; i++)
            new (tmp_data + i) T(array_[i]);
        destroy_data();
        array_ = tmp_data;
        capacity_ = new_capacity;
    }

    template<typename T>
    void my_vector<T>::resize(std::size_t n) {
        if (n <= size_) {
            destroy_items(n, size_);
            size_ = n;
            return;
        }

        if (n <= capacity_) {
            for (std::size_t i = size_; i < n; i++)
                new (array_ + i) T();
            size_ = n;
            return;
        }

        std::size_t new_capacity = cpl2(n);
        T* tmp_data = allocate(new_capacity);
        for (std::size_t i = 0; i < size_; i++) {
            new (tmp_data + i) T(array_[i]);
        }
        for (std::size_t i = size_; i < n; i++) {
            new (tmp_data + i) T();
        }
        destroy_data();
        array_ = tmp_data;
        capacity_ = new_capacity;
        size_ = n;
    }

    template<typename T>
    my_vector<T> &my_vector<T>::operator=(const my_vector<T> &other) {
        if (&other == this)
            return *this;

        destroy_data();
        size_ = other.size_;
        capacity_ = other.capacity_;
        array_ = allocate(capacity_);
        for (std::size_t i = 0; i < size_; i++) {
            new (array_ + i) T(other.array_[i]);
        }
        return *this;
    }

    template<typename T>
    void my_vector<T>::push_back(const T& t) {
        reserve(size_ + 1);
        new (array_ + size_++) T(t);
    }

    template<typename T>
    void my_vector<T>::pop_back() {
        size_ -= 1;
    }

    template<typename T>
    void my_vector<T>::clear() {
        size_ = 0;
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

//#endif // MY_VECTOR_IMPL_H_