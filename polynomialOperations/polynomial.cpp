#include "polynomial.h"
#include <iostream>
using namespace std;
//note: you are not allowed to include any additional library, see also FAQ for what you can/cannot do
//write your code below and submit this file only

Polynomial::Polynomial() {
    head = nullptr;
}

Polynomial::Polynomial(const Polynomial& another) {
    if (another.head == nullptr) { head = nullptr; return; }
    Term * anotherTerm = another.head;

    head = new Term;
    head->coefficient = anotherTerm->coefficient;
    head->exponent = anotherTerm->exponent;
    Term * currentTerm = head;
    anotherTerm = anotherTerm->next;
    for (;anotherTerm; currentTerm = currentTerm->next, anotherTerm = anotherTerm->next) {
        currentTerm->next = new Term();
        currentTerm->next->coefficient = anotherTerm->coefficient;
        currentTerm->next->exponent = anotherTerm->exponent;
    }
    currentTerm->next = nullptr;
}

Polynomial::Polynomial(int array[], int arraySize) {
    if (arraySize == 0) { head = nullptr; return; }
    int startAt = 0;
    for (; startAt < arraySize; startAt++) {
        if (array[startAt] != 0) { break; }
    }
    if (arraySize == startAt) { head = nullptr; return; }
    head = new Term;
    head->coefficient = array[startAt];
    head->exponent = arraySize - startAt - 1;
    Term * h = head;
    for (int i = startAt+1; i < arraySize; i++) {
        if (array[i] == 0) { continue; }
        int exponent = arraySize - i - 1;
        h->next = new Term;
        h->next->coefficient = array[i];
        h->next->exponent = exponent;
        h = h->next;
    }
    h->next = nullptr;
}

//done
Polynomial::~Polynomial() {
    while (head) {
        Term * headNext = head->next;
        delete head;
        head = headNext;
    }
}

//done
void Polynomial::print() const {
    Term * h { head };
    // for (Term * tempTerm = head; tempTerm != nullptr; tempTerm = tempTerm->next, cout << (tempTerm==nullptr) << endl) {
    //     cout << "info: " << tempTerm->coefficient << " " << tempTerm->exponent << endl;
    // }

    if (!head) { cout << "0"; return; }
    
    
    if (h->exponent > 1) { 
        if (abs(h->coefficient) > 1) { cout << h->coefficient << "*x" << "^" << h->exponent; }
        else { 
            if (h->coefficient == -1) { cout <<  "-x" << "^" << h->exponent; }
            else { cout <<  "x" << "^" << h->exponent; }
        }
    }
    else if (h->exponent == 1) { 
        if (abs(h->coefficient) > 1) { cout << h->coefficient << "*x"; }
        else { 
            if (h->coefficient == -1) { cout << "-x"; }
            else { cout << "x"; }
        }
    }
    else { cout << h->coefficient; }
    h = h->next;
    for (; h; h = h->next) {
        cout << " ";
        if (h->coefficient > 0) { cout << "+ "; } 
        else if (h->coefficient == 0) { break; } 
        else { cout << "- "; }
        if (h->exponent > 1) { 
            if (abs(h->coefficient) > 1) { cout << abs(h->coefficient) << "*x" << "^" << h->exponent; }
            else { cout << "x" << "^" << h->exponent; }
        }
        else if (h->exponent == 1) { 
            if (abs(h->coefficient) > 1) { cout << abs(h->coefficient) << "*x"; }
            else { cout << "x"; }
        }
        else { 
            cout << abs(h->coefficient); 
        }
    }

    // Term * tempT { head };
    // int count = 0;
    // for (; tempT; tempT = tempT->next, count++);
    // cout << " , Count is: " << count;

}

