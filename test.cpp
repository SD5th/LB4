#include <iostream>
#include <iomanip>
#include "Set.h"

using namespace std;

void PrintSetAsTree(Set<int> set)
{
    DynamicArray<Set<int>::Pair> PairsArray = set.MakePairsArray();
    int max;
    if (set.GetMin() * -1 > set.GetMax())
        max = set.GetMin() * -1;
    else
        max = set.GetMax();
    int w = 0;
    if (max == 0)
        w = 1;
    while (max > 0)
    {
        w++;
        max /= 10;
    }
    if (set.GetMin() < 0)
        w++;
    cout.fill(' ');
    cout << '(' << setw(w) << PairsArray[0].child << ')' << endl;
    for (int i = 1; i < PairsArray.GetSize(); i++)
    {
        int child = PairsArray[i].child;
        int parent = PairsArray[i].parent;
        int layer = PairsArray[i].layer;
        bool isOneChild = true;
        for (int j = i + 1; j < PairsArray.GetSize(); j++)
            if (PairsArray[j].child == child)
            {
                isOneChild = false;
                break;
            }
        for (int j = 0; j < layer-1; j++)
            cout << setw(w) << ' ';
        cout << setw(w/2) << ' ';
        cout.fill('━');
        if (isOneChild)
            cout << '┗' << setw(w - w/2 - 1) << '━';
        else
            cout << '┣' << setw(w - w/2 - 1) << '━';


    }
}

int main()
{

}
/*
┣ ┗ ━ ┃
(10)
  ┣━(20)
  ┃   ┣━(30)
  ┃   ┃   ┗━(40)
  ┃   ┗━(15)
  ┗━( 5)
      ┣━( 7)
      ┃   ┗━( 8)
      ┗━( 3)
          ┣━( 4)
          ┗━( 2)



(10)━━(20)━━(30)━━(40)
  ┃     ┗━━━(15)
  ┗━━━( 5)━━( 7)━━( 8)
        ┗━━━( 3)━━( 4)
              ┗━━━( 2)

*/