#include <iostream>

using namespace std;

class Node {
    public:
        int x;
        int y;

        Node(int x = 5, int y = 6) : x{x}, y{y} {
            cout << "create" << endl;
        }
    
        ~Node() {
            cout << "deleting" << endl;
        }
};

void fun1(Node& n) {
    Node x = n;
    cout << &x << &n << endl;
}

template <typename T>
void fun2(T a) {
    cout << a << endl;
}

int main() {

    fun2("aa");
}