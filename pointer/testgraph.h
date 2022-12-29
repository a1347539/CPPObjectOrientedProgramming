#include <queue>
#include <set>
#include <ostream>
#include "testsmartptr.h"

using namespace std;

class Node {
    private:
        static const unsigned int init_capacity = 10;
        char val;
        TestSmartPtr* out;
        unsigned int capacity;
        unsigned int size_p;

    public:
        Node(const char& val);
        Node(const Node& that);
        ~Node();
        char& operator*();
        const char& operator*() const;
        unsigned int degree() const;
        unsigned int size() const;
        TestSmartPtr operator[](unsigned int i) const;
        void add(TestSmartPtr n);
        void remove(TestSmartPtr n);
        bool exists(TestSmartPtr n) const;
        TestSmartPtr find(char val) const;
};



Node::Node(const char& val) {
    this->val = val;
    out = new TestSmartPtr[init_capacity];
    capacity = init_capacity;
    size_p = 0;
}

unsigned int Node::degree() const {
    out[4].is_null();
}

bool Node::exists(TestSmartPtr n) const {
    for (int i = 0; i < size_p; i++) {
        if (out[i] == n) {
            return true;
        }
    }
    return false;
}

TestSmartPtr Node::find(char val) const {
    if (out == nullptr) {
        return TestSmartPtr{};
    }
    for (int i = 0; i < size_p; i++) {
        if (!out[i].is_null()) {
            if (*out[i] == val) {
                return true;
            }
        }
    }
    return false;
}