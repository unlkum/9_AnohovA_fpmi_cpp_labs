#include "vector_impl.h"

void Vector::Reallocate(size_t new_capacity) {
    int* new_data = new int[new_capacity];
    // UB new_capacity < size_
    std::copy(data_, data_ + size_, new_data);

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

Vector::Vector() : size_(0), capacity_(0), data_(nullptr) {
}

Vector::Vector(size_t size)
    : size_(size), capacity_(size), data_(size > 0 ? new int[size] : nullptr) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = 0;
    }
}

Vector::Vector(std::initializer_list<int> list)
    : size_(list.size()),
      capacity_(list.size()),
      data_(list.size() > 0 ? new int[list.size()] : nullptr) {
    std::copy(list.begin(), list.end(), data_);
}

Vector::Vector(const Vector& other)
    : size_(other.size_), capacity_(other.capacity_), data_(new int[other.capacity_]) {
    std::copy(other.data_, other.data_ + size_, data_);
}

Vector& Vector::operator=(Vector other) {
    this->Swap(other);
    return *this;
}

void Vector::Swap(Vector& other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

int& Vector::At(size_t ind) {
    if (ind >= size_) {
        throw std::out_of_range("Vector::at() - Index out of range");
    }
    return data_[ind];
}

const int& Vector::At(size_t ind) const {
    if (ind >= size_) {
        throw std::out_of_range("Vector::at() - Index out of range");
    }
    return data_[ind];
}

size_t Vector::Size() const {
    return size_;
}

size_t Vector::Capacity() const {
    return capacity_;
}

void Vector::PushBack(const int item) {
    if (size_ >= capacity_) {
        size_t new_capacity = (capacity_ == 0u) ? 1u : capacity_ * 2u;
        Reallocate(new_capacity);
    }
    data_[size_] = item;
    ++size_;
}

void Vector::PopBack() {
    if (size_ > 0) {
        --size_;
    }
}

void Vector::Clear() {
    size_ = 0;
}

void Vector::Reserve(size_t new_capacity) {
    if (capacity_ >= new_capacity) {
        return;
    }
    Reallocate(new_capacity);
}

int& Vector::operator[](size_t ind) {
    return data_[ind];
}

const int& Vector::operator[](size_t ind) const {
    return data_[ind];
}

Vector::~Vector() {
    delete[] data_;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "[";
    for (size_t i = 0; i < v.Size(); ++i) {
        os << v[i];
        if (i + 1 < v.Size()) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
