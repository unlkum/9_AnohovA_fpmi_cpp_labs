#include <iostream>
#include <ostream>
#include <string>

struct Student {
    std::string name;
    int age;
    double gpa;

    [[nodiscard]] bool IsHonorsStudent() const {
        return age < 25 && gpa > 4.0;
    }

    // [[nodiscard]] string PrintInfo() const {
    //     return "Name: " + name + " , Age: " + std::to_string(age) + '\n';
    // }

    void WriteTo(std::ostream &os) const {
        os << "Name: " << name << " , Age: " << std::to_string(age) << '\n';
    }
};

static std::ostream& operator<<(std::ostream& os, const Student& a) {
    return os << a.name << ' ' << a.age << '\n';
}

int main () {
    Student a {.name="Alex", .age=24, .gpa=5.0};
    // std::cout << a.PrintInfo();
    // a.WriteTo(std::cout);
    
    std::cout << a;
}

окей, функции структуры вроде +-, 
классы конструкторы деструкторы 
перегрузки операторов всех
правило трех и пяти
и вперед делать лабу 4