#include "Set.h"
#include <cassert>


void Test_Constructor_FromArray_Empty()
{
    ArraySequence<int> array;
    Set<int> set(array);
    ArraySequence<int> newArr;
    set.SetToArray(newArr);
    assert(newArr.GetSize() == 0);

    std::cout << "Test_Constructor_FromArray_Empty: OK\n";
}

void Test_Constructor_FromArray_Ordered_EvenSize()
{
    ArraySequence<int> array;
    array.Append(0);
    array.Append(1);
    array.Append(2);
    array.Append(3);
    array.Append(4);
    array.Append(5);
    Set<int> set(array);
    ArraySequence<int> newArr;
    set.SetToArray(newArr);    
    assert(newArr.GetSize() == 6);
    assert(newArr[0] == 0);
    assert(newArr[1] == 1);
    assert(newArr[2] == 2);
    assert(newArr[3] == 3);
    assert(newArr[4] == 4);
    assert(newArr[5] == 5);
    

    std::cout << "Test_Constructor_FromArray_Ordered_EvenSize: OK\n";
}

void Test_Constructor_FromArray_UnorderedRepetative_UnevenSize()
{
    ArraySequence<int> array;
    array.Append(5);
    array.Append(5);
    array.Append(2);
    array.Append(-1);
    array.Append(4);
    array.Append(3);
    Set<int> set(array);
    ArraySequence<int> newArr;
    set.SetToArray(newArr);    
    assert(newArr.GetSize() == 5);
    assert(newArr[0] == -1);
    assert(newArr[1] == 2);
    assert(newArr[2] == 3);
    assert(newArr[3] == 4);
    assert(newArr[4] == 5);
    

    std::cout << "Test_Constructor_FromArray_UnorderedRepetative_UnevenSize: OK\n";
}

void Test_Constructor_Default()
{
    Set<int> set;
    ArraySequence<int> arr;
    set.SetToArray(arr);
    assert(arr.GetSize() == 0);

    std::cout << "Test_Constructor_Default: OK\n";
}

void Test_Constructor_Copy_Empty()
{
    Set<int> set1;
    Set<int> set2(set1);
    ArraySequence<int> arr;
    set2.SetToArray(arr);
    assert(arr.GetSize() == 0);

    std::cout << "Test_Constructor_Copy_Empty: OK\n";
}

void Test_Constructor_Copy_NotEmpty()
{
    ArraySequence<int> array;
    array.Append(0);
    array.Append(1);
    array.Append(2);
    array.Append(3);
    array.Append(4);
    array.Append(5);
    Set<int> set1(array);
    Set<int> set2(set1);
    ArraySequence<int> newArr;
    set2.SetToArray(newArr);
    assert(newArr.GetSize() == 6);
    assert(newArr[0] == 0);
    assert(newArr[1] == 1);
    assert(newArr[2] == 2);
    assert(newArr[3] == 3);
    assert(newArr[4] == 4);
    assert(newArr[5] == 5);

    std::cout << "Test_Constructor_Copy_NotEmpty: OK\n";
}

void Test_GetMin_Empty()
{
    Set<int> set;
    try
    {
        int min = set.GetMin();
        assert(false); 
    }
    catch (const IndexOutOfRange &excep)
    {
        assert(std::string(excep.what()) == "Set: GetMin. Set is empty.");
    }
    std::cout << "Test_GetMin_Empty: OK\n";
}

void Test_GetMin_NotEmpty()
{
    ArraySequence<int> array;
    array.Append(0);
    array.Append(1);
    array.Append(2);
    Set<int> set(array);
    assert(set.GetMin() == 0);
    std::cout << "Test_GetMin_NotEmpty: OK\n";
}

void Test_GetMax_Empty()
{
    Set<int> set;
    try
    {
        int min = set.GetMax();
        assert(false);
    }
    catch (const IndexOutOfRange &excep)
    {
        assert(std::string(excep.what()) == "Set: GetMax. Set is empty.");
    }
    std::cout << "Test_GetMax_Empty: OK\n";
}

void Test_GetMax_NotEmpty()
{
    ArraySequence<int> array;
    array.Append(0);
    array.Append(1);
    array.Append(2);
    Set<int> set(array);
    assert(set.GetMax() == 2);
    std::cout << "Test_GetMin_NotEmpty: OK\n";
}

void Test_Insert_Empty()
{
    Set<int> set;
    set.Insert(1);
    ArraySequence<int> array;
    set.SetToArray(array);
    assert(array.GetSize() == 1);
    assert(array[0] == 1);

    std::cout << "Test_Insert_Empty: OK\n";
}

