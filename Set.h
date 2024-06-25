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

                ~Node() = default;

            // Insert-Search-Remove pack of functions
                int GetHeightDifference()
                {
                    return (right == nullptr ? -1 : right->height) - (left == nullptr ? -1 : left->height);
                }

                void SwapValues(const Node* & toSwapFor)
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
                void CopyConstructor_ForSet(const Node* & toCopy)
                {
                    this = new Node(toCopy->value);
                    if (toCopy->left != nullptr)
                        left->CopyConstructor_ForSet(toCopy->left);
                    if (toCopy->left != nullptr)
                        right->CopyConstructor_ForSet(toCopy->right);
                    UpdateHeight();
                }

                void FromArrayConstructor_ForSet(const ArraySequence<T> & array, int left, int right)
                {
                    int mid = (left + right)/2;
                    value = array[mid];
                    if (left < mid)
                    {
                        left = new Node;
                        
                    }
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
                
                void Insert_ForSet(const T& toInsert)
                {
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
                        else
                        {
                            T newValue = right->GetMin_ForSet();
                            this = Remove_ForSet(newValue);
                            value = newValue;
                            return this;
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
                }
       
                void SetToArray_ForSet(const ArraySequence<T>* & result)
                {
                    if (left != nullptr)
                        SetToArray_ForSet(left);
                    result->Append(value);
                    if (right != nullptr)
                        SetToArray_ForSet(right);
                }
        
                void Map_ForSet(const Node & node, T (*function)(T))
                {
                    if (node.left != nullptr)
                    {
                        left = new Node(function(node.left->value));
                        left->Map_ForSet(node.left, function);
                    }
                    if (node.right != nullptr)
                    {
                        right = new Node(function(node.right->value));
                        right->Map_ForSet(node.right, function);
                    }
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
                root->CopyConstructor_ForSet(toCopy.root);
        }

        Set(const ArraySequence<T> & array):
            root(nullptr) 
        {
            if (array.GetSize() != 0)
            {
                SortArray(array, 0, array.GetSize()-1);
                root->FromArrayConstructor_ForSet(array, 0, array.GetSize()-1);
            }
        }

        ~Set()
        {
            root->Destructor_ForSet();
        }

    // User functions
        T GetMin()
        {
            return root->GetMin_ForSet();
        }

        T GetMax()
        {
            return root->GetMax_ForSet();
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

        ArraySequence<T> SetToArray() // Using LNR traversal
        {
            ArraySequence<T> result = *(new ArraySequence<T>);
            if (root != nullptr)
                root->SetToArray_ForSet(result);
            return result;
        }

    // Map, Reduce, Where
        void Map(const Set<T> & set, T (*function)(T))
        {
            if (root != nullptr)
                delete this;
            if (set.root != nullptr)
            {
                root = new Node(function(set.root->value));
                root.Map_ForSet(set.root);
            }
        }
        
        T Reduce (const Set<T> set, T (*function)(T, T), const T & constant)
        {
            if (set.root != nullptr)
                return set.Reduce_ForSet(constant, function);
        }
        
        void Where(const Set<T> & set, bool (*function)(T))
        {
            if (root != nullptr)
                delete this;
            if (set.root != nullptr)
            {
                ArraySequence<T>* unpreparedArray = set.SetToArray();
                ArraySequence<T>* array = new ArraySequence<T>;
                for (int i = 0; i < unpreparedArray->GetSize(); i++)
                    if (function(unpreparedArray[i]))
                        array->Append(unpreparedArray[i]);
                
            }
        }
};