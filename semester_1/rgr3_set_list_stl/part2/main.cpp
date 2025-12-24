#include <book.h>
#include <exception>
#include <fstream>
#include <iostream>

/*
std::list<Book> library
Book - class
std::set<Author> authors
*/

/*
bool IsEmptyFile(std::ifstream& file) {
    return file.peek() == std::ifstream::traits_type::eof();
}

std::list<Book> readFromFile(const std::string& filename) {
    std::ifstream file{filename};
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open the file \"" + filename + "\"...");
    }

    if (IsEmptyFile(file)) {
        throw std::runtime_error("Error: File \"" + filename + "\" is empty...");
    }

    while (file) {
    }
}
    */

int main() {
    try {
        Library library;

        library.loadFromFile("data.txt");

        std::cout << "Books by Ivanov:\n";
        library.findBooksByAuthor("Ivanov");

        Book* book = library.findBook("C++ Programming");
        if (book) {
            book->addAuthor({"Sidorov", "Sergey", "Ivanovich"});
            book->removeAuthor("Petrov");
        }

        library.removeBook("Algorithms");

    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}