// TODO: Implement the output operator<< for SmartPtr
#include "smartptr.h"

template <typename T>
ostream& operator<<(ostream& os, const SmartPtr<T>& sp) {
    if (sp.ptr == nullptr) { 
        return (os << "SmartPtr()"); 
    }
    return (os << "SmartPtr(" << *(sp.ptr) << "," << *(sp.count) << ")");
}