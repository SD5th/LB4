#include <iostream>
#include "C:\Main\Kodiki\C++\Labs\2Sem\LB2-2\Sequence.h"
using namespace std;

template <typename T>
void mergeForSortArray(ArraySequence<T> & array, int left, int mid, int right) {
        
            int size1 = mid - left + 1;
            int size2 = right - mid;

            ArraySequence<T> subarrayLeft(size1), subarrayRight(size2);

            for (int i = 0; i < size1; i++)
                subarrayLeft[i] = array[left + i];
            for (int i = 0; i < size2; i++)
                subarrayRight[i] = array[mid + 1 + i];

            int i = 0, j = 0, k = left;
            while (i < size1 && j < size2) {
                if (subarrayLeft[i] <= subarrayRight[j]) {
                    array[k] = subarrayLeft[i];
                    i++;
                } 
                else {
                    array[k] = subarrayRight[j];
                    j++;
                }
                k++;
            }

            while (i < size1) {
                array[k] = subarrayLeft[i];
                i++;
                k++;
            }

            while (j < size2) {
                array[k] = subarrayRight[j];
                j++;
                k++;
            }
        }

template <typename T>
void SortArray(ArraySequence<T> & array, int left, int right) 
        {
            if (left < right) {
                int mid = left + (right - left) / 2;
                SortArray(array, left, mid);
                SortArray(array, mid + 1, right);
                mergeForSortArray(array, left, mid, right);
            }
        }

template <typename T>
void DeleteRepetitions(ArraySequence<T>& array)
{
    ArraySequence<T> arrayResult;
    if (array.GetSize() != 0)
    {
        arrayResult.Append(array[0]);
        for (int i = 1; i < array.GetSize(); i++)
            if(array[i] != array[i-1])
                arrayResult.Append(array[i]);
        array.Resize(0);
        array = *(new ArraySequence<T>(arrayResult));
    }
}

template <typename T>
struct Pair;


template <typename T>
class Set
{
    private:
    // Class Node
        class Node
        {
            public:
                T value;
                Node* left;
                Node* right;
                int height;

            // Node constructors-destructors
                Node(const T& value, Node* left, Node* right):
                    value(value),
                    left(left),
                    right(right),
                    height(0)
                { }
                
                Node(const T& value):
                    value(value),
                    left(nullptr),
                    right(nullptr),
                    height(0)
                { }

                Node():
                    left(nullptr),
                    right(nullptr),
                    height(0)
                { }

                ~Node() = default;

            // Insert-Search-Remove pack of functions
                int GetHeightDifference()
                {
                    return (right == nullptr ? -1 : right->height) - (left == nullptr ? -1 : left->height);
                }

                void SwapValues(Node* toSwapFor)
                {
                    T buffer = value;
                    value = toSwapFor->value;
                    toSwapFor->value = buffer;
                }

                void UpdateHeight()
                {
                    height = max((left == nullptr ? 0 : left->height + 1), (right == nullptr ? 0 : right->height + 1));
                }
                
                void LeftRotate()
                {
                    SwapValues(right);
                    Node* buffer = left;
                    left = right;
                    right = right->right;
                    left->right = left->left;
                    left->left = buffer;
                    left->UpdateHeight();
                    UpdateHeight();   
                }
                
                void RightRotate()
                {
                    SwapValues(left);
                    Node* buffer = right;
                    right = left;
                    left = left->left;
                    right->left = right->right;
                    right->right = buffer;
                    right->UpdateHeight();
                    UpdateHeight();
                }
                
                void Balance()
                {
                    int heightDiff = GetHeightDifference();
                    if (heightDiff == -2)
                    {
                        if (left->GetHeightDifference() == 1)
                            left->LeftRotate();
                        RightRotate();
                    }
                    else if (heightDiff == 2)
                    {
                        if (right->GetHeightDifference() == -1)
                            right->LeftRotate();
                        LeftRotate();
                    }
                }

