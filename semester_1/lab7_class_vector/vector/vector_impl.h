#pragma once

#include <initializer_list>
#include <cstddef>
#include <iostream>

class Vector {
private:
    size_t size_;
    size_t capacity_;
    int* data_;

    void Reallocate(size_t new_capacity);

public:
    // Конструктор по умолчанию
    Vector();

    // Конструктор, принимающий размер вектора и заполняющий его нулями
    explicit Vector(size_t size);

    // Принимающий std::intitializer_list<int> — Vector v{1, 2, 3, 4, 5};
    Vector(std::initializer_list<int> list);

    // Конструктор копирования Vector b = a; или Vector b(a)
    Vector(const Vector& other);

    // Оператор присваивания копированием b = a; b(a)
    Vector& operator=(Vector other);

    // Метод Swap, который принимает другой вектор по ссылке и меняет содержимое текущего вектора
    void Swap(Vector& other);

    // Метод At (неконстантный)
    int& At(size_t ind);

    // Метод At (константный)
    const int& At(size_t ind) const;

    // Метод Size
    size_t Size() const;

    // Метод Capacity
    size_t Capacity() const;

    // Метод PushBack
    void PushBack(const int item);

    // Метод PopBack, который удаляет последний элемент вектора
    void PopBack();

    // Метод Clear , который делает контейнер пустым
    void Clear();

    // Метод Reserve принимающий новое capacity
    void Reserve(size_t new_capacity);

    // Оператор индексирования data[i] (для записи/чтения)
    int& operator[](size_t ind);

    // Константный оператор индексирования data[i] (только для чтения)
    const int& operator[](size_t ind) const;  // для const Vector& v

    // Деструктор
    ~Vector();

    /*
    // Vector a, b;
    // a = std::move(b);

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
};

std::ostream& operator<<(std::ostream& os, const Vector& v);
