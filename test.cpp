/*
#include <iostream>
#include <iomanip>
#include "Set.h"

using namespace std;

    void PrintTreeVisual(Node* root_local, const std::string &prefix_local = "", bool isLeft = true) 
    {
        if (root_local == nullptr) {
            return;
        }

        std::cout << prefix_local;
        std::wcout << (isLeft ? L"└── " : L"├── ");
        std::cout << "[" << root_local->info.key << "]: " << root_local->info.item << std::endl;

        PrintTreeVisual(root_local->right, prefix_local + (isLeft ? "|    " : "     "), false);
        PrintTreeVisual(root_local->left, prefix_local + (isLeft ? "|    " : "     "), true);
    }
    DynamicArray<Set<int>::Pair> PairsArray = set.MakePairsArray();
    
    

void PrintSetAsTree(Set<int> set)
{
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
    DynamicArray<string> lines

    
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
    int a = ' ';
    cout << a;
}

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
  
  0     1     2     3 
( 8)━━(12)━━(14)━━(15)
  ┃     ┃     ┗━━━(13)
  ┃     ┗━━━(10)━━(11)
  ┃           ┗━━━( 9)
  ┗━━━( 4)━━( 6)━━( 7)
        ┃     ┗━━━( 5)
        ┗━━━( 2)━━( 3)
              ┗━━━( 1) 

*/