void Test_Insert_NotEmpty()
{
    ArraySequence<int> array;
    array.Append(0);
    array.Append(1);
    array.Append(2);
    Set<int> set(array);
    set.Insert(3);
    ArraySequence<int> newArr;
    set.SetToArray(newArr);
    assert(newArr.GetSize() == 4);
    assert(newArr[0] == 0);
    assert(newArr[1] == 1);
    assert(newArr[2] == 2);
    assert(newArr[3] == 3);

    std::cout << "Test_Insert_NotEmpty: OK\n";
}

void Test_Insert_Repetative()
{
    ArraySequence<int> array;
    array.Append(0);
    array.Append(1);
    array.Append(2);
    Set<int> set(array);
    set.Insert(1);
    ArraySequence<int> newArr;
    set.SetToArray(newArr);
    assert(newArr.GetSize() == 3);
    assert(newArr[0] == 0);
    assert(newArr[1] == 1);
    assert(newArr[2] == 2);

    std::cout << "Test_Insert_Repetative: OK\n";
}

void Test_Search_Empty()
{
    Set<int> set;
    assert(set.Search(1) == false);

    std::cout << "Test_Search_Empty: OK\n";
}

void Test_Search_Existing()
{
    Set<int> set;
    set.Insert(0);
    set.Insert(1);
    set.Insert(2);
    set.Insert(3);
    set.Insert(4);
    assert(set.Search(2) == true);

    std::cout << "Test_Search_Existing: OK\n";
}

void Test_Search_NotExisting()
{
    Set<int> set;
    set.Insert(0);
    set.Insert(1);
    set.Insert(2);
    set.Insert(3);
    set.Insert(4);
    assert(set.Search(100) == false);

    std::cout << "Test_Search_NotExisting: OK\n";
}

void Test_Remove_Empty()
{
    Set<int> set;
    set.Remove(5);

    std::cout << "Test_Remove_Empty: OK\n";
}

void Test_Remove_NotExisting()
{
    Set<int> set;
    set.Insert(2);
    set.Insert(1);
    set.Remove(3);

    assert(set.Search(1) == true);
    assert(set.Search(2) == true);

    std::cout << "Test_Remove_NotExisting: OK\n";
}

void Test_Remove_Existing_0L0R()
{
    Set<int> set;
    set.Insert(2);
    set.Insert(1);
    set.Remove(1);

    assert(set.Search(1) == false);
    assert(set.Search(2) == true);

    std::cout << "Test_Remove_Existing_0L0R: OK\n";
}

void Test_Remove_Existing_1L0R()
{
    Set<int> set;
    set.Insert(10);
    set.Insert(20);
    set.Insert(5);
    set.Insert(4);
    set.Remove(5);

    assert(set.Search(5) == false);
    assert(set.Search(20) == true);
    assert(set.Search(10) == true);
    assert(set.Search(4) == true);

    std::cout << "Test_Remove_Existing_1L0R: OK\n";
}

void Test_Remove_Existing_1L1R()
{
    Set<int> set;
    ArraySequence<int> arr;
    
    set.Insert(10);
    set.Insert(20);
    set.Insert(5);
    set.Insert(4);
    set.Insert(6);
    set.Remove(5);
    

    assert(set.Search(5) == false);
    assert(set.Search(20) == true);
    assert(set.Search(4) == true);
    assert(set.Search(10) == true);
    assert(set.Search(6) == true);

    std::cout << "Test_Remove_Existing_1L1R: OK\n";
}

int Test_Map_MultByTwo(int number)
{
    return number * 2;
}

void Test_Map()
{
    int (*function)(int) = Test_Map_MultByTwo;
    Set<int> set;
    set.Insert(1);
    set.Insert(10);
    set.Insert(100);
    set.Insert(1000);
    set.Insert(10000);

    Set<int> mappedSet = set.Map(function);
    
    assert(mappedSet.Search(2) == true);
    assert(mappedSet.Search(20) == true);
    assert(mappedSet.Search(200) == true);
    assert(mappedSet.Search(2000) == true);
    assert(mappedSet.Search(20000) == true);
    
    assert(mappedSet.Search(1) == false);
    assert(mappedSet.Search(10) == false);
    assert(mappedSet.Search(100) == false);
    assert(mappedSet.Search(1000) == false);
    assert(mappedSet.Search(10000) == false);

    std::cout << "Test_Map: OK\n";    
}

int Test_Reduce_SummOfTwo(int x, int y)
{
    return x+y;
}

