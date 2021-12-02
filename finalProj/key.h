#pragma once
#include<iostream>
#include"utility.h"

using namespace std;

class Key {
	int key;
public:
	static int comparisons;
	Key(int x = 0);
	int the_key() const;
};

typedef Key Record;

const int max_list = 10;

template <class Record>
class List {
public:
	//  methods of the List ADT
	List();
	int size() const;
	bool full() const;
	bool empty() const;
	void clear();
	void traverse(void (*visit)(Record&));
	Error_code retrieve(int position, Record& x) const;
	Error_code replace(int position, const Record& x);
	Error_code remove(int position, Record& x);
	Error_code insert(int position, const Record& x);

protected:
	//  data members for a contiguous list implementation
	int count;
	Record entry[max_list];
};


template <class Record>
List<Record>::List()
{
	count = 0;
}


template <class Record>
int List<Record>::size() const
{
	return count;
}

template <class Record>
bool List<Record>::empty() const
/*
Post: The function returns true if list is empty
*/
{
	if (count == 0)
		return true;
	else
		return false;
}


template <class Record>
bool List<Record>::full() const
/*
Post: The function returns true if list is full
*/
{
	if (count == max_list)
		return true;
	else
		return false;
}


template <class Record>
void List<Record>::clear()
/*
Post: The function clears the list
*/
{
	if (count == 0)
		cout << "Empty List" << endl;
	else
		for (int i = 0; i < count; i++)
		{
			entry[i] = 0;
		}
	count = 0;
}

template <class Record>
void List<Record>::traverse(void (*visit)(Record&))
/*
Post: The action specified by function (*visit) has been performed on every
	  entry of the List, beginning at position 0 and doing each in turn.
*/
{
	for (int i = 0; i < count; i++)
		(*visit)(entry[i]);
}

template <class Record>
Error_code List<Record>::retrieve(int position, Record& x) const
/*
 Post: If 0 <= position < n, where n is the number of entries
in the List, the function succeeds: The entry at position
is copied to x; all List entries remain unchanged.
Else: The function fails with a diagnostic error code
*/
{
	if (full())
		return overflow;
	if (position < 0 || position > count)
		return rangerror;
	x = entry[position];
	return success;

}

template <class Record>
Error_code List<Record>::replace(int position, const Record& x)
/*
* Post: If 0 <= position < n, where n is the number of entries
in the List, the function succeeds: The entry at position
is replaced by x; all other entries remain unchanged.
Else: The function fails with a diagnostic error code.
*/
{
	if (full())
		return overflow;
	if (position < 0 || position > count)
		return rangerror;
	entry[position] = x;
	return success;
}

template <class Record>
Error_code List<Record>::remove(int position, Record& x)
/*
* Post: If 0 <= position < n, where n is the number of entries in
the List, the function succeeds: The entry at position is
removed from the List, and all later entries have their
position numbers decreased by 1. The parameter x
records a copy of the entry formerly at position.
Else: The function fails with a diagnostic error code
*/

{
	if (full())
		return overflow;
	if (position < 0 || position > count)
		return rangerror;
	for (int i = position; i < count; i++)
	{
		entry[i] = entry[i + 1];
	}
	count--;
	return success;
}

template <class Record>
Error_code List<Record>::insert(int position, const Record& x)
/*
Post: If the List is not full and 0 <= position <= n,
	  where n is the number of entries in the List, the function succeeds:
	  Any entry formerly at position and all later entries have their position
	  numbers increased by 1, and x is inserted at position of the List.
	  Else: The function fails with a diagnostic error code.
*/
{
	if (full())
		return overflow;

	if (position < 0 || position > count)
		return rangerror;

	for (int i = count - 1; i >= position; i--)
		entry[i + 1] = entry[i];

	entry[position] = x;
	count++;
	return success;
}