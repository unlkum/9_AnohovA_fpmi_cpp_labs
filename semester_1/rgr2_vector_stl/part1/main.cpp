#include <algorithm>
#include <cstdint>
#include <exception>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

// Safe abs
int64_t SafeAbs(int x) {
    return std::llabs(static_cast<int64_t>(x));
}

// Read Vector of nums
std::vector<int> GetVector() {
    std::vector<int> v;
    std::string input;

    std::cout << "Enter integers (q to finish):\n";

    while (std::cin >> input && input != "q") {
        v.push_back(std::stoi(input));
    }

    if (v.empty()) {
        throw std::runtime_error("Vector is empty");
    }
    return v;
}

// Sum of nums
int64_t Sum(const std::vector<int>& v) {
    return std::accumulate(v.begin(), v.end(), int64_t{0});
}

// Amount of numbers
size_t Size(const std::vector<int>& v) {
    return v.size();
}

// Amount of nums in vector equal to given value
size_t Count(const std::vector<int>& v, const int value) {
    return std::count(v.begin(), v.end(), value);
}

// Amount of numbers that satisfy a condition, such as "greater than n"
size_t CountIf(const std::vector<int>& v, const int value) {
    return std::count_if(v.begin(), v.end(), [value](int element) { return element > value; });
}

// Replace all zeros with the arithmetic mean (take the whole part);
void ReplaceZeroWithAvg(std::vector<int>& v) {
    if (v.empty()) {
        throw std::invalid_argument("Vector is empty");
    }
    int64_t sum = Sum(v);
    int avg = sum / static_cast<int64_t>(v.size());
    std::replace(v.begin(), v.end(), 0, avg);
}

// Sum of numbers from interval [l, r]
int64_t SumOnInterval(const std::vector<int>& v, size_t l, size_t r) {
    if (l > r || r >= v.size()) {
        throw std::out_of_range("Wrong interval");
    }
    return std::accumulate(v.begin() + l, v.begin() + r + 1, int64_t{0});
}

// Add to each element of the vector the sum of all numbers from a given interval
void AddIntervalToEach(std::vector<int>& v, size_t l, size_t r) {
    int64_t total_sum = SumOnInterval(v, l, r);
    std::transform(v.begin(), v.end(), v.begin(), [total_sum](int x) {
        return static_cast<int>(x + total_sum);
    });
}

// Difference between max and min element
int64_t Difference(const std::vector<int>& v) {
    const int64_t min_val = *std::min_element(v.begin(), v.end());
    const int64_t max_val = *std::max_element(v.begin(), v.end());
    return max_val - min_val;
}

// Replace all nums whose modulus is an even number with the difference
void ReplaceEvenWithDiff(std::vector<int>& v) {
    int64_t diff = Difference(v);
    std::transform(
        v.begin(), v.end(), v.begin(), [diff](int x) { return (SafeAbs(x) % 2 == 0) ? diff : x; });
}

// Remove from the sequence all numbers with equal abs values, except the first one
void ReplaceEqualNums(std::vector<int>& v) {
    std::vector<int> result;
    result.reserve(v.size());

    for (int x : v) {
        bool uniq_element = std::none_of(
            result.begin(), result.end(), [x](int y) { return SafeAbs(x) == SafeAbs(y); });
        if (uniq_element) {
            result.push_back(x);
        }
    }
    v.swap(result);
}

// Print vector
void Print(const std::vector<int>& v) {
    std::cout << "\nVector:\n";
    for (int element : v) {
        std::cout << element << ' ';
    }
    std::cout << "\n\n";
}

int main() {
    try {
        std::vector<int> v = GetVector();
        Print(v);

        std::cout << "Sum of numbers: " << Sum(v) << "\n";
        std::cout << "Total number of elements: " << Size(v) << "\n";

        int value;
        std::cout << "Enter value to count: ";
        std::cin >> value;
        std::cout << "Count of equal elements: " << Count(v, value) << "\n";

        int n;
        std::cout << "Enter n (count elements greater than n): ";
        std::cin >> n;
        std::cout << "Count of elements greater than n: " << CountIf(v, n) << "\n\n";

        std::vector<int> copy_v = v;
        ReplaceZeroWithAvg(copy_v);
        std::cout << "After replacing zeros with average:\n";
        Print(copy_v);

        copy_v = v;
        size_t l, r;
        std::cout << "Enter interval l and r: ";
        std::cin >> l >> r;
        AddIntervalToEach(copy_v, l, r);
        std::cout << "After adding interval sum to each element:\n";

        Print(copy_v);

        copy_v = v;
        ReplaceEvenWithDiff(copy_v);
        std::cout << "After replacing even elements with (max - min):\n";
        Print(copy_v);

        copy_v = v;
        ReplaceEqualNums(copy_v);
        std::cout << "After removing equal elements:\n";
        Print(copy_v);

    } catch (const std::exception& e) {
        std::cerr << e.what();
    }

    return 0;
}