#include "library.h"

#include <iostream>

int main() {
    try {
        Library lib;
        lib.loadFromFile("data.txt");

        std::cout << "All books:\n";
        lib.print();
        std::cout << "\n";

        std::cout << "Add new book:\n";
        Book b(777, "Design Patterns", 1994);
        b.addAuthor({"Erich", "-", "Gamma"});
        lib.add(b);
        lib.print();
        std::cout << "\n";

        std::cout << "Find by author:\n";
        lib.findByAuthor("Stroustrup");
        std::cout << "\n";

        std::cout << "Modify 'Introduction to Algorithms':\n";
        Book* found = lib.find("Introduction to Algorithms");
        if (found) {
            found->removeAuthor("Cormen");
            found->addAuthor({"Ivanov", "I.", "I."});
            std::cout << *found << std::endl;
        } else {
            std::cout << "Book not found\n";
        }
        std::cout << "\n";

        std::cout << "Remove 'Clean Code':\n";
        lib.remove("Clean Code");
        lib.print();

    } catch (const std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    return 0;
}