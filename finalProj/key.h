#pragma once
#include<iostream>

using namespace std;

class Key {
	int key;
public:
	static int comparisons;
	//static int assignments;
	Key(int x = 0);
	int the_key() const;

	//Key& operator = (const Key& original);
};


int Key::comparisons = 0;

Key::Key(int x)
{
	key = x;
}

int Key::the_key() const {
	return key;
}



bool operator ==(const Key& x, const Key& y);
bool operator >(const Key& x, const Key& y);
bool operator <(const Key& x, const Key& y);
bool operator >=(const Key& x, const Key& y);
bool operator <=(const Key& x, const Key& y);
bool operator !=(const Key& x, const Key& y);

ostream& operator << (ostream& os, const Key& k);

/*
Key& Key::operator=(const Key& original)
{
	//Key::assignments++;
	return *this;
}
*/

ostream& operator <<(ostream& os, const Key& k)
{
	os << k.the_key();
	return os;
}

bool operator ==(const Key& x, const Key& y)
{
	Key::comparisons++;
	return x.the_key() == y.the_key();
}

bool operator >(const Key& x, const Key& y)
{
	Key::comparisons++;
	return x.the_key() > y.the_key();
}

bool operator <(const Key& x, const Key& y)
{
	Key::comparisons++;
	return x.the_key() < y.the_key();
}

bool operator >=(const Key& x, const Key& y)
{
	Key::comparisons++;
	return x.the_key() >= y.the_key();
}

bool operator <=(const Key& x, const Key& y)
{
	Key::comparisons++;
	return x.the_key() <= y.the_key();
}

bool operator !=(const Key& x, const Key& y)
{
	Key::comparisons++;
	return x.the_key() != y.the_key();
}