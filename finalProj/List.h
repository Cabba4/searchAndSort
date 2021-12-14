#pragma once

#include "utility.h"
#include "key.h"

const int max_list = 10000;
//const int max_list = 15;

typedef Key Record;

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


class Ordered_list :public List<Record> {
public:
	Ordered_list();
	Error_code insert(const Record& data);
	Error_code insert(int position, const Record& data);
	//Error_code replace(int position, const Record& data);
};

class Sortable_list : public List<Record> {
public:
	Sortable_list();
	void insertion_sort();
};


Sortable_list::Sortable_list()
{
	count = 0;
}

void Sortable_list::insertion_sort()
/*
Post: The entries of the Sortable_list have been rearranged so that
	  the keys in all the  entries are sorted into nondecreasing order.
Uses: Methods for the class Record; the contiguous List implementation of
	  Chapter 6
*/
{
	int first_unsorted;    //  position of first unsorted entry
	int position;          //  searches sorted part of list
	Record current;        //  holds the entry temporarily removed from list
	current.comparisons = 0;
	for (first_unsorted = 1; first_unsorted < count; first_unsorted++)
		if (entry[first_unsorted] < entry[first_unsorted - 1]) {
			current.comparisons++;
			position = first_unsorted;
			current = entry[first_unsorted];         //  Pull unsorted entry out of the list.
			//current.assignments += 2;
			do {               //  Shift all entries until the proper position is found.
				entry[position] = entry[position - 1];
				//current.assignments++;
				position--;                           //  position is empty.
			} while (position > 0 && entry[position - 1] > current);
			entry[position] = current;
			current.comparisons++;
		}
	cout << "Comparisions : " << current.comparisons << endl;
	//cout << "Assignments : " << current.assignments << endl;
}

Ordered_list::Ordered_list()
{
	count = 0;
}


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


Error_code Ordered_list::insert(const Record& data)
/*
Post: If the Ordered_list is not full, the function succeeds:
	  The Record data is inserted into the list, following the
	  last entry of the list with a strictly lesser key (or in the
	  first list position if no list element has a lesser key).
	  Else: the function fails with the diagnostic Error_code overflow.
*/
{
	int s = size();
	int position;
	for (position = 0; position < s; position++) {
		Record list_data;
		retrieve(position, list_data);
		if (data >= list_data) break;
	}
	return List<Record>::insert(position, data);
}


Error_code Ordered_list::insert(int position, const Record& data)
/*
Post: If the Ordered_list is not full, 0 <= position <= n,
	  where n is the number of entries in the list,
	  and the Record data can be inserted at position in the list,
	  without disturbing the list order, then the function succeeds:
	  Any entry formerly in position and all later entries have their
	  position numbers increased by 1 and data is inserted at position
	  of the List.
	  Else: the function fails with a diagnostic Error_code.
*/
{
	Record list_data;
	if (position > 0) {
		retrieve(position - 1, list_data);
		if (data < list_data)
			return fail;
	}
	if (position < size()) {
		retrieve(position, list_data);
		if (data > list_data)
			return fail;
	}
	return List<Record>::insert(position, data);
}


template <class Record>
void output(Record& x)
{
	cout << x << "   ";
}