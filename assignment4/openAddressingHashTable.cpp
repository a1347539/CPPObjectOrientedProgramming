#include "openAddressingHashTable.h"


OpenAddressingHashTable::OpenAddressingHashTable(int m, int (*hash)(string, int)) : HashTable(m, *hash) {
	table = new Cell[m];
	for (int i = 0; i < m; i++) {
		(table + i)->magic = nullptr;
		(table + i)->status = HashTable::EMPTY;
	}
}
	
OpenAddressingHashTable::~OpenAddressingHashTable() {

	for (int i = 0; i < m; i++) {
		delete (table + i)->magic;
		(table + i)->magic = nullptr;
	}

	delete[] table;
}
	
bool OpenAddressingHashTable::add(Magic* magic) {
	// rehashing should be performed when the number of active cells is 
	// more than half of the hash table size, before adding the new item.


	int i = hi(magic->suffix, 0);
	if (printSteps) {
		cout << "hash(\"" << magic->suffix << "\") = " << i << endl;  // required
	}

	if (activeCellCount > m / 2) {
		performRehashing();
		i = hi(magic->suffix, 0);
	}

	int comparisons = 1;
	while ((table + i)->status == HashTable::ACTIVE) {
		if (printSteps) {
			cout << magic->prefix << magic->suffix << " collided at cell " << i << endl;  // required
		}
		// Add the magic using its suffix as the key
		i = hi(magic->suffix, comparisons);
		if (comparisons >= m) {
			comparisons = m;
			comparisonCount += comparisons;
			if (printSteps) {
				cout << magic->prefix << magic->suffix << " cannot be added" << endl;  // required
			}
			return false;
		}
		comparisons++;
	}

	// simple pointer assignment should be done when you add the magic to the corresponding cell.
	(table + i)->magic = magic;
	(table + i)->status = ACTIVE;
	comparisonCount += comparisons;
	activeCellCount++;
	if (printSteps) {
		cout << magic->prefix << magic->suffix << " added at cell " << i << endl;  // required
	}
	return true;
}

bool OpenAddressingHashTable::remove(string key) {

	int i = hi(key, 0);
	if (printSteps) {
		cout << "hash(\"" << key << "\") = " << i << endl;  // required
	}
	int comparisons = 1;

	while (true) {
		if ((table + i)->status == HashTable::EMPTY) {
			if (printSteps) {
				cout << "visited cell " << i << " but could not find it" << endl;  // required
			}
			comparisonCount += comparisons;

			if (printSteps) {
				cout << key << " cannot be removed" << endl;  // required
			}
			return false;
		}
		else if ((table + i)->status == HashTable::DELETED) {
			if (printSteps) {
				cout << "visited cell " << i << " but could not find it" << endl;  // required
			}
			i = hi(key, comparisons);
			if (comparisons >= m) {
				comparisons = m;
				comparisonCount += comparisons;

				if (printSteps) {
					cout << key << " cannot be removed" << endl;  // required
				}

				return false;
			}
			comparisons++;
		}
		else {
			if ((table + i)->magic->suffix == key) {

				if (printSteps) {
					cout << table[i].magic->prefix << table[i].magic->suffix << " removed at cell " << i << endl;  // required
				}

				// deallocate the magic stored
				delete (table + i)->magic;
				(table + i)->magic = nullptr;
				// set the cell status to DELETED
				(table + i)->status = HashTable::DELETED;

				comparisonCount += comparisons;
				activeCellCount--;

				return true;
			}
			else {
				if (printSteps) {
					cout << "visited cell " << i << " but could not find it" << endl;  // required
				}
				i = hi(key, comparisons);
				if (comparisons >= m) {
					comparisons = m;
					comparisonCount += comparisons;

					if (printSteps) {
						cout << key << " cannot be removed" << endl;  // required
					}

					return false;
				}
				comparisons++;
			}
		}
	}
}

Magic* OpenAddressingHashTable::get(string key) {
	
	int i = hi(key, 0);
	if (printSteps) {
		cout << "hash(\"" << key << "\") = " << i << endl;  // required
	}
	int comparisons = 1;

	while (true) {
		if ((table + i)->status == HashTable::EMPTY) {
			if (printSteps) {
				cout << "visited cell " << i << " but could not find it" << endl;  // required
			}
			comparisonCount += comparisons;
			if (printSteps) {
				cout << key << " cannot be found" << endl;  // required
			}
			return nullptr;
		}
		else if ((table + i)->status == HashTable::DELETED) {
			if (printSteps) {
				cout << "visited cell " << i << " but could not find it" << endl;  // required
			}
			i = hi(key, comparisons);
			if (comparisons >= m) {
				comparisons = m;
				comparisonCount += comparisons;
				if (printSteps) {
					cout << key << " cannot be found" << endl;  // required
				}
				return nullptr;
			}
			comparisons++;
		}
		else {
			if ((table + i)->magic->suffix == key) {
				if (printSteps) {
					cout << table[i].magic->prefix << table[i].magic->suffix << " found at cell " << i << endl;  // required
				}
				comparisonCount += comparisons;
				return (table + i)->magic;
			}
			else {
				if (printSteps) {
					cout << "visited cell " << i << " but could not find it" << endl;  // required
				}
				i = hi(key, comparisons);
				if (comparisons >= m) {
					comparisons = m;
					comparisonCount += comparisons;
					if (printSteps) {
						cout << key << " cannot be found" << endl;  // required
					}
					return nullptr;
				}
				comparisons++;
			}
		}
	}
}

