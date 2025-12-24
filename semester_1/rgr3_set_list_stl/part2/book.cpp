#include "book.h"

bool Author::operator<(const Author& other) const {
    if (last != other.last) {
        return last < other.last;
    }
    if (first != other.first) {
        return first < other.first;
    }
    return middle < other.middle;
}

bool Author::operator==(const Author& other) const {
    return last == other.last && first == other.first && middle == other.middle;
}

Book::Book() : number_(0), year_(0) {
}

Book::Book(size_t number, std::string name, size_t year)
    : number_(number), name_(name), year_(year) {
}

void Book::addAuthor(const Author& author) {
    authors_.push_back(author);
    sortAuthors();
}

void Book::removeAuthor(const std::string& last) {
    authors_.remove_if([&last](const Author& a) { return a.last == last; });
}

bool Book::hasAuthor(const std::string& last) const {
    for (const auto& author : authors_) {
        if (author.last == last) {
            return true;
        }
    }
    return false;
}

void Book::sortAuthors() {
    authors_.sort();
}

const std::string& Book::getName() const {
    return name_;
}

const std::list<Author>& Book::getAuthors() const {
    return authors_;
}

size_t Book::getNumber() const {
    return number_;
}

size_t Book::getYear() const {
    return year_;
}

bool Book::operator<(const Book& other) const {
    return name_ < other.name_;
}

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << book.number_ << " \"" << book.name_ << "\" " << book.year_ << "\n";
    if (book.authors_.empty()) {
        os << " No authors";
    } else {
        for (const auto& a : book.authors_) {
            os << " " << a.last << " " << a.first << " " << a.middle << ";";
        }
    }
    return os;
}