            // Functions to realize Set functions
                void CopyConstructor_ForSet(const Node* toCopy)
                {
                    if (toCopy->left != nullptr)
                    {
                        left = new Node(toCopy->left->value);
                        left->CopyConstructor_ForSet(toCopy->left);
                    }
                    if (toCopy->right != nullptr)
                    {
                        right = new Node(toCopy->right->value);
                        right->CopyConstructor_ForSet(toCopy->right);
                    }
                    UpdateHeight();
                }

                void FromArrayConstructor_ForSet(const ArraySequence<T> & array, int l, int r)
                {
                    int m = (l + r)/2;
                    value = array[m];
                    if (l < m)
                    {
                        left = new Node;
                        left->FromArrayConstructor_ForSet(array, l, m-1);
                    }
                    if (m < r)
                    {
                        right = new Node;
                        right->FromArrayConstructor_ForSet(array, m+1, r);
                    }
                    UpdateHeight();
                }

                void Destructor_ForSet()
                {
                    
                    if (left != nullptr)
                        left->Destructor_ForSet();
                    if (right != nullptr)
                        right->Destructor_ForSet();
                    delete this;    
                }
                
                T GetMin_ForSet()
                {
                    if (left == nullptr)
                        return value;
                    return left->GetMin_ForSet();
                }
                
                T GetMax_ForSet()
                {
                    if (right == nullptr)
                        return value;
                    return right->GetMax_ForSet();
                }
                
                void GetSize_ForSet(int & size)
                {
                    size++;
                    if (left != nullptr)
                        left->GetSize_ForSet(size);
                    if (right != nullptr)
                        right->GetSize_ForSet(size);
                }

                void Insert_ForSet(const T& toInsert)
                {
                    if (toInsert == value)
                        return;
                    if (toInsert < value)
                    {
                        if (left == nullptr)
                            left = new Node(toInsert);
                        else
                            left->Insert_ForSet(toInsert);
                    }
                    else if (value < toInsert)
                    {
                        if (right == nullptr)
                            right = new Node(toInsert);
                        else
                            right->Insert_ForSet(toInsert);
                    }
                    UpdateHeight();
                    Balance();
                }

                bool Search_ForSet(const T& toSearch)
                {
                    if (toSearch == value)
                        return true;
                    else if (toSearch < value)
                    {
                        if (left == nullptr)
                            return false;
                        else
                            return left->Search_ForSet(toSearch);
                    }
                    else if (value < toSearch)
                    {
                        if (right == nullptr)
                            return false;
                        else
                            return right->Search_ForSet(toSearch);
                    }
                    return false;
                }

                Node* Remove_ForSet(const T& toRemove)
                {
                    if (toRemove == value)
                    {
                        if (left == nullptr && right == nullptr)
                        {
                            delete this;
                            return nullptr;
                        }
                        else if (left != nullptr && right != nullptr)
                        {
                            T newValue = right->GetMin_ForSet();
                            right = right->Remove_ForSet(newValue);
                            value = newValue;
                            return this;
                        }
                        else if (left != nullptr)
                        {
                            Node* toReturn = left;
                            delete this;
                            return toReturn;
                        }
                        else if (right != nullptr)
                        {
                            Node* toReturn = right;
                            delete this;
                            return toReturn;
                        }
                    }

                    else if (toRemove < value)
                    {
                        if (left == nullptr)
                            return this;
                        else
                        {
                            left = left->Remove_ForSet(toRemove);
                            Balance();
                            UpdateHeight();
                            return this;
                        }
                    }
                    else if (value < toRemove)
                    {
                        if (right == nullptr)
                            return this;
                        else
                        {
                            right = right->Remove_ForSet(toRemove);
                            Balance();
                            UpdateHeight();
                            return this;
                        }
                    }         
                    return this;       
                }
       
                void SetToArray_ForSet(ArraySequence<T> & result)
                {
                    if (left != nullptr)
                        left->SetToArray_ForSet(result);
                    result.Append(value);
                    if (right != nullptr)
                        right->SetToArray_ForSet(result);
                }
        
