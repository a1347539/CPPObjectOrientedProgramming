#include <ostream>

using namespace std;

ostream& operator<<(ostream& os, const TestSmartPtr& sp);

class TestSmartPtr {
    friend ostream& operator<<(ostream&, const TestSmartPtr&);

    private:
        char* ptr;
        unsigned int* count;

    public:
        TestSmartPtr();
        TestSmartPtr(const char& val);
        TestSmartPtr(const TestSmartPtr& that);
        ~TestSmartPtr();
        TestSmartPtr& operator=(const TestSmartPtr& that);
        void set(const char& val);
        void unset();
        bool is_null() const;
        bool operator==(const TestSmartPtr& that) const;
        bool operator!=(const TestSmartPtr& that) const;
        char& operator*() const;
        char* operator->() const;
};


TestSmartPtr::TestSmartPtr(const TestSmartPtr& that) {
    if (that.ptr == nullptr) {
        ptr = nullptr;
        count = nullptr;
    }
    else {
        ptr = that.ptr;
        (*that.count)++;
        count = that.count;
    }
}

TestSmartPtr::~TestSmartPtr() {
    if (count == 0) {
        delete ptr;
        ptr = nullptr;
        delete count;
        count = nullptr;
    } else {
        (*count)--;
    }
}

TestSmartPtr& TestSmartPtr::operator=(const TestSmartPtr& that) {
    if (ptr == that.ptr) {
        return *this;
    }
    (*count)--;
    if (count == 0) {
        delete ptr;
        ptr = nullptr;
        delete count;
        count = nullptr;
    }
    ptr = that.ptr;
    (*that.count)++;
    count = that.count;

    return *this;
}

void TestSmartPtr::set(const char& val) {
    (*count)--;
    if (count == 0) {
        delete ptr;
        ptr = nullptr;
        delete count;
        count = nullptr;
    }
    ptr = new char { val };
    count = new unsigned int { 1 };
}

void TestSmartPtr::unset() {
    (*count)--;
    if (count == 0) {
        delete ptr;
        ptr = nullptr;
        delete count;
        count = nullptr;
    }
    ptr = nullptr;
    count = nullptr;
}

TestSmartPtr find(TestSmartPtr root, char val) { 
    TestSmartPtr stack { root };
    TestSmartPtr result = recursive_find(stack, root, val);
    return result; 
}

const TestSmartPtr& recursive_find(TestSmartPtr stack, TestSmartPtr root, char val) {
    return TestSmartPtr {};
}