int OpenAddressingHashTable::getClusterCount() const {
	int low = 0;
	int high = m;
	int csize = 0;

	if (table[0].status == HashTable::ACTIVE && table[high - 1].status == HashTable::ACTIVE) {
		csize++;
		for (int i = high - 1; i > 0; i--, high--) {
			if (table[i].status != HashTable::ACTIVE) {
				break;
			}
		}
		for (int i = 0; i < high; i++, low++) {
			if (table[i].status != HashTable::ACTIVE) {
				break;
			}
		}
	}

	for (int i = low; i < high; i++) {
		if (table[i].status == HashTable::ACTIVE) {
			int j = i;
			while (true) {
				if (table[j].status != HashTable::ACTIVE) {
					i = j;
					break;
				}
				j++;
				if (j > high - 1) {
					i = j - 1;
					break;
				}
			}
			csize++;
		}
	}

	return csize;
}

int OpenAddressingHashTable::getLargestClusterSize() const {
	int low = 0;
	int high = m;
	int size = 0;

	if (table[0].status == HashTable::ACTIVE && table[m - 1].status == HashTable::ACTIVE) {
		if (m == 1) { return 1; }
		for (int i = m - 1; i > 0; i--, high--, size++) {
			if (table[i].status != HashTable::ACTIVE) {
				break;
			}
		}
		for (int i = 0; i < high; i++, low++, size++) {
			if (table[i].status != HashTable::ACTIVE) {
				break;
			}
		}
	}

	for (int i = low; i < high; i++) {
		if (table[i].status == HashTable::ACTIVE) {
			int j = i;
			int tempSize = 0;
			while (true) {
				if (table[j].status != HashTable::ACTIVE) {
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

void BubbleSort(int arr[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

string OpenAddressingHashTable::getClusterSizeSortedList() const {
	int low = 0;
	int high = m;
	int maxSize = 10;
	int* sizes = new int[maxSize] {0};
	int sizeCount = 0;

	if (table[0].status == HashTable::ACTIVE && table[high - 1].status == HashTable::ACTIVE) {
		int size = 0;
		if (m == 1) {
			delete[] sizes;
			sizes = nullptr;
			return "1";
		}
		for (int i = high - 1; i > 0; i--, high--, size++) {
			if (table[i].status != HashTable::ACTIVE) {
				break;
			}
		}
		for (int i = 0; i < high; i++, low++, size++) {
			if (table[i].status != HashTable::ACTIVE) {
				break;
			}
		}
		sizes[sizeCount] = size;
		sizeCount++;
	}

	for (int i = low; i < high; i++) {
		if (table[i].status == HashTable::ACTIVE) {
			int j = i;
			int tempSize = 0;
			while (true) {
				if (table[j].status != HashTable::ACTIVE) {
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
			int* tempSizes = new int[maxSize * 2] { 0 };
			for (int i = 0; i < maxSize; i++) {
				tempSizes[i] = sizes[i];
			}
			maxSize *= 2;
			delete[] sizes;
			sizes = nullptr;
			sizes = new int[maxSize] {0};
			for (int i = 0; i < maxSize; i++) {
				sizes[i] = tempSizes[i];
			}
			delete[] tempSizes;
			tempSizes = nullptr;
		}
	}

	BubbleSort(sizes, maxSize);

	string s = "";

	for (int i = maxSize - 1; i >= 0; i--) {
		if (sizes[i] == 0) {
			break;
		}
		if (s != "") { s += "," + std::to_string(sizes[i]); }
		else { s += std::to_string(sizes[i]); }
	}

	delete[] sizes;
	sizes = nullptr;
	if (s == "") {
		return "(empty)";
	}
	return s;
}

void OpenAddressingHashTable::performRehashing() {
	if (printSteps) {
		cout << "Rehashing is needed!" << endl;  // required
	}
	activeCellCount = 0;
	Cell* newTable = new Cell[m];
	for (int i = 0; i < m; i++) {
		newTable[i] = table[i];
	}
	delete[] table;
	table = nullptr;
	int oldtm = m;
	m *= 2;
	table = new Cell[m];

	for (int i = 0; i < m; i++) {
		table[i].status = HashTable::EMPTY;
		table[i].magic = nullptr;
	}
	
	for (int i = 0; i < oldtm; i++) {
		if (newTable[i].status != HashTable::ACTIVE) { continue; }
		add(newTable[i].magic);
	}

	delete[] newTable;
	newTable = nullptr;

	if (printSteps) {
		cout << "Rehashing is done!" << endl;  // required
	}
}