                T Reduce_ForSet(T & outputValue, T (*function)(T, T))
                {
                    outputValue = function(outputValue, value);
                    if (left != nullptr)
                        outputValue = left->Reduce_ForSet(outputValue, function);
                    if (left != nullptr)
                        outputValue = right->Reduce_ForSet(outputValue, function);
                    return outputValue;
                }
        
                void MakePairsArray_ForSet(ArraySequence<Pair<T>> & PairsArray, const int & layer)
                {
                    if (right != nullptr)
                    {
                        PairsArray.Append(Pair(value, right->value, layer));
                        right.MakePairsArray_ForSet(PairsArray, layer+1);
                    }
                    
                    if (left != nullptr)
                    {
                        PairsArray.Append(Pair(value, left->value, layer));
                        left.MakePairsArray_ForSet(PairsArray, layer+1);
                    }
                }
        };
    
    // Data fields
        Node* root;

    public:
    // Constructors
        Set():
            root(nullptr)
        { }

        Set(const Set & toCopy):
            root(nullptr)
        {
            if (toCopy.root != nullptr)
            {
                root = new Node(toCopy.root->value);
                root->CopyConstructor_ForSet(toCopy.root);
            }
        }

        Set(const ArraySequence<T> & array):
            root(nullptr) 
        {
            if (array.GetSize() != 0)
            {
                ArraySequence<T> arrayReady(array);
                SortArray(arrayReady, 0, arrayReady.GetSize()-1);
                DeleteRepetitions(arrayReady);
                root = new Node;
                root->FromArrayConstructor_ForSet(arrayReady, 0, arrayReady.GetSize()-1);
            }
        }

        ~Set()
        {
            if (root != nullptr)
                root->Destructor_ForSet();
        }

    // User functions
        T GetMin()
        {
            if (root != nullptr)
                return root->GetMin_ForSet();
            else 
                throw IndexOutOfRange("Set: GetMin. Set is empty.");
        }

        T GetMax()
        {
            if (root != nullptr)
                return root->GetMax_ForSet();
            else 
                throw IndexOutOfRange("Set: GetMax. Set is empty.");
        }

        int GetSize()
        {
            if (root == nullptr)
                return 0;
            int size = 0;
            root.GetSize_ForSet(size);
            return size;
        }

        void Insert(const T& toInsert)
        {

            if (root == nullptr)
                root = new Node(toInsert);
            else
                root->Insert_ForSet(toInsert);
        }

        bool Search(const T& toSearch)
        {
            if (root == nullptr)
                return false;
            else
                return root->Search_ForSet(toSearch);
        }

        void Remove(const T& toRemove)
        {
            if (root != nullptr)
            {
                root = root->Remove_ForSet(toRemove);
                root->Balance();
                root->UpdateHeight();
            }
        }

        void SetToArray(ArraySequence<T> & result) const  // Using LNR traversal
        {
            result.Resize(0);
            if (root != nullptr)
                root->SetToArray_ForSet(result);
        }
    
    // Map, Reduce, Where
        Set<T> Map(T (*function)(T))
        {
            ArraySequence<T> array; 
            SetToArray(array);
            for (int i = 0; i < array.GetSize(); i++)
                array[i] = function(array[i]);
            return *(new Set<T>(array));
        }
        
        T Reduce (T (*function)(T, T), const T & constant)
        {
            T result = constant;
            if (root != nullptr)
                return root->Reduce_ForSet(result, function);
            else
                throw IndexOutOfRange("Set: Reduce. Set is empty.");
        }
        
        Set<T> Where(bool (*function)(T))
        {
            ArraySequence<T> unpreparedArray;
            SetToArray(unpreparedArray);
            ArraySequence<T> array;
            for (int i = 0; i < unpreparedArray.GetSize(); i++)
                if (function(unpreparedArray[i]))
                    array.Append(unpreparedArray[i]);
            return *(new Set<T>(array));
        }

