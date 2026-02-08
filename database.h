/*
другеи названия плюс ыы все по другому крч
    loadFromFile(string filename): Отвечает за парсинг файла (Задача 1).
    printAll(): Выводит список (Задача 2).
    printSortedByName(): Создает вектор, сортирует его и выводит (Задача 4).
    printByAverageRange(float min, float max): (Задача 5).
    printBySubject(string subject): (Задача 6).
    printSubjectStatistics(): Считает и выводит статистику по предметам (Задачи 7 и 8).
    findBestStudents(): (Задача 9).
    findDebtors(): Ищет двоечников (Задача 10).
*/
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

struct Mark {
    std::string subject_;  // предмет
    size_t mark_;          // оценка
    // TODO
    bool isBad() const;
};

struct StudentData {
    std::string name_;         // фамилия, инициалы
    size_t number_;            // номер зачётки
    std::vector<Mark> marks_;  // результаты сессии

    // TODO
    size_t index_;
    double average_ = 0.0;

    void calculateAverage();
    size_t getSum() const;
    bool hasBadGrades() const;
};

class Database {
   private:
    std::map<size_t, StudentData> students_;
    void printStudentLine(std::ostream& os, const StudentData& s, bool showAvg) const;

   public:
    enum class PrintMode { SortCards, Average, SortName, Original, SortAvg };
    void readFromFile(const std::string& filename);

    void printOriginal(std::ostream& os) const;
    void printCardSorted(std::ostream& os) const;

    void printNameSorted(std::ostream& os) const;
    void printFromRange(std::ostream& os, const double min, const double max) const;

    void printAveragePoint(std::ostream& os) const;

    void printWithSubject(std::ostream& os, std::string subject) const;

    void printToStream(std::ostream& os, PrintMode mode = PrintMode::Original) const;

    void printSubjectStatistics(std::ostream& os);

    void printBestStudents(std::ostream& os);

    void printBadStudents(std::ostream& os);
    // friend std::ostream& operator<<(std::ostream& os, const Database& db);
};