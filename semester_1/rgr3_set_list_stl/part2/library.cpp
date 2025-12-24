#include "library.h"

#include <fstream>
#include <iostream>
#include <limits>

void Library::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("File not found");
    }

    while (file.peek() != EOF) {
        size_t num, year, count;
        std::string name;

        file >> num;
        if (file.fail()) {
            break;
        }

        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(file, name);

        file >> year >> count;

        Book b(num, name, year);
        for (size_t i = 0; i < count; ++i) {
            std::string l, f, m;
            file >> l >> f >> m;
            b.addAuthor({f, m, l});
        }
        add(b);
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void Library::add(const Book& book) {
    auto it = books_.begin();
    while (it != books_.end()) {
        if (book < *it) {
            books_.insert(it, book);
            return;
        }
        ++it;
    }
    books_.push_back(book);
}

void Library::remove(const std::string& name) {
    books_.remove_if([&name](const Book& b) { return b.getName() == name; });
}

Book* Library::find(const std::string& name) {
    for (auto& book : books_) {
        if (book.getName() == name) {
            return &book;
        }
    }
    return nullptr;
}

void Library::findByAuthor(const std::string& last) const {
    for (const auto& book : books_) {
        if (book.hasAuthor(last)) {
            std::cout << book << std::endl;
        }
    }
}

void Library::print() const {
    for (const auto& book : books_) {
        std::cout << book << std::endl;
    }
}