
#include "database.h"

#include <algorithm>
#include <fstream>
#include <iomanip>

// Mark
bool Mark::isBad() const {
    if (mark_ <= 3) {
        return true;
    }
    return false;
}

// StudentData
void StudentData::calculateAverage() {
    if (marks_.empty()) {
        average_ = 0.0;
        return;
    }
    double sum = 0;
    for (const auto& m : marks_) {
        sum += m.mark_;
    }
    average_ = sum / marks_.size();
}

size_t StudentData::getSum() const {
    size_t sum = 0;
    for (const auto& m : marks_) {
        sum += m.mark_;
    }
    return sum;
}

bool StudentData::hasBadGrades() const {
    for (const auto& m : marks_) {
        if (m.isBad()) {
            return true;
        }
    }
    return false;
}

// Database
bool addStudent(std::map<size_t, StudentData>& students_, const StudentData& student) {
    auto [it, inserted] = students_.try_emplace(student.number_, student);
    return inserted;
}

void Database::readFromFile(const std::string& filename) {
    std::ifstream file{filename};
    if (!file.is_open()) {
        throw std::runtime_error("File not found");
    }

    size_t str_counter = 0;

    std::string str;
    while (std::getline(file, str)) {
        if (str.empty()) {
            continue;
        }
        std::stringstream line(str);

        StudentData student;
        line >> student.name_ >> student.number_;
        student.index_ = ++str_counter;

        std::string subject;
        size_t mark;
        while (line >> subject >> mark) {
            student.marks_.push_back({subject, mark});
        }
        student.calculateAverage();

        if (!addStudent(students_, student)) {
            // we can log it somehow
            std::cout << "There was already a student with this number!\n";
        }
    }
    std::cout << "Data loaded. Total students: " << students_.size() << '\n';
}

void Database::printStudentLine(std::ostream& os, const StudentData& s, bool showAvg) const {
    os << std::left << std::setw(5) << s.index_;
    os << std::setw(15) << s.name_ << std::setw(7) << s.number_;

    if (showAvg) {
        os << " | AVG: " << std::fixed << std::setprecision(1) << std::setw(6) << s.average_;
    }

    for (const auto& m : s.marks_) {
        os << std::setw(5) << m.subject_ << std::setw(3) << m.mark_ << ' ';
    }
    os << '\n';
}

void Database::printToStream(std::ostream& os, PrintMode mode) const {
    struct IndexedStudent {
        size_t number;
        const StudentData* data;
    };

    std::vector<IndexedStudent> list;

    for (const auto& [n, s] : this->students_) {
        list.push_back({s.index_, &s});
    }

    std::string title;
    switch (mode) {
        case PrintMode::Original:
            title = "STUDENTS LIST (ORIGINAL FILE ORDER)";
            std::sort(
                list.begin(), list.end(), [](const IndexedStudent& a, const IndexedStudent& b) {
                    return a.data->index_ < b.data->index_;
                });
            break;
        case PrintMode::SortCards:
            title = "SORTED STUDENTS (WITH CARD NUM)";
            break;
        case PrintMode::SortName:
            title = "STUDENTS SORTED (BY NAME)";
            std::sort(
                list.begin(), list.end(), [](const IndexedStudent& a, const IndexedStudent& b) {
                    if (a.data->name_ == b.data->name_) {
                        return a.data->average_ > b.data->average_;
                    }
                    return a.data->name_ < b.data->name_;
                });
            break;
        case PrintMode::Average:
            title = "STUDENTS REPORT (WITH AVERAGE GRADE)";
            break;
        case PrintMode::SortAvg:
            title = "SORTED STUDENTS (WITH AVERAGE GRADE)";
            std::sort(
                list.begin(), list.end(), [](const IndexedStudent& a, const IndexedStudent& b) {
                    return a.data->average_ > b.data->average_;
                });
    }

    os << "\n" << title << "\n";
    for (const auto& item : list) {
        bool showAvg = false;
        if (mode == PrintMode::Average || mode == PrintMode::SortAvg) {
            showAvg = true;
        }
        printStudentLine(os, *item.data, showAvg);
    }
}

void Database::printOriginal(std::ostream& os) const {
    printToStream(os, PrintMode::Original);
}

void Database::printAveragePoint(std::ostream& os) const {
    printToStream(os, Database::PrintMode::Average);
}

void Database::printCardSorted(std::ostream& os) const {
    printToStream(os, PrintMode::SortCards);
}

void Database::printNameSorted(std::ostream& os) const {
    printToStream(os, Database::PrintMode::SortName);
}

void Database::printFromRange(std::ostream& os, const double min, const double max) const {
    os << "\nSTUDENTS IN RANGE\n";

    std::vector<const StudentData*> filtered;
    for (const auto& [id, s] : students_) {
        if (s.average_ >= min && s.average_ <= max) {
            filtered.push_back(&s);
        }
    }

    std::sort(filtered.begin(), filtered.end(), [](const StudentData* a, const StudentData* b) {
        return a->average_ > b->average_;
    });

    for (const auto* s : filtered) {
        printStudentLine(os, *s, true);
    }

    // printToStream(os, Database::PrintMode::SortAvg);
}

void Database::printWithSubject(std::ostream& os, std::string subject) const {
    os << "\nSTUDENTS WITH SUBJECT " << subject << " :\n";

    for (const auto& [id, s] : students_) {
        bool has_subject = std::any_of(s.marks_.begin(), s.marks_.end(), [&subject](const Mark& m) {
            return m.subject_ == subject;
        });

        if (has_subject) {
            printStudentLine(os, s, false);
        }
    }
}

void Database::printSubjectStatistics(std::ostream& os) {
    struct SubjectData {
        size_t count_ = 0;
        double sum_ = 0.0;
    };

    std::map<std::string, SubjectData> stats_map;

    for (const auto& [n, s] : students_) {
        for (const auto& m : s.marks_) {
            stats_map[m.subject_].count_++;
            stats_map[m.subject_].sum_ += m.mark_;
        }
    }
    os << "\nSTUDENTS PER SUBJECT\n";
    for (const auto& [subject, data] : stats_map) {
        os << subject << ' ' << data.count_ << '\n';
    }

    std::vector<std::pair<std::string, double>> stats_vec;
    for (const auto& [subject, data] : stats_map) {
        double average = data.sum_ / data.count_;
        stats_vec.emplace_back(subject, average);
    }
    typedef std::pair<std::string, double> Element;
    std::sort(stats_vec.begin(), stats_vec.end(), [](const Element& a, const Element& b) {
        return a.second > b.second;
    });

    os << "\nSORTED SUBJECTS BY AVERAGE POINTS\n";
    for (const auto& el : stats_vec) {
        os << el.first << " - " << std::fixed << std::setprecision(2) << el.second << "\n";
    }
}

void Database::printBestStudents(std::ostream& os) {
    if (students_.empty()) {
        return;
    }

    size_t max_sum = 0;
    for (const auto& [id, s] : students_) {
        size_t current_sum = s.getSum();
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    os << "\nSTUDENTS WITH MAX SUM: " << max_sum << "\n";
    for (const auto& [id, s] : students_) {
        if (s.getSum() == max_sum) {
            printStudentLine(os, s, true);
        }
    }
}

void Database::printBadStudents(std::ostream& os) {
    os << "\nSTUDENTS WITH BAD GRADES\n";
    bool found = false;

    for (const auto& [id, s] : students_) {
        if (s.hasBadGrades()) {
            printStudentLine(os, s, true);
            found = true;
        }
    }

    if (!found) {
        os << "No students with bad grades found!\n";
    }
}

// а что если в файле введут double отметку?