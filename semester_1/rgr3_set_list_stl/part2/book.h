#include <cstddef>
#include <list>
#include <string>

struct Author {
    std::string first;
    std::string middle;
    std::string last;

    bool operator<(const Author& other) const {
        return first < other.first;
    }
};

class Book {
   private:
    size_t number_;
    std::list<Author> authors_;
    std::string name_;
    size_t year_;

   public:
    Book();
    Book(size_t number, const std::string& name, size_t year);

    void addAuthor(const Author& author);
    void sortAuthors();
    bool hasAuthor(const) const;

    const std::string& getName() const;
    const std::list<Author>& getAuthors() const;

    bool operator<(const Book& other) const;
};

class Library {
   private:
    std::list<Book> books_;

   public:
    void loadFromFile(const std::string& filename);

    void addBook(const Book& book);
    void removeBook(const std::string& name);

    Book* findBook(const std::string& name);
    void findBooksByAuthor(const std::string& last) const;
};