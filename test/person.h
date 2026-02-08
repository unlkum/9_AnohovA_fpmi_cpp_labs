
class Person {
   public:
    std::string name;
    int* age = nullptr;

    // constructors
    Person() = default;

    explicit Person(const std::string& name_val) : name(name_val) {
    }

    explicit Person(const std::string& name_val, int age_val) : name(name_val), age(new int{age_val}) {
    }

    // constructor copy - MyClass a = b; / MyClass a(b);
    explicit Person(const Person& other) : name(other.name), age(new int{*other.age}) {
    }

    // Operator =  (a = b)
    Person& operator=(const Person& other) {
        if (this != &other) {
            delete age;
            name = other.name;
            age = new int{*other.age};
        }
        return *this;
    }

    // delete
    ~Person() {
        delete age;
    }
};

std::ostream& operator<<(std::ostream& os, const Person& a) {
    os << a.name << ' ' << (a.age ? *a.age : 0);
    return os;
}