    // Operations with Sets
        Set<T> Union(const Set<T> & set)
        {
            ArraySequence<T> array; 
            SetToArray(array);
            ArraySequence<T> array2;
            set.SetToArray(array2);
            
            for (int i = 0; i < array2.GetSize(); i++)
                array.Append(array2[i]);
            return *(new Set<T>(array));
        }

        Set<T> Intersection(const Set<T> set)
        {
            ArraySequence<T> array1;
            SetToArray(array1);
            ArraySequence<T> array2;
            set.SetToArray(array2);
            ArraySequence<T> array;
            int i = 0, j = 0;
            while (i < array1.GetSize() && j < array2.GetSize())
            {
                if (array1[i] == array2[j])
                {
                    array.Append(array1[i]);
                    i++;
                    j++;
                }
                else if (array1[i] < array2[j])
                    i++;
                else if (array2[j] < array1[i])
                    j++;
            }
            return *(new Set<T>(array));
        }

        Set<T> Substraction(const Set<T> set)
        {
            ArraySequence<T> array1;
            SetToArray(array1);
            ArraySequence<T> array2;
            set.SetToArray(array2);
            ArraySequence<T> array;
            int i = 0, j = 0;
            while (i < array1.GetSize() && j < array2.GetSize())
            {
                if (array1[i] == array2[j])
                {
                    i++;
                    j++;
                }
                else if (array1[i] < array2[j])
                {
                    array.Append(array1[i]);
                    i++;
                }
                else if (array2[j] < array1[i])
                    j++;
            }
            while (i < array1.GetSize())
            {
                array.Append(array1[i]);
                i++;
            }
            return *(new Set<T>(array));
        }
        
        struct Pair
        {
            T parent;
            T child;
            int layer;
            Pair(T parent, T child, int layer):
                parent(parent),
                child(child),
                layer(layer)
            { }
        };

        DynamicArray<Pair> MakePairsArray()
        {
            DynamicArray<Pair> PairsArray = *(new DynamicArray<Pair>);
            if (root != nullptr)
            {
                PairsArray.Append(Pair(root->value, root. value, 0));
                root.MakePairsArray_ForSet(PairsArray, 1);
            }
            return PairsArray;
        }
        
        
        
        bool operator == (const Set<T> & setToCompare)
        {
            ArraySequence<T> arr1, arr2;
            SetToArray(arr1);
            setToCompare.SetToArray(arr2);
            if (arr1.GetSize() != arr2.GetSize())
                return false;
            for (int i = 0; i < arr1.GetSize(); i++)
                if (arr1[i] != arr2[i])
                    return false;
            return true;            
        }

        bool operator < (const Set<T> & setToCompare)
        {
            ArraySequence<T> arr1, arr2;
            SetToArray(arr1);
            setToCompare.SetToArray(arr2);
            if (arr1.GetSize() >= arr2.GetSize())
                return false;
            int i = 0, j = 0;
            while (i < arr1.GetSize())
            {
                if (arr1[i] == arr2[j])
                {
                    i++;
                    j++;
                }
                else if (arr1[i] > arr2[j])
                    j++;
                else if (arr1[i] < arr2[j])
                    return false;
            }
            return true;            
        } 
        bool operator <= (const Set<T> & setToCompare)
        {
            if ((*(this) < setToCompare) || (*(this) == setToCompare))
                return true;
            return false;       
        } 

        bool operator > (const Set<T> & setToCompare)
        {
            ArraySequence<T> arr1, arr2;
            SetToArray(arr1);
            setToCompare.SetToArray(arr2);
            if (arr1.GetSize() <= arr2.GetSize())
                return false;
            int i = 0, j = 0;
            while (j < arr2.GetSize())
            {
                if (arr1[i] == arr2[j])
                {
                    i++;
                    j++;
                }
                else if (arr2[j] > arr1[i])
                    i++;
                else if (arr2[j] < arr1[i])
                    return false;
            }
            return true;            
        } 
        bool operator >= (const Set<T> & setToCompare)
        {
            if ((*(this) > setToCompare) || (*(this) == setToCompare))
                return true;
            return false;       
        } 
};