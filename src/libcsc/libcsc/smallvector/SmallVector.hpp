#pragma once

#include <algorithm>
#include <iostream>

namespace libcsc {

template <typename T, unsigned N>
class SmallVector {
   public:
    struct iterator {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T**;
        using reference = T&;

        explicit iterator(pointer ptr) : ptr_(ptr) {}

        T operator*() const { return (**ptr_); }
        T operator->() { return (**ptr_); }

        iterator& operator++() {
            ptr_ = (ptr_ + 1);
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            (*this)++;
            return tmp;
        }

        iterator& operator--() {
            ptr_ = ptr_ - 1;
            return *this;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            (*this)--;
            return tmp;
        }

        iterator operator+(const int n) const { return iterator(ptr_ + n); }

        iterator& operator+=(const int n) {
            ptr_ = ptr_ + n;
            return *this;
        }

        iterator operator-(const int n) const { return iterator(ptr_ - n); }

        iterator& operator-=(const int n) {
            ptr_ = ptr_ - n;
            return *this;
        }

        difference_type operator-(const iterator& it) const {
            return ptr_ - it.ptr_;
        }

        bool operator<(const iterator& it) const { return *ptr_ < it.*ptr_; }

        bool operator<=(const iterator& it) const { return *ptr_ <= it.*ptr_; }

        bool operator>(const iterator& it) const { return *ptr_ > it.*ptr_; }

        bool operator>=(const iterator& it) const { return *ptr_ >= it.*ptr_; }

        friend bool operator==(const iterator& a, const iterator& b) {
            return a.ptr_ == b.ptr_;
        }
        friend bool operator!=(const iterator& a, const iterator& b) {
            return a.ptr_ != b.ptr_;
        }

        reference operator[](const int n) const { return (*(ptr_ + n)); }

       private:
        pointer ptr_;
    };

    SmallVector() {
        arr_ = new T*[N];
        for (size_t i = 0; i < N; i++) {
            arr_[i] = &static_arr_[i];
        }
    }

    SmallVector(SmallVector& other) {
        if (this != &other) {
            arr_ = new T*[other.capacity_];
            std::copy(other.static_arr_, other.static_arr_ + N, static_arr_);
            for (size_t i = 0; i < N; i++) {
                arr_[i] = &static_arr_[i];
            }
            if (other.capacity_ > N) {
                delete[] dynamic_arr_;
                dynamic_arr_ = new T[other.capacity_ - N];
                std::copy(
                    other.dynamic_arr_,
                    other.dynamic_arr_ + other.size_ - N,
                    dynamic_arr_);
                for (size_t i = N; i < other.capacity_; i++) {
                    arr_[i] = &dynamic_arr_[i - N];
                }
            }
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
    }
    SmallVector(SmallVector&& other) noexcept {
        if (this != &other) {
            delete[] dynamic_arr_;
            delete[] arr_;
            arr_ = other.arr_;
            dynamic_arr_ = other.dynamic_arr_;
            std::move(other.static_arr_, other.static_arr_ + N, static_arr_);
            for (size_t i = 0; i < N; i++) {
                arr_[i] = &static_arr_[i];
            }
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.dynamic_arr_ = nullptr;
            other.arr_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
    }

    ~SmallVector() {
        delete[] dynamic_arr_;

        delete[] arr_;
    }

    [[nodiscard]] bool is_empty() const { return size_ == 0; }

    [[nodiscard]] size_t size() const { return size_; }

    [[nodiscard]] size_t capacity() const { return capacity_; }

    [[nodiscard]] size_t static_capacity() const { return N; }

    void push_back(const T& value) {
        if (size_ < N) {
            static_arr_[size_] = value;
        } else {
            if (size_ >= capacity_) {
                add_memory();
            }
            dynamic_arr_[size_ - N] = value;
        }
        size_++;
    }

    void remove(size_t index) {
        if (index < N) {
            for (size_t i = index + 1; i < (size_ < N ? size_ : N); i++) {
                static_arr_[i - 1] = static_arr_[i];
            }
            if (size_ > N) {
                static_arr_[N - 1] = dynamic_arr_[0];
                for (size_t i = 1; i < size_ - N; i++) {
                    dynamic_arr_[i - 1] = dynamic_arr_[i];
                }
            }

        } else {
            for (size_t i = index + 1 - N; i < size_ - N; ++i) {
                dynamic_arr_[i - 1] = dynamic_arr_[i];
            }
        }
        --size_;
    }

    void clear() {
        delete[] dynamic_arr_;
        dynamic_arr_ = nullptr;
        delete[] arr_;
        arr_ = new T*[N];
        for (size_t i = 0; i < N; i++) {
            arr_[i] = &static_arr_[i];
        }
        size_ = 0;
        capacity_ = N;
    }

    T& operator[](size_t index) {
        return (index < N ? static_arr_[index] : dynamic_arr_[index - N]);
    }

    const T& operator[](size_t index) const {
        return (index < N ? static_arr_[index] : dynamic_arr_[index - N]);
    }

    iterator begin() { return iterator(arr_); }

    const iterator begin() const { return iterator(arr_); }

    iterator end() { return iterator(arr_ + size_); }

    const iterator end() const { return iterator(arr_ + size_); }

    SmallVector& operator=(SmallVector& other) {
        if (this != &other) {
            arr_ = new T*[other.capacity_];
            std::copy(other.static_arr_, other.static_arr_ + N, static_arr_);
            for (size_t i = 0; i < N; i++) {
                arr_[i] = &static_arr_[i];
            }
            if (other.capacity_ > N) {
                delete[] dynamic_arr_;
                dynamic_arr_ = new T[other.capacity_ - N];
                std::copy(
                    other.dynamic_arr_,
                    other.dynamic_arr_ + other.size_ - N,
                    dynamic_arr_);
                for (size_t i = N; i < other.capacity_; i++) {
                    arr_[i] = &dynamic_arr_[i - N];
                }
            }
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
        return *this;
    }

    SmallVector& operator=(SmallVector&& other) {
        if (this != &other) {
            delete[] dynamic_arr_;
            delete[] arr_;
            arr_ = other.arr_;
            dynamic_arr_ = other.dynamic_arr_;
            std::move(other.static_arr_, other.static_arr_ + N, static_arr_);
            for (size_t i = 0; i < N; i++) {
                arr_[i] = &static_arr_[i];
            }
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.dynamic_arr_ = nullptr;
            other.arr_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
        return *this;
    }

   private:
    T* dynamic_arr_{};
    T static_arr_[N]{};
    size_t size_{};
    size_t capacity_ = N;

    T** arr_{};

    void add_memory() {
        if (dynamic_arr_ == nullptr)
            dynamic_arr_ = new T[1];

        delete[] arr_;

        capacity_ *= 2;
        T* tmp = dynamic_arr_;
        dynamic_arr_ = new T[capacity_ - N];
        for (size_t i = 0; i < size_ - N; ++i)
            dynamic_arr_[i] = tmp[i];
        delete[] tmp;

        arr_ = new T*[capacity_];
        for (size_t i = 0; i < N; i++) {
            arr_[i] = &static_arr_[i];
        }
        for (size_t i = N; i < capacity_; i++) {
            arr_[i] = &dynamic_arr_[i - N];
        }
    }
};

}  // namespace libcsc