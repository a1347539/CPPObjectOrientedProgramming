#include <iostream>

using namespace std;

struct Node {
    int i;
    Node * next = nullptr;
};

struct myInt {
    int i, exp;
    Node * head;
};

Node returnNode() {
    Node x { 5, nullptr};
    return x;
}

int main() {
    myInt * x = new myInt { 4, 5 };
    myInt* y = x;
    myInt myInt1;
    myInt myInt2 {3, 4, new Node{ 5, new Node {3, new Node {4, new Node {2, new Node {3, new Node {1, nullptr}}}}} }};
    Node * tempMyInt2Node = myInt2.head;
    Node * tempMyInt1Node = myInt1.head;
    Node * prevNode = tempMyInt1Node;

    Node xxx = returnNode();
    cout << xxx.i;

    return 0;
}