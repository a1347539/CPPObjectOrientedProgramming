#include "shop.h"
#include <iostream>
#include <cctype> //hint: you may use the isupper function in it
using std::cout;
using std::endl;


Shop::Shop(HashTable* fireTable, HashTable* iceTable, HashTable* lightningTable) : profit(0), fireTable(fireTable), iceTable(iceTable), lightningTable(lightningTable) {
}

Shop::~Shop() {
	delete fireTable;
	delete iceTable;
	delete lightningTable;
}

HashTable* Shop::getTable(string prefix) const {
	if (prefix == "Fire") {
		return fireTable;
	}
	else if (prefix == "Ice") {
		return iceTable;
	}
	else if (prefix == "Lightning") {
		return lightningTable;
	}
	else {
		return nullptr;
	}
}

bool Shop::stockUp(string name, int quantity, int price) const {
	string prefix;
	string suffix;
	int prefixLength = 0;
	if (name[0] == 'F') { prefixLength = 4; }
	else if (name[0] == 'I') { prefixLength = 3; }
	else { prefixLength = 9; }
	prefix = name.substr(0, prefixLength);
	suffix = name.substr(prefixLength, name.length() - prefixLength);

	HashTable* h = getTable(prefix);
	Magic* m = h->get(suffix);
	if (m) {
		// If the inventory already has this magic (magic with the same suffix in the corresponding table),
		// then simply increase the current quantity of this magic in the table, by the specified quantity.
		// If the provided price is different from the current price, just update the price to this new price.
		m->quantity += quantity;
		m->price = price;
	}
	else {
		// If the inventory doesn't already have this magic, 
		// then we need to add it to the corresponding hash table (e.g. fire magic must go to the fire table) 
		// using only the suffix as the key (e.g. use "Ball" as the key for "FireBall")
		Magic* m = new Magic{ prefix, suffix, price, quantity };
		int result = h->add(m);
		if (result == 0) { delete m; m = nullptr; }
		return result;
	}

	return true;
}

bool Shop::sell(string name, int quantity) {
	string prefix;
	string suffix;
	int prefixLength = 0;
	if (name[0] == 'F') { prefixLength = 4; }
	else if (name[0] == 'I') { prefixLength = 3; }
	else { prefixLength = 9; }
	prefix = name.substr(0, prefixLength);
	suffix = name.substr(prefixLength, name.length() - prefixLength);

	HashTable* h = getTable(prefix);
	Magic* m = h->get(suffix);

	if (m == nullptr) { return false; }

	if (m->quantity < quantity) { return false; }

	// m exists and m->quantity is larger or equal to quantity

	m->quantity -= quantity;

	profit += (quantity * m->price);

	if (m->quantity == 0) {
		return h->remove(suffix);
	}

	return true;
}