Polynomial Polynomial::add(const Polynomial& another) const {
    if (another.head == nullptr && head == nullptr) { return Polynomial(); }
    if (head == nullptr) { return Polynomial(another); }
    if (another.head == nullptr) { return Polynomial(*this); }
    // both polynomials have terms

    Term * addedTerm = new Term;
    Term * addedCurrent = addedTerm;
    
    Term * anotherTerm = another.head;
    Term * thisTerm = head;

    bool firstTermDef = false;
    int tempCoefficient = 0;
    int tempExponent = 0;
    // add first term
    while (thisTerm && anotherTerm && !firstTermDef) {
        if (thisTerm->exponent > anotherTerm->exponent) {
            tempCoefficient = thisTerm->coefficient;
            tempExponent = thisTerm->exponent;
            thisTerm = thisTerm->next;
        } else if (thisTerm->exponent < anotherTerm->exponent) {
            tempCoefficient = anotherTerm->coefficient;
            tempExponent = anotherTerm->exponent;
            anotherTerm = anotherTerm->next;
        } else {
            tempCoefficient = thisTerm->coefficient + anotherTerm->coefficient;
            tempExponent = thisTerm->exponent;
            thisTerm = thisTerm->next;
            anotherTerm = anotherTerm->next;
        }

        if (tempCoefficient == 0) {
            continue;
        }
        addedCurrent->coefficient = tempCoefficient;
        addedCurrent->exponent = tempExponent;
        firstTermDef = true;
    }

    if (!firstTermDef) {
        if (thisTerm) {
            addedCurrent->coefficient = thisTerm->coefficient;
            addedCurrent->exponent = thisTerm->exponent;
            thisTerm = thisTerm->next;
            firstTermDef = true;
        } else if (anotherTerm) {
            addedCurrent->coefficient = anotherTerm->coefficient;
            addedCurrent->exponent = anotherTerm->exponent;
            anotherTerm = anotherTerm->next;
            firstTermDef = true;
        } else {
            delete addedTerm;
            addedTerm = nullptr;
            return Polynomial(); 
        }  
    }

    while (thisTerm && anotherTerm) {
        int newCoefficient = 0;
        int newExponent = 0;
        if (thisTerm->exponent > anotherTerm->exponent) {
            newCoefficient = thisTerm->coefficient;
            newExponent = thisTerm->exponent;
            thisTerm = thisTerm->next;
        } else if (thisTerm->exponent < anotherTerm->exponent) {
            newCoefficient = anotherTerm->coefficient;
            newExponent = anotherTerm->exponent;
            anotherTerm = anotherTerm->next;
        } else {
            newCoefficient = thisTerm->coefficient + anotherTerm->coefficient;
            newExponent = thisTerm->exponent;
            thisTerm = thisTerm->next;
            anotherTerm = anotherTerm->next;
            if (newCoefficient == 0) {
                continue;
            }
        }
        addedCurrent->next = new Term;
        addedCurrent->next->coefficient = newCoefficient;
        addedCurrent->next->exponent = newExponent;

        addedCurrent = addedCurrent->next;
    }

    if (thisTerm) {
        for (;thisTerm ;thisTerm = thisTerm->next, addedCurrent = addedCurrent->next) {
            addedCurrent->next = new Term;
            addedCurrent->next->coefficient = thisTerm->coefficient;
            addedCurrent->next->exponent = thisTerm->exponent;
        }
        addedCurrent->next = nullptr;
    } else if (anotherTerm) {
        for (;anotherTerm ;anotherTerm = anotherTerm->next, addedCurrent = addedCurrent->next) {
            addedCurrent->next = new Term;
            addedCurrent->next->coefficient = anotherTerm->coefficient;
            addedCurrent->next->exponent = anotherTerm->exponent;
        }
        addedCurrent->next = nullptr;
    } else {
        addedCurrent->next = nullptr;
    }

    Polynomial temp;
    temp.head = addedTerm;
    return temp;
}

