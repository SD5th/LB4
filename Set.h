#include <iostream>

using namespace std;

template <typename T>
class Set
{
    private:
        class Node
        {
            public:
                T value;
                Node* left;
                Node* right;
                int height;

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

                void LeftRotate()
                {
                    SwapValues(right);
                    Node* buffer = left;
                    left = right;
                    right = left->right;
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
                    left = right->left;
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

                void UpdateHeight()
                {
                    height = max((left == nullptr ? 0 : left->height + 1), (right == nullptr ? 0 : right->height + 1));
                }

                void Insert(const T& toInsert)
                {
                    if (toInsert < value)
                    {
                        if (left == nullptr)
                            left = new Node(toInsert);
                        else
                            left->Insert(toInsert);
                    }
                    else if (value < toInsert)
                    {
                        if (right == nullptr)
                            right = new Node(toInsert);
                        else
                            right->Insert(toInsert);
                    }
                    UpdateHeight();
                    Balance();
                }

                bool Search(const T& toSearch)
                {
                    if (toSearch == value)
                        return true;
                    else if (toSearch < value)
                    {
                        if (left == nullptr)
                            return false;
                        else
                            return left->Search(toSearch);
                    }
                    else if (value < toSearch)
                    {
                        if (right == nullptr)
                            return false;
                        else
                            return right->Search(toSearch);
                    }
                }

                Node* Remove(const T& toRemove)
                {
                    if (toRemove == value)
                    {
                        if (left == nullptr && right == nullptr)
                        {
                            delete this;
                            return nullptr;
                        }
                        else if (left == nullptr)
                        {
                            Node* toReturn = right;
                            delete this;
                            return toReturn;
                        }
                        else if (right == nullptr)
                        {
                            Node* toReturn = left;
                            delete this;
                            return toReturn;
                        }
                        else
                        {
                            T newValue = right->GetMin();
                            right = right->Remove(newValue);
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
                            left = left->Remove(toRemove);
                            left->Balance();
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
                            right = right->Remove(toRemove);
                            UpdateHeight();
                            return this;
                        }
                    }                
                }
                void CopyConstructor(Node* toCopy)
                {
                    this = new Node(toCopy->value);
                    left->CopyConstructor(toCopy->left);
                    right->CopyConstructor(toCopy->right);
                }

                void Destructor()
                {
                    if (left != null)
                        left->Destructor();
                    if (right != null)
                        right->Destructor();
                    delete this;
                }
                T GetMin()
                {
                    if (left == nullptr)
                        return value;
                    return left->GetMin();
                }
                T GetMax()
                {
                    if (right == nullptr)
                        return value;
                    return right->GetMax();
                }
        };
        Node* root;

    public:
        Set():
            root(nullptr)
        { }
        Set(const Set & toCopy)
        {
            root->CopyConstructor(toCopy.root);
        }
        ~Set()
        {
            root->Destructor();
        }


        T GetMin()
        {
            return root->GetMin();
        }
        T GetMax()
        {
            return root->GetMax();
        }
        void Insert(const T& element)
        {
            if (root == nullptr)
                root = new Node(element);
            else
                root->Insert(element);

        }
        bool Search(const T& element)
        {
            if (root == nullptr)
                return false;
            else
                return root->Search(element);
        }
        void Remove(const T& element)
        {
            root = root->Remove(element);
            root->Balance();
            root->UpdateHeight(); 
        }
};

