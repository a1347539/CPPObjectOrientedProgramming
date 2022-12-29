#include <iostream>
#include <string>
#include "smartptr.h"
#include "graph.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;

int main(int argc, char** argv) {

    cout << boolalpha;
    Node<int> n1{ 0 };
    n1.add(new_node(1));
    n1.add(new_node(2));
    n1.add(new_node(3));
    cout << "n1: " << n1 << "\n";
    cout << "n1.size(): " << n1.size() << "\n\n";
    {
        Node<int> n2{ n1 };
        cout << "n2: " << n2 << "\n";
        cout << "n2.size(): " << n2.size() << "\n\n";
    }
    cout << "n1: " << n1 << "\n";
    cout << "n1.size(): " << n1.size() << "\n";
    return 0;
}
