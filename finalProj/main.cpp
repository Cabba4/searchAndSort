// searchandsort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "list.h"
#include "utility.h"
#include "TIMER.h"
#include <random>


using namespace std;

Timer T;
double time1;
int list_size;
int position;
int comparision;

List<Record> the_list;
Ordered_list list2;
Sortable_list slist;

Error_code sequential_search(const List<Record>& the_list,
	const Key& target, int& position)
	/*
	Post: If an entry in the_list has key equal to target, then return
		  success and the output parameter position locates such an entry
		  within the list.
		  Otherwise return not_present and position becomes invalid.
	*/
{
	int s = the_list.size();
	T.reset();
	target.comparisons = 0;
	for (position = 0; position < s; position++) {
		Record data;
		the_list.retrieve(position, data);
		if (data == target)
		{
			comparision = target.comparisons;
			time1 = T.elapsed_time();
			return success;
		}
	}
	time1 = T.elapsed_time();
	comparision = target.comparisons;
	return not_present;
}

Error_code binary_search_1(const Ordered_list& the_list,
	const Key& target, int& position)
	/*
	Post: If a Record in the_list  has Key equal to target, then position locates
		  one such entry and a code of success is returned.
		  Otherwise, not_present is returned and position is undefined.
	Uses: Methods for classes List and Record.
	*/
{
	Record data;
	//cout << "BURH" << endl;
	//list2.traverse(output);
	int bottom = 0, top = the_list.size() - 1;
	T.reset();
	target.comparisons = 0;

	while (bottom < top) {
		int mid = (bottom + top) / 2;
		the_list.retrieve(mid, data);
		if (data < target)
			bottom = mid + 1;
		else
			top = mid;
	}
	if (top < bottom)
	{
		comparision = target.comparisons;
		time1 = T.elapsed_time();
		return not_present;
	}
	
	else {
		position = bottom;
		the_list.retrieve(bottom, data);
		if (data == target)
		{
			comparision = target.comparisons;
			//cout << "hmmmm" << endl;
			time1 = T.elapsed_time();
			return success;
		}
		else 
		{
			comparision = target.comparisons;
			time1 = T.elapsed_time();
			return not_present; 
		}
	}
}

void initialise(int size)
{
	
	for (int i = 0; i < size; i++)
	{
		the_list.insert(i, i * 2 + 1);
	}
	//the_list.traverse(output);
}

void initialise_order_list(int size)
{

	for (int i = 0; i < size; i++)
	{
		list2.insert(i, i * 2 + 1);
	}
	//the_list.traverse(output);
}

void initialise_sort(int size)
{
	
	for (int i = 0; i < size; i++)
	{
		int random = 1 + (rand() % (size * 10));
		slist.insert(i, random);
	}

	slist.traverse(output);
	cout << endl;
}

void search_1()
{
	system("clear");
	cout << "Enter data size for the list " << endl;
	cin >> list_size;
	initialise(list_size);
	list_size--;
	int num;
	cout << "How many times must search run?" << endl;
	cin >> num;
	cout << "Now program will randomly generate numbers to be searched for!" << endl;
	for (int i = 0; i < num; i++)
	{
		int random = 1 + (rand() % (list_size * 2 + 1));
		cout << "Number generated is = " << random << endl;
		cout << "sequential_search:" << endl;
		cout << "------------------" << endl;
		if (sequential_search(the_list, random, position) == success)
		{
			cout << "Status: Successful" << endl;
			cout << "Elapsed Time: " << T.elapsed_time() << endl;
			cout << "Comparisions per search: " << comparision << endl;
			cout << "------------------" << endl;
			cout << "------------------" << endl;
		}
		else
		{
			cout << "Status: Unsuccessful" << endl;
			cout << "Elapsed Time: " << T.elapsed_time() << endl;
			cout << "Comparisions per search: " << comparision << endl;
			cout << "------------------" << endl;
			cout << "------------------" << endl;
		}
	}
	
}


void search_2()
{
	system("clear");
	cout << "Enter data size for the list " << endl;
	cin >> list_size;
	initialise_order_list(list_size);
	list_size--;
	int num;
	cout << "How many times must search run?" << endl;
	cin >> num;
	cout << "Now program will randomly generate numbers to be searched for!" << endl;
	for (int i = 0; i < num; i++)
	{
		int random = 1 + (rand() % (list_size * 2 + 1));
		cout << "Number generated is = " << random << endl;
		cout << "binary_search:" << endl;
		cout << "------------------" << endl;
		if (binary_search_1(list2, random, position) == success)
		{
			cout << "Status: Successful" << endl;
			cout << "Elapsed Time: " << T.elapsed_time() << endl;
			cout << "Comparisions per search: " << comparision << endl;
			cout << "------------------" << endl;
			cout << "------------------" << endl;
		}
		else
		{
			cout << "Status: Unsuccessful" << endl;
			cout << "Elapsed Time: " << T.elapsed_time() << endl;
			cout << "Comparisions per search: " << comparision << endl;
			cout << "------------------" << endl;
			cout << "------------------" << endl;
		}
	}
}


void sort_1()
{
	system("clear");
	cout << "Enter data size for the list " << endl;
	cin >> list_size;
	initialise_sort(list_size);
	list_size--;
	cout << "Now program will sort randomly generated data set!" << endl;
	T.reset();
	cout << "insertion_sort:" << endl;
	cout << "------------------" << endl;
	slist.insertion_sort();
	time1 = T.elapsed_time();
	{
		cout << "Status: Successful" << endl;
		cout << "Elapsed Time: " << T.elapsed_time() << endl;
		//slist.traverse(output);

		cout << "------------------" << endl;
		cout << "------------------" << endl;
	}
}

void startup()
{
	char ans;
	do
	{
		system("clear");
		cout << "Welcome to this Search and Sort Program " << endl;
		cout << "Sequential Search..........................1" << endl;
		cout << "Binary Search..............................2" << endl;
		cout << "Insertion Sort..................................3" << endl;
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1: search_1();
			break;

		case 2: search_2();
			break;

		case 3: sort_1();
			break;

		default: cout << "Wrong value" << endl;
		}

		cout << "Run again?" << endl;
		cin >> ans;
	} while (ans == 'Y' || ans == 'y');
	
}



int main()
{
	startup();
	
}


