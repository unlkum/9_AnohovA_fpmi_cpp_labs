#pragma once
#include "book.h"

#include <list>
#include <string>

class Library {
   private:
    std::list<Book> books_;

   public:
    void loadFromFile(const std::string& filename);
    void add(const Book& book);
    void remove(const std::string& name);
    Book* find(const std::string& name);
    void findByAuthor(const std::string& last) const;
    void print() const;
};