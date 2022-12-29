// TODO: Implement the member functions of SmartPtr (Part (A), except the output operator)

template <typename T>
SmartPtr<T>::SmartPtr() {
    ptr = nullptr;
    count = nullptr;
}

template <typename T>
SmartPtr<T>::SmartPtr(const T& val) {
    ptr = new T { val };
    count = new unsigned int { 1 };
}

template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr<T>& that) {
    if (that.ptr == nullptr) {
        ptr = nullptr;
        count = nullptr;
    }
    else {
        ptr = that.ptr;
        *(that.count) += 1;
        count = that.count;
    }
}

template <typename T>
SmartPtr<T>::~SmartPtr() {
    if (ptr == nullptr) {
        return;
    }
    (*count)--;
    if ((*count) == 0) {
        delete ptr;
        ptr = nullptr;
        delete count;
        count = nullptr;
    }
    ptr = nullptr;
    count = nullptr;
}

template <typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T>& that) {
    if (ptr == that.ptr) {
        return *this;
    }
    if (ptr != nullptr) {
        (*count)--;
        if ((*count) == 0) {
            delete ptr;
            ptr = nullptr;
            delete count;
            count = nullptr;
        }
        ptr = nullptr;
        count = nullptr;
    }
    
    if (that.ptr) {
        ptr = that.ptr;
        (*that.count)++;
        count = that.count;
    }
    else {
        ptr = nullptr;
        count = nullptr;
    }
    return *this;
}

template <typename T>
void SmartPtr<T>::set(const T& val) {
    if (ptr == nullptr) {
        ptr = new T { val };
        count = new unsigned int { 1 };
        return;
    }

    (*count)--;
    if ((*count) == 0) {
        delete ptr;
        ptr = nullptr;
        delete count;
        count = nullptr;
    }
    ptr = new T { val };
    count = new unsigned int { 1 };
}

template <typename T>
void SmartPtr<T>::unset() {
    if (ptr == nullptr) {
        return;
    }
    (*count)--;
    if ((*count) == 0) {
        delete ptr;
        ptr = nullptr;
        delete count;
        count = nullptr;
    }
    ptr = nullptr;
    count = nullptr;
}

template <typename T>
bool SmartPtr<T>::is_null() const {
    return ptr?false:true;
}

template <typename T>
bool SmartPtr<T>::operator==(const SmartPtr<T>& that) const {
    return ptr==that.ptr?true:false;
}

template <typename T>
bool SmartPtr<T>::operator!=(const SmartPtr<T>& that) const {
    return ptr!=that.ptr?true:false;
}

template <typename T>
T& SmartPtr<T>::operator*() const {
    return *ptr;
}

template <typename T>
T* SmartPtr<T>::operator->() const {
    return ptr;
}