void Test_Reduce_Empty()
{
    int (*function)(int, int) = Test_Reduce_SummOfTwo;
    Set<int> set;

    try
    {
        int reduced = set.Reduce(function, 0);
        assert(false); 
    }
    catch (const IndexOutOfRange &excep)
    {
        assert(std::string(excep.what()) == "Set: Reduce. Set is empty.");
    }
    std::cout << "Test_Reduce_Empty: OK\n";    
}

void Test_Reduce_NotEmpty()
{
    int (*function)(int, int) = Test_Reduce_SummOfTwo;
    Set<int> set;
    set.Insert(1);
    set.Insert(10);
    set.Insert(100);
    set.Insert(1000);
    set.Insert(10000);    
    
    assert(set.Reduce(function, 0) == 11111);
    std::cout << "Test_Reduce_NotEmpty: OK\n";    
}

bool Test_Where_ModByTwo(int number)
{
    return (number % 2 == 0);
}

void Test_Where()
{
    bool (*function)(int) = Test_Where_ModByTwo;
    Set<int> set;
    set.Insert(2);
    set.Insert(4);
    set.Insert(5);
    set.Insert(7);
    set.Insert(10);

    Set<int> wheredSet = set.Where(function);
    
    assert(wheredSet.Search(2) == true);
    assert(wheredSet.Search(4) == true);
    assert(wheredSet.Search(10) == true);
    
    assert(wheredSet.Search(5) == false);
    assert(wheredSet.Search(7) == false);

    std::cout << "Test_Where: OK\n";    
}

void Test_Union()
{
    Set<int> set1;
    set1.Insert(1);
    set1.Insert(3);
    set1.Insert(5);
    set1.Insert(7);
    Set<int> set2;
    set2.Insert(2);
    set2.Insert(4);
    set2.Insert(5);
    set2.Insert(7);

    Set<int> unionedSet = set1.Union(set2);
    
    assert(unionedSet.Search(1) == true);
    assert(unionedSet.Search(2) == true);
    assert(unionedSet.Search(3) == true);
    assert(unionedSet.Search(4) == true);
    assert(unionedSet.Search(5) == true);
    assert(unionedSet.Search(7) == true);

    std::cout << "Test_Union: OK\n";    
}
void Test_Intersection()
{
    Set<int> set1;
    set1.Insert(1);
    set1.Insert(3);
    set1.Insert(5);
    set1.Insert(7);
    Set<int> set2;
    set2.Insert(2);
    set2.Insert(4);
    set2.Insert(5);
    set2.Insert(7);

    Set<int> intersectedSet = set1.Intersection(set2);
    
    assert(intersectedSet.Search(1) == false);
    assert(intersectedSet.Search(2) == false);
    assert(intersectedSet.Search(3) == false);
    assert(intersectedSet.Search(4) == false);
    assert(intersectedSet.Search(5) == true);
    assert(intersectedSet.Search(7) == true);

    std::cout << "Test_Intersection: OK\n";    
}

void Test_Substraction()
{
    Set<int> set1;
    set1.Insert(1);
    set1.Insert(3);
    set1.Insert(5);
    set1.Insert(7);
    Set<int> set2;
    set2.Insert(2);
    set2.Insert(4);
    set2.Insert(5);
    set2.Insert(7);

    Set<int> substractedSet = set1.Substraction(set2);
    
    assert(substractedSet.Search(1) == true);
    assert(substractedSet.Search(2) == false);
    assert(substractedSet.Search(3) == true);
    assert(substractedSet.Search(4) == false);
    assert(substractedSet.Search(5) == false);
    assert(substractedSet.Search(7) == false);

    std::cout << "Test_Substraction: OK\n";    
}


void StartAllTests()
{
    Test_Constructor_FromArray_Empty();
    Test_Constructor_FromArray_Ordered_EvenSize();
    Test_Constructor_FromArray_UnorderedRepetative_UnevenSize();
    Test_Constructor_Default();
    Test_Constructor_Copy_Empty();
    Test_Constructor_Copy_NotEmpty();
    Test_GetMin_Empty();
    Test_GetMin_NotEmpty();
    Test_GetMax_Empty();
    Test_GetMax_NotEmpty();
    Test_Insert_Empty();
    Test_Insert_NotEmpty();
    Test_Insert_Repetative();
    Test_Search_Empty();
    Test_Search_Existing();
    Test_Search_NotExisting();
    Test_Remove_Empty();
    Test_Remove_NotExisting();
    Test_Remove_Existing_0L0R();
    Test_Remove_Existing_1L0R();
    Test_Remove_Existing_1L1R();
    Test_Map();
    Test_Reduce_Empty();
    Test_Reduce_NotEmpty();
    Test_Where();
    Test_Union();
    Test_Intersection();
    Test_Substraction();
}

int main()
{
    StartAllTests();
}