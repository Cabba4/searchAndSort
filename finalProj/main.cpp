// searchandsort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "key.h"
#include "utility.h"


using namespace std;

bool operator ==(const Key& x, const Key& y);
bool operator >(const Key& x, const Key& y);
bool operator <(const Key& x, const Key& y);
bool operator >=(const Key& x, const Key& y);
bool operator <=(const Key& x, const Key& y);
bool operator !=(const Key& x, const Key& y);

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
    for (position = 0; position < s; position++) {
        Record data;
        the_list.retrieve(position, data);
        if (data == target) return success;
    }
    return not_present;
}



int main()
{
    Record R,temp;
    R = 10;
    List<Record> L;
    L.insert(0, R);
    L.insert(1, 11);
    L.retrieve(0, temp);
    cout << temp.the_key() << endl;
}


