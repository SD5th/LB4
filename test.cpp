#include <iostream>
#include "Set.h"

int main()
{
    ArraySequence<int> arr;
    arr.Append(5);
    arr.Append(4);
    arr.Append(3);
    arr.Append(2);
    arr.Append(1);
    arr.Append(0);
    SortArray(arr, 0, arr.GetSize()-1); 
    for (int i = 0; i < 6; i++)
        cout << arr[i] << ' ';
}