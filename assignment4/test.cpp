#include <iostream>
#define _CRTDBG_MAP_ALLOC //to get more details
#include <stdlib.h>  
#include <crtdbg.h>   //for malloc and free

#include "linearProbingHashTable.h"
#include "quadraticProbingHashTable.h"
#include "doubleHashingHashTable.h"
#include "shop.h"

using namespace std;

int (*stringLength)(string, int) = [](string s, int m) { return (int)s.length() % m; };
int (*stringHash)(string, int) = [](string s, int m) {
    //this is an implementation of the hash function seen on p.29 of the hashing lecture notes
    //we are not going to explain it for you
    //consider understanding it part of your task
    //but note that it ignores letter cases intentionally, and assumes input consists of English characters only
    //we also assume the input string won't cause overflow for this function for all test cases
    //it should work for any string with no more than 6 characters
    int r = 0;
    for (unsigned int i = 0;i < s.length();i++)
        r = (s[i] - ((s[i] >= 'a') ? 'a' : 'A') + 1) + r * 37;
    return r % m;
};

//a convenient helper function to print various statistics
void printStats(HashTable* hashTable, bool activeCellCount, bool comparisonCount, bool clusterCount, bool largestClusterSize, bool clusterSizeList)
{
    if (activeCellCount)
        cout << "Active cell count = " << hashTable->getActiveCellCount() << endl;
    if (comparisonCount)
        cout << "Accumulated comparison count = " << hashTable->getAccumulatedComparisonCount() << endl;
    if (clusterCount)
        cout << "Cluster count = " << hashTable->getClusterCount() << endl;
    if (largestClusterSize)
        cout << "Largest cluster size = " << hashTable->getLargestClusterSize() << endl;
    if (clusterSizeList)
        cout << "Cluster size list = " << hashTable->getClusterSizeSortedList() << endl;
}

int getClusterCount(const char* c) {
    int low = 0;
    int high = strlen(c);
    int csize = 0;

    if (c[0] == '1' && c[high-1] == '1') {
        csize++;
        for (int i = high-1; i > 0; i--, high--) {
            if (c[i] == '0') {
                break;
            }

        }
        for (int i = 0; i < high; i++, low++) {
            if (c[i] == '0') {
                break;
            }
        }
    }

    for (int i = low; i < high; i++) {
        if (c[i] == '1') {
            int j = i;
            while (true) {
                if (c[j] == '0') {
                    i = j;
                    break;
                }
                j++;
                if (j > high-1) {
                    i = j - 1;
                    break;
                }
            }
            csize++;
        }
    }

    return csize;
}

int getLargestClusterSize(const char* c) {

    int low = 0;
    int high = strlen(c);
    int size = 0;

    if (c[0] == '1' && c[high-1] == '1') {
        if (strlen(c) == 1) { return 1; }
        for (int i = high-1; i > 0; i--, high--, size++) {
            if (c[i] == '0') {
                break;
            }
        }

        for (int i = 0; i < high; i++, low++, size++) {
            if (c[i] == '0') {
                break;
            }
        }
    }

    for (int i = low; i < high; i++) {
        if (c[i] == '1') {
            int j = i;
            int tempSize = 0;
            while (true) {
                if (c[j] == '0') {
                    i = j;
                    break;
                }
                j++;
                tempSize++;
                if (tempSize > size) {
                    size = tempSize;
                }
                if (j > high - 1) {
                    i = j - 1;
                    break;
                }
            }
        }
    }

    return size;
}

void bubbleSort(int arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

string getClusterSizeSortedList(const char* c) {
    int low = 0;
    int high = strlen(c);
    int maxSize = 5;
    int* sizes = new int[maxSize] {0};
    int sizeCount = 0;

    if (c[0] == '1' && c[high - 1] == '1') {
        int size = 0;
        if (strlen(c) == 1) { 
            delete[] sizes;
            return "1"; 
        }
        for (int i = high - 1; i > 0; i--, high--, size++) {
            if (c[i] == '0') {
                break;
            }
        }

        for (int i = 0; i < high; i++, low++, size++) {
            if (c[i] == '0') {
                break;
            }
        }
        sizes[sizeCount] = size;
        sizeCount++;
    }

    for (int i = low; i < high; i++) {
        if (c[i] == '1') {
            int j = i;
            int tempSize = 0;
            while (true) {
                if (c[j] == '0') {
                    i = j;
                    break;
                }
                j++;
                tempSize++;
                if (j > high - 1) {
                    i = j - 1;
                    break;
                }
            }
            sizes[sizeCount] = tempSize;
            sizeCount++;
        }

        if (sizeCount >= maxSize) {
            int* tempSizes = new int[maxSize * 2] {0};
            for (int i = 0; i < maxSize; i++) {
                tempSizes[i] = sizes[i];
            }
            maxSize *= 2;
            delete[] sizes;
            sizes = new int[maxSize] {0};
            for (int i = 0; i < maxSize; i++) {
                sizes[i] = tempSizes[i];
            }
            delete[] tempSizes;
        }

    }
    bubbleSort(sizes, maxSize);

    string s = "";

    for (int i = 0; i < maxSize; i++) {
        if (sizes[i] == 0) {
            continue;
        }
        if (s != "") { s += ","+to_string(sizes[i]); }
        else { s += to_string(sizes[i]); }
    }

    delete[] sizes;
    if (s == "") {
        return "(empty)";
    }
    return s;
}

int main() {

    {
        Shop* s = new Shop(new DoubleHashingHashTable(3, stringLength, stringHash), 
            new DoubleHashingHashTable(3, stringLength, stringHash), 
            new DoubleHashingHashTable(3, stringLength, stringHash));

        cout << s->stockUp("FireFff", 500, 500);
        cout << s->stockUp("FireFcf", 500, 500);
        cout << s->stockUp("FireFvf", 500, 500);
        cout << s->stockUp("FireFbf", 500, 500);
        cout << s->stockUp("FireFgf", 500, 500);
        cout << s->stockUp("FireFtf", 500, 500);
        cout << s->stockUp("FireFrf", 500, 500);
        cout << s->stockUp("FireFef", 500, 500);

        

        s->print();
        delete s;

    }

    _CrtDumpMemoryLeaks();
    return 0;
    {
        HashTable* hashTable = new LinearProbingHashTable(3, stringLength);
        hashTable->togglePrintSteps();

        Magic* m = new Magic{ "Fire", "Bal", 5, 5 };
        Magic* m1 = new Magic{ "Fire", "Bac", 5, 5 };
        Magic* m2 = new Magic{ "Fire", "Bad", 5, 5 };
        Magic* m3 = new Magic{ "Fire", "Bae", 5, 5 };

        hashTable->add(m);
        hashTable->add(m1);
        hashTable->print();
        hashTable->add(m2);
        hashTable->add(m3);

        hashTable->print();

        delete hashTable;
    }

    _CrtDumpMemoryLeaks();

    return 0;
}