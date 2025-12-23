#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <utility>

class Vector {
   private:
    size_t size_;
    size_t capacity_;
    int* data_;

    void Reallocate(size_t new_capacity) {
        int* new_data = new int[new_capacity];

        std::copy(data_, data_ + size_, new_data);

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

   public:
    // Конструктор по умолчанию
    Vector() : size_(0), capacity_(0), data_(nullptr) {
    }

    // Конструктор, принимающий размер вектора и заполняющий его нулями
    explicit Vector(size_t size)
        : size_(size), capacity_(size), data_(size > 0 ? new int[size] : nullptr) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = 0;
        }
    }

    // Принимающий std::intitializer_list<int> — Vector v{1, 2, 3, 4, 5};
    Vector(std::initializer_list<int> list)
        : size_(list.size())
        , capacity_(list.size())
        , data_(list.size() > 0 ? new int[list.size()] : nullptr) {
        std::copy(list.begin(), list.end(), data_);
    }

    // Конструктор копирования Vector b = a; или Vector b(a)
    Vector(const Vector& other)
        : size_(other.size_), capacity_(other.capacity_), data_(new int[other.capacity_]) {
        std::copy(other.data_, other.data_ + size_, data_);
    }

    // Оператор присваивания копированием b = a;
    Vector& operator=(Vector other) {
        this->Swap(other);

        return *this;
    }

    // Метод Swap, который принимает другой вектор по ссылке и меняет содержимое текущего вектора
    void Swap(Vector& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    // Метод At (неконстантный)
    int& At(size_t ind) {
        if (ind >= size_) {
            throw std::out_of_range("Vector::at() - Index out of range");
        }
        return data_[ind];
    }

    // Метод At (константный)
    const int& At(size_t ind) const {
        if (ind >= size_) {
            throw std::out_of_range("Vector::at() - Index out of range");
        }
        return data_[ind];
    }

    // Метод Size
    size_t Size() const {
        return size_;
    }

    // Метод Capacity
    size_t Capacity() const {
        return capacity_;
    }

    // Метод PushBack
    void PushBack(const int item) {
        if (size_ >= capacity_) {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            Reallocate(new_capacity);
        }
        data_[size_] = item;
        ++size_;
    }

    // Метод PopBack , который удаляет последний элемент вектора
    void PopBack() {
        if (size_ > 0) {
            --size_;
        }
    }

    // Метод Clear , который делает контейнер пустым
    void Clear() {
        size_ = 0;
    }

    // Метод Reserve принимающий новое capacity
    void Reserve(size_t new_capacity) {
        if (capacity_ >= new_capacity) {
            return;
        }
        Reallocate(new_capacity);
    }

    /*
    Vector(Vector&& other) noexcept
        : size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
        other.size_ = 0;
        other.capacity_ = 0;
        other.data_ = nullptr;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {

            delete[] data_;

            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = other.data_;

            other.size_ = 0;
            other.capacity_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }
    */

    // Оператор индексирования data[i] (для записи/чтения)
    int& operator[](size_t ind) {
        return data_[ind];
    }

    // Константный оператор индексирования data[i] (только для чтения)
    const int& operator[](size_t ind) const {  // для const Vector& v
        return data_[ind];
    }

    // Деструктор
    ~Vector() {
        delete[] data_;
    }
};

std::ostream& operator<<(std::ostream& os, const Vector& v);