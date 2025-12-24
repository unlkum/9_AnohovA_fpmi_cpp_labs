#pragma once
#include <iostream>
#include <list>
#include <string>

struct Author {
    std::string first;
    std::string middle;
    std::string last;

    bool operator<(const Author& other) const;
    bool operator==(const Author& other) const;
};

class Book {
   private:
    size_t number_;
    std::list<Author> authors_;
    std::string name_;
    size_t year_;

   public:
    Book();
    Book(size_t number, std::string name, size_t year);

    void addAuthor(const Author& author);
    void removeAuthor(const std::string& last);
    bool hasAuthor(const std::string& last) const;
    void sortAuthors();

    const std::string& getName() const;
    const std::list<Author>& getAuthors() const;
    size_t getNumber() const;
    size_t getYear() const;

    bool operator<(const Book& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Book& book);
};