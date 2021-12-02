#include"key.h"

int Key::comparisons = 0;

Key::Key(int x)
{
	key = x;
}

int Key::the_key() const {
	return key;
}


