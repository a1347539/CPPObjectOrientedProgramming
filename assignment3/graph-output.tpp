// TODO: Implement the output operator<< for Node
#include "graph.h"

template <typename T>
ostream& operator<<(std::ostream& os, const Node<T>& n) {
    int starting = 0;
    os << "Node(" << *n << ",{";
    for (unsigned int i = 0; i < n.size(); i++) {
        if (!n[i].is_null()) {
            os << *(*n[i]);
            starting = i+1;
            break;
        }
    }
    for (unsigned int i = starting; i < n.size(); i++) {
        if (!n[i].is_null()) {
            os << "," << *(*n[i]);
        }
    }
    return (os << "})");
}