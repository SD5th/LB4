
#include <iostream>
#include <iomanip>
#include "Set.h"

using namespace std;

struct Square
{
    bool isUsed;
    bool isValue;
    int value;
    char symbol;
    Square():
        isUsed(false)
    { }
    Square(int value):
        isUsed(true),
        isValue(true),
        value(value)
    { }
    Square(char symbol):
        isUsed(true),
        isValue(false),
        symbol(symbol)
    { }    
};

void PrintSetAsTree(Set<int> set)
{
    if (set.IsEmpty())
        return;
    DynamicArray<Set<int>::Pair> PairsArray = set.MakePairsArray();
    int max;
    if (set.GetMin() * -1 > set.GetMax())
        max = set.GetMin() * -1;
    else
        max = set.GetMax();
    int num_width = 0;
    if (max == 0)
        num_width = 1;
    while (max > 0)
    {
        num_width++;
        max /= 10;
    }
    if (set.GetMin() < 0)        
        num_width++;                        //(333)━━  (7)    (22)━━   (6)   (1)━━  (5)
    int width = num_width + 4;  // ( ) ━ ━      ┗               ┗             ┗

    int maxLayer = 0;
    for (int i = 0; i< PairsArray.GetSize(); i++)
        if (PairsArray[i].layer > maxLayer)
            maxLayer = PairsArray[i].layer;
    
    int m = maxLayer+1;
    int n = 1;
    for (int i = 0; i < PairsArray.GetSize()-1; i++)
        if (PairsArray[i].child != PairsArray[i+1].parent)
            n++;
    
    DynamicArray<DynamicArray<Square>> board(n);
    for (int i = 0; i < n; i++)
        board[i] = DynamicArray<Square>(m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)                   //        i        j
            board[i][j] = Square();                   //board[stroka][stolbec]

    board[0][0] = Square(PairsArray[0].child);
    for (int pairNum = 1; pairNum < PairsArray.GetSize(); pairNum++)
    {
        int childLayer = PairsArray[pairNum].layer;
        int childRow = 0;
        while (board[childRow][childLayer].isUsed)
            childRow++;
        board[childRow][childLayer] = Square(PairsArray[pairNum].child);
        int parentLayer = childLayer - 1, parentRow;
        for (parentRow = 0; (!(board[parentRow][parentLayer].isValue && board[parentRow][parentLayer].value == PairsArray[pairNum].parent)); parentRow++);
        
        for (int i = parentRow + 1; i < paren)
    }



}

    /*


8 8 
8 12
12 14
14 15
14 13
12 10
10 11
10 9
8 4
4 6
6 7
6 5
4 2
2 3
2 1
  
  0     1     2     3        4 = m      = maxLayer + 1
( 8)━━|(12)━━|(14)━━|(15)
  ┃   |  ┃   |  ┗━━━|(13)
  ┃   |  ┗━━━|(10)━━|(11)
  ┃   |      |  ┗━━━|( 9)
  ┗━━━|( 4)━━|( 6)━━|( 7)
      |  ┃   |  ┗━━━|( 5)
      |  ┗━━━|( 2)━━|( 3)
      |      |  ┗━━━|( 1) 
                           8 = n
                     = 

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
*/