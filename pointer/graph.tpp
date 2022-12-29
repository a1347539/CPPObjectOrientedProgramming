// TODO: Implement the member functions of Node (Part (B), except the output operator)
//             and the graph operations (Part (C))

template <typename T>
Node<T>::Node(const T& val) {
    this->val = val;
    out = nullptr;
    capacity = 0;
    size_p = 0;
}

template <typename T>
Node<T>::Node(const Node<T>& that) {
    val = that.val;
    out = that.out;
    capacity = that.capacity;
    size_p = that.size_p;
}

template <typename T>
Node<T>::~Node() {
    for (unsigned int i = 0; i < size_p; i++) {
        remove(out[i]);
    }
    delete [] out;
}

template <typename T>
T& Node<T>::operator*() {
    return val;
}

template <typename T>
const T& Node<T>::operator*() const {
    return val;
}

template <typename T>
unsigned int Node<T>::degree() const {
    int count = 0;
    for (unsigned int i = 0; i < size_p; i++) {
        if (!out[i].is_null()) {
            count++;
        }
    }
    return count;
}

template <typename T>
unsigned int Node<T>::size() const {
    return size_p;
}

template <typename T>
SmartPtr<Node<T>> Node<T>::operator[](unsigned int i) const {
    return out[i];
}

template <typename T>
void Node<T>::add(SmartPtr<Node<T>> n) {
    if (n.is_null()) {
        return;
    }
    if (exists(n)) {
        cout << "already exist" << endl;
        return;
    }
    if (&(*n) == this) {
        cout << "adding same node " << endl;
        return;
    }

    if (out == nullptr) {
        out = new SmartPtr<Node<T>>[init_capacity];
    }

    size_p++;
    if (size_p > capacity) {
        capacity *= 2;
    }

    out[size_p-1] = n;
}

template <typename T>
void Node<T>::remove(SmartPtr<Node<T>> n) {
    if (n.is_null()) { return; }
    if (!exists(n)) { return; }
    for (unsigned int i = 0; i < size_p; i++) {
        if (out[i] == n) {
            out[i].unset();
        }
    }
}

template <typename T>
bool Node<T>::exists(SmartPtr<Node<T>> n) const {
    if (n.is_null()) { return false; }
    for (unsigned int i = 0; i < size_p; i++) {
        if (out[i] == n) {
            return true;
        }
    }
    return false;
}

template <typename T>
SmartPtr<Node<T>> Node<T>::find(T val) const {
    for (unsigned int i = 0; i < size_p; i++) {
        if (!out[i].is_null()) {
            if (*(*out[i]) == val) {
                return out[i];
            }
        }
    }
    return SmartPtr<Node<T>> {};
}

template <typename T> 
SmartPtr<Node<T>> new_node(const T& val) {
    return SmartPtr<Node<T>> { val }; 
}

template <typename T> 
void remove_node(SmartPtr<Node<T>> n) {
    // n is pointer to self
    if (n.is_null()) { return; }
    for (unsigned int i = 0; i < (*n).size(); i++) {
        if ((*n)[i].is_null()) { continue; }
        (*(*n)[i]).remove(n);
        (*n).remove((*n)[i]);
    }
}

template <typename T> 
void add_edge(SmartPtr<Node<T>> n1, SmartPtr<Node<T>> n2) {
    if (n1.is_null() or n2.is_null()) { cout << "null node" << endl; return; }
    if (n1 == n2) { cout << "same node" << endl; return; }
    if ((*n1).exists(n2) && (*n2).exists(n1)) { cout << "same connection" << endl; return; }
    (*n1).add(n2);
    (*n2).add(n1);
}

template <typename T> 
void remove_edge(SmartPtr<Node<T>> n1, SmartPtr<Node<T>> n2) {
    if (n1.is_null() or n2.is_null()) { cout << "null node" << endl; return; }
    if (!(*n1).exists(n2) || !(*n2).exists(n1)) { cout << "not connected" << endl; return; }

    (*n1).remove(n2);
    (*n2).remove(n1);

}

template <typename T> 
void remove_graph(SmartPtr<Node<T>> root) {
    SmartPtr<Node<T>> stack { *(*root) };
    recursive_delete(stack, root);
}

template <typename T> 
void recursive_delete(SmartPtr<Node<T>> stack, SmartPtr<Node<T>> root) {
    bool haveNewNeighbor = false;
    
    for (unsigned int i = 0; i < (*root).size(); i++) {
        if ((*root)[i].is_null()) { continue; }
        if ((*stack).exists((*root)[i])) { continue; }
        haveNewNeighbor = true; 
        break; 
    }
    if (!haveNewNeighbor) {
        remove_node(root);
        return;
    }
    (*stack).add(root);
    for (unsigned int i = 0; i < (*root).size(); i++) {
        if ((*root)[i].is_null()) { continue; }
        if ((*stack).exists((*root)[i])) { continue; }
        recursive_delete(stack, (*root)[i]);
    }

    (*stack).remove(root);
    remove_node(root);
}

template <typename T> 
SmartPtr<Node<T>> find(SmartPtr<Node<T>> root, T val) { 
    if (root.is_null()) { return SmartPtr<Node<T>> {}; }
    SmartPtr<Node<T>> found { *(*root) };
    return recursive_find(found, root, val); 
}

template <typename T> 
SmartPtr<Node<T>> recursive_find(SmartPtr<Node<T>> found, SmartPtr<Node<T>> root, T val) {
    if (*(*root) == val) { return root; } 

    bool haveNewNeighbor = false;
    for (unsigned int i = 0; i < (*root).size(); i++) {
        if ((*root)[i].is_null()) { continue; }
        if ((*found).exists((*root)[i])) { continue; }
        haveNewNeighbor = true; 
        break; 
    }
    if (!haveNewNeighbor) {
        return SmartPtr<Node<T>> {};
    }

    (*found).add(root);
    for (unsigned int i = 0; i < (*root).size(); i++) {
        SmartPtr<Node<T>> out {};
        if ((*root)[i].is_null()) { continue; }
        if ((*found).exists((*root)[i])) { continue; }
        out = recursive_find(found, (*root)[i], val);
        if (!out.is_null()) {
            return out;
        }
    }
    return SmartPtr<Node<T>> {};
}

template <typename T> 
bool reachable(SmartPtr<Node<T>> root, SmartPtr<Node<T>> dest) { 
    if (root.is_null() || dest.is_null()) { return false; }
    SmartPtr<Node<T>> found { *(*root) };
    return recursive_reachable(found, root, dest); 
}

template <typename T> 
bool recursive_reachable(SmartPtr<Node<T>> found, SmartPtr<Node<T>> root, SmartPtr<Node<T>> dest) {
    if (root == dest) { return true; } 

    bool haveNewNeighbor = false;
    for (unsigned int i = 0; i < (*root).size(); i++) {
        if ((*root)[i].is_null()) { continue; }
        if ((*found).exists((*root)[i])) { continue; }
        haveNewNeighbor = true; 
        break; 
    }
    if (!haveNewNeighbor) {
        return false;
    }

    (*found).add(root);
    for (unsigned int i = 0; i < (*root).size(); i++) {
        if ((*root)[i].is_null()) { continue; }
        if ((*found).exists((*root)[i])) { continue; }
        if (recursive_reachable(found, (*root)[i], dest)) {
            return true;
        }
    }
    return false;
}