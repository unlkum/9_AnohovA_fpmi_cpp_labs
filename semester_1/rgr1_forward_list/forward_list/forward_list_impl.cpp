#include "forward_list_impl.h"
#include <cstddef>
#include <cstdint>
#include <iterator>

// your code goes here

// default constructor
ForwardList::ForwardList() : head_(nullptr), size_(0) {
}

// copy constructor (ForwardList b = a;) | (ForwardList b(a);)
ForwardList::ForwardList(const ForwardList& rhs) : head_(nullptr), size_(0) {
    Node* it = rhs.head_;
    Node* last = nullptr;
    while (it != nullptr) {
        Node* node = new Node(it->value_);  // declare node with already filled node->value_
        if (head_ == nullptr) {
            head_ = node;
        } else {
            last->next_ = node;
        }
        last = node;
        it = it->next_;
        ++size_;
    }
}

// Constructs a ForwardList with `count` copies of elements with value `value`.
ForwardList::ForwardList(size_t count, int32_t value) : head_(nullptr), size_(0) {
    for (size_t i = 0; i < count; ++i) {
        PushFront(value);
    }
}

// Constructs a ForwardList with std::initializer_list<int32_t> (ForwardList a{1,2,3};)
ForwardList::ForwardList(std::initializer_list<int32_t> init) : head_(nullptr), size_(0) {
    // 1 2 3 4 | _ 4 3 2 1

    for (std::reverse_iterator<const int*> it = std::rbegin(init); it < std::rend(init); ++it) {
        PushFront(*it);
    }
}

// operator= overloading (a = b;)
// delete old memory and put new
ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this == &rhs) {
        return *this;
    }

    Clear();

    Node* it = rhs.head_;
    Node* last = nullptr;
    while (it != nullptr) {
        Node* node = new Node(it->value_);  // declare node with already filled node->value_
        if (head_ == nullptr) {
            head_ = node;
        } else {
            last->next_ = node;
        }
        last = node;
        it = it->next_;
        ++size_;
    }

    return *this;
}

// destructor
ForwardList::~ForwardList() {
    Clear();
}

// insert new element on the top of the list
void ForwardList::PushFront(int32_t value) {
    Node* start = new Node(value);
    start->next_ = head_;
    head_ = start;
    ++size_;
}

// delete first element of the list
void ForwardList::PopFront() {
    if (head_ == nullptr) {
        return;  // empty list
    }

    Node* temp = head_;
    head_ = temp->next_;
    delete temp;
    --size_;
}

// remove every occurence of an element in the list
// whose value equals to param `value`,
// the remaining elements must remain in the same order
void ForwardList::Remove(int32_t value) {
    // We iterate through the list and remove nodes whose value matches the given value.
    // If the node is the head we update the head ptr. Otherwise we link the previous node to the
    // next one. Each removed node is deleted, while the remaining nodes keep their order

    Node* node = head_;
    Node* last = nullptr;

    while (node != nullptr) {
        Node* next = node->next_;

        if (node->value_ == value) {
            if (node == head_) {  // last == nullptr
                head_ = next;
            } else {
                last->next_ = next;
            }
            delete node;
            --size_;
        } else {
            last = node;
        }
        node = next;
    }
}

// erases all the elements
void ForwardList::Clear() {
    while (head_ != nullptr) {
        PopFront();
    }
}

// find list's element by the `value`
// returns true, if element exists
// otherwise, returns false
bool ForwardList::FindByValue(int32_t value) {
    for (ForwardListIterator it = begin(); it != end(); ++it) {
        if (*it == value) {
            return true;
        }
    }
    return false;
}

// print list's elements to stream separated by space
void ForwardList::Print(std::ostream& out) {
    for (ForwardListIterator it = begin(); it != end(); ++it) {
        out << *it;
        if (std::next(it) != end()) {
            out << ' ';
        }
    }
}

// void ForwardList::Print(std::ostream& out) {
//     Node* it = head_;
//     while (it != nullptr) {
//         out << it->value_;
//         if (it->next_ != nullptr) {
//             out << ' ';
//         }
//         it = it->next_;
//     }
// }

// get first element of the list
int32_t ForwardList::Front() const {
    if (head_ == nullptr) {
        throw std::runtime_error("ForwardList is empty");
    }
    return head_->value_;
}

// get size of the list
size_t ForwardList::Size() const {
    return size_;
}