Polynomial Polynomial::subtract(const Polynomial& another) const {
    if (another.head == nullptr && head == nullptr) { return Polynomial(); }
    if (another.head == nullptr) { return Polynomial(*this); }
    Term * subTerm = new Term;
    Term * subbedCurrent = subTerm;

    Term * anotherTerm = another.head;
    Term * thisTerm = head;
    if (head == nullptr) {
        subbedCurrent->coefficient = anotherTerm->coefficient * -1;
        subbedCurrent->exponent = anotherTerm->exponent;
        anotherTerm = anotherTerm->next;
        for (;anotherTerm; subbedCurrent = subbedCurrent->next, anotherTerm = anotherTerm->next) {
            subbedCurrent->next = new Term();
            subbedCurrent->next->coefficient = anotherTerm->coefficient * -1;
            subbedCurrent->next->exponent = anotherTerm->exponent;
        }
        subbedCurrent->next = nullptr;
        Polynomial temp;
        temp.head = subTerm;
        return temp;
    }

    bool firstTermDef = false;
    int tempCoefficient = 0;
    int tempExponent = 0;
    // add first term
    while (thisTerm && anotherTerm && !firstTermDef) {
        if (thisTerm->exponent > anotherTerm->exponent) {
            tempCoefficient = thisTerm->coefficient;
            tempExponent = thisTerm->exponent;
            thisTerm = thisTerm->next;
        } else if (thisTerm->exponent < anotherTerm->exponent) {
            tempCoefficient = anotherTerm->coefficient * -1;
            tempExponent = anotherTerm->exponent;
            anotherTerm = anotherTerm->next;
        } else {
            tempCoefficient = thisTerm->coefficient - anotherTerm->coefficient;
            tempExponent = thisTerm->exponent;
            thisTerm = thisTerm->next;
            anotherTerm = anotherTerm->next;
        }

        if (tempCoefficient == 0) {
            continue;
        }
        subbedCurrent->coefficient = tempCoefficient;
        subbedCurrent->exponent = tempExponent;
        firstTermDef = true;
    }

    if (!firstTermDef) {
        if (thisTerm) {
            subbedCurrent->coefficient = thisTerm->coefficient;
            subbedCurrent->exponent = thisTerm->exponent;
            thisTerm = thisTerm->next;
            firstTermDef = true;
        } else if (anotherTerm) {
            subbedCurrent->coefficient = anotherTerm->coefficient * -1;
            subbedCurrent->exponent = anotherTerm->exponent;
            anotherTerm = anotherTerm->next;
            firstTermDef = true;
        } else {
            delete subTerm;
            subTerm = nullptr;
            return Polynomial(); 
        }  
    }

    while (thisTerm && anotherTerm) {
        int newCoefficient = 0;
        int newExponent = 0;
        if (thisTerm->exponent > anotherTerm->exponent) {
            newCoefficient = thisTerm->coefficient;
            newExponent = thisTerm->exponent;
            thisTerm = thisTerm->next;
        } else if (thisTerm->exponent < anotherTerm->exponent) {
            newCoefficient = anotherTerm->coefficient * -1;
            newExponent = anotherTerm->exponent;
            anotherTerm = anotherTerm->next;
        } else {
            newCoefficient = thisTerm->coefficient - anotherTerm->coefficient;
            newExponent = thisTerm->exponent;
            thisTerm = thisTerm->next;
            anotherTerm = anotherTerm->next;
            if (newCoefficient == 0) {
                continue;
            }
        }
        subbedCurrent->next = new Term;
        subbedCurrent->next->coefficient = newCoefficient;
        subbedCurrent->next->exponent = newExponent;

        subbedCurrent = subbedCurrent->next;
    }

    if (thisTerm) {
        for (;thisTerm ;thisTerm = thisTerm->next, subbedCurrent = subbedCurrent->next) {
            subbedCurrent->next = new Term;
            subbedCurrent->next->coefficient = thisTerm->coefficient;
            subbedCurrent->next->exponent = thisTerm->exponent;
        }
        subbedCurrent->next = nullptr;
    } else if (anotherTerm) {
        for (;anotherTerm ;anotherTerm = anotherTerm->next, subbedCurrent = subbedCurrent->next) {
            subbedCurrent->next = new Term;
            subbedCurrent->next->coefficient = anotherTerm->coefficient * -1;
            subbedCurrent->next->exponent = anotherTerm->exponent;
        }
        subbedCurrent->next = nullptr;
    } else {
        subbedCurrent->next = nullptr;
    }

    Polynomial temp;
    temp.head = subTerm;
    return temp;
}

