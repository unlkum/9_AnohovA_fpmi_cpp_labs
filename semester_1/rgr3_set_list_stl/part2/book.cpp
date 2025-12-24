#include "book.h"

Book::Book() : number_(0), year_(0) {
}

Book::Book(size_t number, const std::string& name, size_t year)
    : number_(number), name_(name), year_(year) {
}

void Book::addAuthor(const Author& author) {
    authors_.push_back(author);
}

void Book::sortAuthors() {
    authors_.sort(); // sort by 1 arg
}

bool hasAuthor(const std::string& last) const {
    
}




