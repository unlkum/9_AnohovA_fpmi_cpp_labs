#include <iostream>
#include <string>
#include <vector>
#include "string.h"
#include "person.h"

// int arr[100000000];
int main() {
    // std::vector <int> a(100000000);
    // int arr[100000000];
    // static int arr[1000000];,
    // Person p2{};
    // Person p3 = std::string("Ivan");
    // Person p1{"Alex", 19};
    // p2 = p1;
    // std::cout << p1 << '\n' << p2 << '\n';
    // std::cout << p2 << '\n';

    SimpleString str1("Hello");
    std::cout << "str1: " << str1.CStr() << "\n";
    
    SimpleString str2(str1);  // копирующий конструктор
    std::cout << "str2 (copy): " << str2.CStr() << "\n";
    
    SimpleString str3("World");
    str3 = str1;  // присваивание
    std::cout << "str3 (assigned): " << str3.CStr() << "\n";
    
    return 0;
}