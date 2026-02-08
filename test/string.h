#include <algorithm>
#include <cstring>

class SimpleString {
   public:
    // constructor
    explicit SimpleString(const char* c_str) {
        if (c_str == nullptr) {
            data_ = new char[1]{'\0'};
            return;
        }
        size_t len = std::strlen(c_str);
        data_ = new char[len + 1];
        // std::strcpy(data_, c_str);
        std::copy(c_str, c_str + len + 1, data_);
    }

    // copy constructor a(b) SimpleString a = b;
    SimpleString(const SimpleString& str) : data_(new char[std::strlen(str.data_) + 1]) {
        std::copy(str.data_, str.data_ + std::strlen(str.data_) + 1, data_);
    }

    // operator=  a = b
    // SimpleString& operator=(const SimpleString& other) {
    //     if (this != &other) {
    //         delete[] data_;
    //         size_t len = std::strlen(other.data_);
    //         data_ = new char[len + 1];
    //         std::copy(other.data_, other.data_ + len + 1, data_);
    //     }
    //     return *this;
    // }

    // better operator=
    SimpleString& operator=(SimpleString other) {
        std::swap(data_, other.data_);
        return *this;
    }

    ~SimpleString() {
        delete[] data_;
    }

    const char* CStr() const {
        return data_;
    }

   private:
    char* data_;
};