Polynomial Polynomial::multiply(const Polynomial& another) const {
    if (head == nullptr || another.head == nullptr) {
        return Polynomial();
    }
    Polynomial result;
    Term* anotherTerm = another.head;
    for (; anotherTerm; anotherTerm = anotherTerm->next) {
        Polynomial temp;
        Term * thisTerm = head;

        temp.head = new Term;
        Term * tempHead = temp.head;
        // multiply first term
        tempHead->coefficient = thisTerm->coefficient * anotherTerm->coefficient;
        tempHead->exponent = thisTerm->exponent + anotherTerm->exponent;
        thisTerm = thisTerm->next;

        for (;thisTerm; thisTerm = thisTerm->next) {
            tempHead->next = new Term;
            tempHead->next->coefficient = thisTerm->coefficient * anotherTerm->coefficient;
            tempHead->next->exponent = thisTerm->exponent + anotherTerm->exponent;
            tempHead = tempHead->next;
        }
        tempHead->next = nullptr;

        Polynomial * tempsrcPoly = new Polynomial { result.add(temp) };
        Term * tempsrc = tempsrcPoly->head;

        while (result.head) {
            Term * nextTerm = result.head->next;
            delete result.head;
            result.head = nextTerm;
        }
        result.head = new Term;
        result.head->coefficient = tempsrc->coefficient;
        result.head->exponent = tempsrc->exponent;
        Term * des = result.head;
        tempsrc = tempsrc->next;
        
        for (; tempsrc; tempsrc = tempsrc->next) {
            des->next = new Term;
            des->next->coefficient = tempsrc->coefficient;
            des->next->exponent = tempsrc->exponent;
            des = des->next;
        }
        des->next = nullptr;
        delete tempsrcPoly;
    }

    return result;
}

void getPowerOf(int array[], int arraySize, int base) {
    array[0] = 1;
    for (int i = 1; i < arraySize; i++) {
        array[i] = base * array[i-1];
    }
}

int Polynomial::evaluate(int valueOfX) const {
    if (head == nullptr) {
        return 0;
    }

    int sum = 0;
    Term * thisHead = head;
    int powerOf[thisHead->exponent+1];
    getPowerOf(powerOf, thisHead->exponent+1, valueOfX);
    for (; thisHead; thisHead = thisHead->next) {
        sum += thisHead->coefficient * powerOf[thisHead->exponent];
    }
    return sum;
}

int Polynomial::compare(const Polynomial& another) const {
    if (head == nullptr && another.head == nullptr) { return 0; }
    if (head == nullptr) { 
        if (another.head->exponent == 0 && another.head->coefficient < 0) {
            return 1;
        }
        return -1; 
    }
    if (another.head == nullptr) { 
        if (head->exponent == 0 && head->coefficient < 0) {
            return -1;
        }
        return 1; 
    }

    Term * thisTerm = head;
    Term * anotherTerm = another.head;

    while (thisTerm && anotherTerm) {
        if (thisTerm->exponent > anotherTerm->exponent) {
            return 1;
        } else if (thisTerm->exponent < anotherTerm->exponent) {
            return -1;
        } else {
            if (thisTerm->coefficient > anotherTerm->coefficient) {
                return 1;
            } else if (thisTerm->coefficient < anotherTerm->coefficient) {
                return -1;
            }
        }
        thisTerm = thisTerm->next;
        anotherTerm = anotherTerm->next;
    }

    if (thisTerm) { return 1; }
    if (anotherTerm) { return -1; }
    return 0;

}
