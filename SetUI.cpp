#include "C:\Main\Kodiki\C++\SimpleConsoleUI\SimpleConsoleUI.h"
#include <stdio.h>
#include "Set.h"
#include "Student.h"
#include "Set_Tests.cpp"
#include <iostream>

using namespace std;

Shell* Head;
Shell* ChooseType;
Shell* CreateSet;
Shell* ListOfSets;
Shell* SetOperations;
Shell* CreateFromLineOperation;
Shell* InsertOperation;
Shell* RemoveOperation;
Shell* UnionOperation;
Shell* IntersectionOperation;
Shell* SubtractionOperation;
Shell* MapOperation;
Shell* WhereOperation;
Shell* Tests;
Shell* Exit;

struct AllSets
{
    enum SetType
    {
        IntType,
        CharType,
        StudentType,
        NoneType
    };
    SetType type;
    ArraySequence<Set<int>*>    IntSets;
    ArraySequence<string>       IntSetNames;
    ArraySequence<Set<char>*>   CharSets;
    ArraySequence<string>       CharSetNames;
    ArraySequence<Set<Student>*>StudentSets;
    ArraySequence<string>       StudentSetNames;

    AllSets():
        type(NoneType),
        IntSets(),
        IntSetNames(),
        CharSets(),
        CharSetNames(),
        StudentSets(),
        StudentSetNames()
    { }
};

AllSets AS = AllSets();


void Head_Function()
{
    cout << "Hello! This is User Interface for Set.h\n";
    Head->Set_Function(nullptr);
}

void ChooseType_Function()
{
    if (AS.type == AllSets::SetType::NoneType)
    {
        Head->Get_Connector()->Append_Shell(ListOfSets);
        Head->Get_Connector()->Append_Shell(CreateSet);
        Head->Get_Connector()->Append_Shell(SetOperations);
        Head->Get_Connector()->Append_Shell(Tests);
        Head->Get_Connector()->Append_Shell(Exit);
    }
    cout << "Choose type of data to work with:\n"
         << "Input 'Int', 'Char', 'Student'.\n"; 
    string setType;
    cin.clear();
    cin.sync();
    getline(cin, setType);
    while(setType != "Int" && setType != "Char" && setType != "Student")
    {
        cout << "Wrong! Input 'Int', 'Char', 'Student'.\n";
        cin.clear();
        cin.sync();
        getline(cin, setType);
    }
    if (setType == "Int")
    {
        cout << "Got it. Let's work with integers.\n";
        AS.type = AllSets::SetType::IntType;
    }
    else if (setType == "Char")
    {
        cout << "Got it. Let's work with characters.\n";
        AS.type = AllSets::SetType::CharType;
    }
    else if (setType == "Student")
    {
        cout << "Got it. Let's work with stuuudents.\n";
        AS.type = AllSets::SetType::StudentType;
    }
}

void CreateSet_Function()
{
    cout << "Let's create set.\n"
         << "Input name of new set.\n";
    string name;
    cin.clear();
    cin.sync();
    getline(cin, name);
    while (name.size() == 0){
        cout << "Empty name, try another\n.";
        cin.clear();
        cin.sync();
        getline(cin, name);
    }

    switch (AS.type)
    {
        case AllSets::IntType:
            AS.IntSets.Append(new Set<int>);
            AS.IntSetNames.Append(name);
            break;
        case AllSets::CharType:
            AS.CharSets.Append(new Set<char>);
            AS.CharSetNames.Append(name);
            break;
        case AllSets::StudentType:
            AS.StudentSets.Append(new Set<Student>);
            AS.StudentSetNames.Append(name);
            break;
        default:
            cout << "unknown set type";
            break;
    }
    
}

void ListOfSets_Function()
{
    cout << "List of all Sets:\n";
    switch (AS.type)
    {
    case AllSets::IntType:
        for (int i = 0; i < AS.IntSets.GetSize(); i++)
        {
            cout << i+1 << ") Name: " << AS.IntSetNames[i] << "\n"
                 << "Items: \n";
            ArraySequence<int> setAsArray;
            AS.IntSets[i]->SetToArray(setAsArray);
            if (setAsArray.GetSize() != 0)
            {
                for (int j = 0; j < setAsArray.GetSize(); j++)
                    cout << setAsArray[j] << ' ';
                cout << "\n\n";
            }
        }
        break;

    case AllSets::CharType:
        for (int i = 0; i < AS.CharSets.GetSize(); i++)
        {
            cout << i+1 << ") Name: " << AS.CharSetNames[i] << "\n"
                 << "Items: \n";
            ArraySequence<char> setAsArray;
            AS.CharSets[i]->SetToArray(setAsArray);
            if (setAsArray.GetSize() != 0)
            {
                for (int j = 0; j < setAsArray.GetSize(); j++)
                    cout << "'" << setAsArray[j] << "' ";
                cout << "\n\n";
            }
        }
    case AllSets::StudentType:
        for (int i = 0; i < AS.StudentSets.GetSize(); i++)
        {
            cout << i+1 << ") Name: " << AS.StudentSetNames[i] << "\n"
                 << "Items: \n";
            ArraySequence<Student> setAsArray;
            AS.StudentSets[i]->SetToArray(setAsArray);
            if (setAsArray.GetSize() != 0)
            {
                for (int j = 0; j < setAsArray.GetSize(); j++)
                    cout << setAsArray[j].name << ", IQ: " << setAsArray[j].IQ << ", Grade: " << setAsArray[j].grade << "\n\n";
                cout << "\n";
            }
        }
        break;
    default:
        cout << "unknown set type";
    }
    
}

void CreateFromLineOperation_Function()
{
    switch (AS.type)
    {
    case AllSets::IntType:
    {

        cout << "Choose Set to fill it from line.\n";
        int number;
        cout << "From 1 to " << AS.IntSets.GetSize() << "\n";
        cin >> number;
        while (number < 1 && AS.IntSets.GetSize() < number)
        {
            cout << "Wrong! From 1 to " << AS.IntSets.GetSize() << "\n";
            cin >> number;
        }
        number -= 1;
        cout << "\nInput your line with spaces between values.\n";
        string line;
        cin.clear();
        cin.sync();
        getline(cin, line);
        ArraySequence<int> numbers;
        int current = 0;
        int degree = 1;
        for (int i = line.size()-1; i >= 0; i--)
        {
            if (0 <= line[i]-48 && line[i]-48 <= 9)
            {
                current += (line[i] - 48)*degree;
                degree *= 10;
            }
            else
            {
                if (!(current == 0 && degree == 1))
                    numbers.Append(current);
                current = 0;
                degree = 1;  
            }
        }
        if (!(current == 0 && degree == 1))
            numbers.Append(current);

        AS.IntSets[number] = new Set<int>(numbers);
        break;
    }

    case AllSets::CharType:
    {
        cout << "Choose Set to fill it from line.\n";
        int number;
        cout << "From 1 to " << AS.CharSets.GetSize() << "\n";
        cin >> number;
        while (number < 1 && AS.CharSets.GetSize() < number)
        {
            cout << "Wrong! From 1 to " << AS.CharSets.GetSize() << "\n";
            cin >> number;
        }
        number -= 1;
        cout << "\nInput your line without any spaces between characters. (You can use space as a value)\n";
        string line;
        cin.clear();
        cin.sync();
        getline(cin, line);
        ArraySequence<char> characters;

        for (int i = 0; i < line.size(); i++)
            characters.Append(line[i]);

        AS.CharSets[number] = new Set<char>(characters);
        break;
    }
    case AllSets::StudentType:
        cout << "Trust me: this will not be funny at all. Let's fill set with insert function.\n";
        break;
    default:
        cout << "unknown type of set\n";
        break;
    }
    cout << "Ready!\n";    
}

void InsertOperation_Function()
{
    cout << "Choose Set to insert item in it.\n";
    int number;
    switch (AS.type)
    {

    case AllSets::IntType:
    {
        cout << "From 1 to " << AS.IntSets.GetSize() << "\n";
        cin >> number;
        while (number < 1 && AS.IntSets.GetSize() < number)
        {
            cout << "Wrong! From 1 to " << AS.IntSets.GetSize() << "\n";
            cin >> number;
        }        
        number -= 1;
        int item;
        cout << "Input item to Insert.\n";
        cin >> item;
        AS.IntSets.Get(number)->Insert(item);
        break;
    }
    
    case AllSets::CharType:
    {
        cout << "From 1 to " << AS.CharSets.GetSize() << "\n";
        cin >> number;
        while (number < 1 && AS.CharSets.GetSize() < number)
        {
            cout << "Wrong! From 1 to " << AS.CharSets.GetSize() << "\n";
            cin >> number;
        }        
        number -= 1;
        char item;
        cout << "Input item to Insert.\n";
        cin >> item;
        AS.CharSets.Get(number)->Insert(item);
        break;
    }

    case AllSets::StudentType:
    {
        cout << "From 1 to " << AS.StudentSets.GetSize() << "\n";
        cin >> number;
        while (number < 1 && AS.StudentSets.GetSize() < number)
        {
            cout << "Wrong! From 1 to " << AS.StudentSets.GetSize() << "\n";
            cin >> number;
        }        
        number -= 1;
        Student item;
        cout << "Input name of student to Insert.\n";
        cin >> item.name;
        cout << "Input IQ of student to Insert.\n";
        cin >> item.IQ;
        cout << "Input grade of student to Insert.\n";
        cin >> item.grade;

        AS.StudentSets.Get(number)->Insert(item);
        break;
    }

    default:
        cout << "unknown set type";
    }
    cout << "Ready!\n";    

}

void RemoveOperation_Function()
{
    cout << "Choose Set to remove item from it.\n";
    int number;
    switch (AS.type)
    {

    case AllSets::IntType:
    {
        cout << "From 1 to " << AS.IntSets.GetSize() << "\n";
        cin >> number;
        while (number < 1 && AS.IntSets.GetSize() < number)
        {
            cout << "Wrong! From 1 to " << AS.IntSets.GetSize() << "\n";
            cin >> number;
        }        
        number -= 1;
        int item;
        cout << "Input item to Remove.\n";
        cin >> item;
        AS.IntSets.Get(number)->Remove(item);
        break;
    }

    case AllSets::CharType:
    {
        cout << "From 1 to " << AS.CharSets.GetSize() << "\n";
        cin >> number;
        while (number < 1 && AS.CharSets.GetSize() < number)
        {
            cout << "Wrong! From 1 to " << AS.CharSets.GetSize() << "\n";
            cin >> number;
        }        
        number -= 1;
        char item;
        cout << "Input item to Remove.\n";
        cin >> item;
        AS.CharSets.Get(number)->Remove(item);
        break;
    }

    case AllSets::StudentType:
    {
        cout << "From 1 to " << AS.StudentSets.GetSize() << "\n";
        cin >> number;
        while (number < 1 && AS.StudentSets.GetSize() < number)
        {
            cout << "Wrong! From 1 to " << AS.StudentSets.GetSize() << "\n";
            cin >> number;
        }        
        number -= 1;
        Student item;
        cout << "Input IQ of student to Remove.\n";
        cin >> item.IQ;
        cout << "Input grade of student to Remove.\n";
        cin >> item.grade;
        item.name = "";

        AS.StudentSets.Get(number)->Remove(item);
        break;
    }

    default:
        cout << "unknown set type";
    }
    cout << "Ready!\n";    
}

void UnionOperation_Function()
{
    cout << "Choose first Set for Union.\n";
    int number1, number2;
    switch (AS.type)
    {
    case AllSets::IntType:
    {
        cout << "From 1 to " << AS.IntSets.GetSize() << "\n";
        cin >> number1;
        while (number1 < 1 && AS.IntSets.GetSize() < number1)
        {
            cout << "Wrong! From 1 to " << AS.IntSets.GetSize() << "\n";
            cin >> number1;
        }        
        number1 -= 1;
        cout << "Choose second Set for Union.\n";
        cout << "From 1 to " << AS.IntSets.GetSize() << "\n";
        cin >> number2;
        while (number2 < 1 && AS.IntSets.GetSize() < number2)
        {
            cout << "Wrong! From 1 to " << AS.IntSets.GetSize() << "\n";
            cin >> number2;
        }        
        number2 -= 1;
        
        AS.IntSets.Append(new Set<int>(AS.IntSets.Get(number1)->Union(*(AS.IntSets.Get(number2)))));
        AS.IntSetNames.Append("Union of " + to_string(number1+1) + " and " + to_string(number2+1));
        break;
    }

    case AllSets::CharType:
    {
        cout << "From 1 to " << AS.CharSets.GetSize() << "\n";
        cin >> number1;
        while (number1 < 1 && AS.CharSets.GetSize() < number1)
        {
            cout << "Wrong! From 1 to " << AS.CharSets.GetSize() << "\n";
            cin >> number1;
        }        
        number1 -= 1;
        cout << "Choose second Set for Union.\n";
        cout << "From 1 to " << AS.CharSets.GetSize() << "\n";
        cin >> number2;
        while (number2 < 1 && AS.CharSets.GetSize() < number2)
        {
            cout << "Wrong! From 1 to " << AS.CharSets.GetSize() << "\n";
            cin >> number2;
        }        
        number2 -= 1;
        
        AS.CharSets.Append(new Set<char>(AS.CharSets.Get(number1)->Union(*(AS.CharSets.Get(number2)))));
        AS.CharSetNames.Append("Union of " + to_string(number1+1) + " and " + to_string(number2+1));
        break;
    }

    case AllSets::StudentType:
    {
        cout << "From 1 to " << AS.StudentSets.GetSize() << "\n";
        cin >> number1;
        while (number1 < 1 && AS.StudentSets.GetSize() < number1)
        {
            cout << "Wrong! From 1 to " << AS.StudentSets.GetSize() << "\n";
            cin >> number1;
        }        
        number1 -= 1;
        cout << "Choose second Set for Union.\n";
        cout << "From 1 to " << AS.StudentSets.GetSize() << "\n";
        cin >> number2;
        while (number2 < 1 && AS.StudentSets.GetSize() < number2)
        {
            cout << "Wrong! From 1 to " << AS.StudentSets.GetSize() << "\n";
            cin >> number2;
        }        
        number2 -= 1;
        
        AS.StudentSets.Append(new Set<Student>(AS.StudentSets.Get(number1)->Union(*(AS.StudentSets.Get(number2)))));
        AS.StudentSetNames.Append("Union of " + to_string(number1+1) + " and " + to_string(number2+1));
        break;
    }

    default:
        cout << "unknown set type";
    }
    cout << "Ready!\n"
         << "Name of new set: Union of " + to_string(number1+1) + " and " + to_string(number2+1);    
}

void IntersectionOperation_Function()
{
    cout << "Choose first Set for Intersection.\n";
    int number1, number2;
    switch (AS.type)
    {
    case AllSets::IntType:
    {
        cout << "From 1 to " << AS.IntSets.GetSize() << "\n";
        cin >> number1;
        while (number1 < 1 && AS.IntSets.GetSize() < number1)
        {
            cout << "Wrong! From 1 to " << AS.IntSets.GetSize() << "\n";
            cin >> number1;
        }        
        number1 -= 1;
        cout << "Choose second Set for Intersection.\n";
        cout << "From 1 to " << AS.IntSets.GetSize() << "\n";
        cin >> number2;
        while (number2 < 1 && AS.IntSets.GetSize() < number2)
        {
            cout << "Wrong! From 1 to " << AS.IntSets.GetSize() << "\n";
            cin >> number2;
        }        
        number2 -= 1;
        
        AS.IntSets.Append(new Set<int>(AS.IntSets.Get(number1)->Intersection(*(AS.IntSets.Get(number2)))));
        AS.IntSetNames.Append("Intersection of " + to_string(number1+1) + " and " + to_string(number2+1));
        break;
    }

    case AllSets::CharType:
    {
        cout << "From 1 to " << AS.CharSets.GetSize() << "\n";
        cin >> number1;
        while (number1 < 1 && AS.CharSets.GetSize() < number1)
        {
            cout << "Wrong! From 1 to " << AS.CharSets.GetSize() << "\n";
            cin >> number1;
        }        
        number1 -= 1;
        cout << "Choose second Set for Intersection.\n";
        cout << "From 1 to " << AS.CharSets.GetSize() << "\n";
        cin >> number2;
        while (number2 < 1 && AS.CharSets.GetSize() < number2)
        {
            cout << "Wrong! From 1 to " << AS.CharSets.GetSize() << "\n";
            cin >> number2;
        }        
        number2 -= 1;
        
        AS.CharSets.Append(new Set<char>(AS.CharSets.Get(number1)->Intersection(*(AS.CharSets.Get(number2)))));
        AS.CharSetNames.Append("Intersection of " + to_string(number1+1) + " and " + to_string(number2+1));
        break;
    }

    case AllSets::StudentType:
    {
        cout << "From 1 to " << AS.StudentSets.GetSize() << "\n";
        cin >> number1;
        while (number1 < 1 && AS.StudentSets.GetSize() < number1)
        {
            cout << "Wrong! From 1 to " << AS.StudentSets.GetSize() << "\n";
            cin >> number1;
        }        
        number1 -= 1;
        cout << "Choose second Set for Intersection.\n";
        cout << "From 1 to " << AS.StudentSets.GetSize() << "\n";
        cin >> number2;
        while (number2 < 1 && AS.StudentSets.GetSize() < number2)
        {
            cout << "Wrong! From 1 to " << AS.StudentSets.GetSize() << "\n";
            cin >> number2;
        }        
        number2 -= 1;
        
        AS.StudentSets.Append(new Set<Student>(AS.StudentSets.Get(number1)->Intersection(*(AS.StudentSets.Get(number2)))));
        AS.StudentSetNames.Append("Intersection of " + to_string(number1+1) + " and " + to_string(number2+1));
        break;
    }

    default:
        cout << "unknown set type";
    }
    cout << "Ready!\n"
         << "Name of new set: Intersection of " + to_string(number1+1) + " and " + to_string(number2+1);    
}

void SubtractionOperation_Function()
{
    cout << "Choose first Set for Subtraction.\n";
    int number1, number2;
    switch (AS.type)
    {
    case AllSets::IntType:
    {
        cout << "From 1 to " << AS.IntSets.GetSize() << "\n";
        cin >> number1;
        while (number1 < 1 && AS.IntSets.GetSize() < number1)
        {
            cout << "Wrong! From 1 to " << AS.IntSets.GetSize() << "\n";
            cin >> number1;
        }        
        number1 -= 1;
        cout << "Choose second Set for Subtraction.\n";
        cout << "From 1 to " << AS.IntSets.GetSize() << "\n";
        cin >> number2;
        while (number2 < 1 && AS.IntSets.GetSize() < number2)
        {
            cout << "Wrong! From 1 to " << AS.IntSets.GetSize() << "\n";
            cin >> number2;
        }        
        number2 -= 1;
        
        AS.IntSets.Append(new Set<int>(AS.IntSets.Get(number1)->Subtraction(*(AS.IntSets.Get(number2)))));
        AS.IntSetNames.Append("Subtraction of " + to_string(number1+1) + " and " + to_string(number2+1));
        break;
    }

    case AllSets::CharType:
    {
        cout << "From 1 to " << AS.CharSets.GetSize() << "\n";
        cin >> number1;
        while (number1 < 1 && AS.CharSets.GetSize() < number1)
        {
            cout << "Wrong! From 1 to " << AS.CharSets.GetSize() << "\n";
            cin >> number1;
        }        
        number1 -= 1;
        cout << "Choose second Set for Subtraction.\n";
        cout << "From 1 to " << AS.CharSets.GetSize() << "\n";
        cin >> number2;
        while (number2 < 1 && AS.CharSets.GetSize() < number2)
        {
            cout << "Wrong! From 1 to " << AS.CharSets.GetSize() << "\n";
            cin >> number2;
        }        
        number2 -= 1;
        
        AS.CharSets.Append(new Set<char>(AS.CharSets.Get(number1)->Subtraction(*(AS.CharSets.Get(number2)))));
        AS.CharSetNames.Append("Subtraction of " + to_string(number1+1) + " and " + to_string(number2+1));
        break;
    }

    case AllSets::StudentType:
    {
        cout << "From 1 to " << AS.StudentSets.GetSize() << "\n";
        cin >> number1;
        while (number1 < 1 && AS.StudentSets.GetSize() < number1)
        {
            cout << "Wrong! From 1 to " << AS.StudentSets.GetSize() << "\n";
            cin >> number1;
        }        
        number1 -= 1;
        cout << "Choose second Set for Subtraction.\n";
        cout << "From 1 to " << AS.StudentSets.GetSize() << "\n";
        cin >> number2;
        while (number2 < 1 && AS.StudentSets.GetSize() < number2)
        {
            cout << "Wrong! From 1 to " << AS.StudentSets.GetSize() << "\n";
            cin >> number2;
        }        
        number2 -= 1;
        
        AS.StudentSets.Append(new Set<Student>(AS.StudentSets.Get(number1)->Subtraction(*(AS.StudentSets.Get(number2)))));
        AS.StudentSetNames.Append("Subtraction of " + to_string(number1+1) + " and " + to_string(number2+1));
        break;
    }

    default:
        cout << "unknown set type";
    }
    cout << "Ready!\n"
         << "Name of new set: Subtraction of " + to_string(number1+1) + " and " + to_string(number2+1);    
}

int MultByTwo(int x)
{
    return x*2;
}

char CharShift(char orig)
{ 
    if ((48 <= orig) & (orig <= 57))
    {
        char result;
        result = (orig - 47) % 10;
        return (result >= 0) ? (result + 48) : (10 + result + 48);
    }

    if ((65 <= orig) & (orig <= 90))
    {
        char result;
        result = (orig - 64) % 26;
        return (result >= 0) ? (result + 65) : (26 + result + 65);
    }

    if ((97 <= orig) & (orig <= 122))
    {
        char result;
        result = (orig - 96) % 26;
        return (result >= 0) ? (result + 97) : (26 + result + 97);
    }
    return orig;    
}

Student MakeAustrianPainter(Student student)
{
    Student result;
    result.name = student.name + " Hitler";
    result.IQ = student.IQ * 2;
    result.grade = 2;
    return result;
}

void MapOperation_Function()
{
    int number;
    switch (AS.type)
    {

    case AllSets::IntType:
    {
        cout << "In this section I want to offer you one cool opportunity: multiply any number by Two!!!\n"
                "Choose Set ";
        cout << "from 1 to " << AS.IntSets.GetSize() << " to multiply it.\n";
        cin >> number;
        while (number < 1 && AS.IntSets.GetSize() < number)
        {
            cout << "Wrong! From 1 to " << AS.IntSets.GetSize() << "\n";
            cin >> number;
        }        
        number -= 1;
        AS.IntSets.Append(new Set<int>(AS.IntSets.Get(number)->Map(MultByTwo)));
        AS.IntSetNames.Append("Mapped " + to_string(number+1));
        break;
    }

    case AllSets::CharType:
    {
        cout << "In this section I want to offer you one cool opportunity: replace each character with the next one!!!\n"
                "Choose Set ";
        cout << "from 1 to " << AS.CharSets.GetSize() << " to transform it.\n";
        cin >> number;
        while (number < 1 && AS.CharSets.GetSize() < number)
        {
            cout << "Wrong! From 1 to " << AS.CharSets.GetSize() << "\n";
            cin >> number;
        }        
        number -= 1;
        AS.CharSets.Append(new Set<char>(AS.CharSets.Get(number)->Map(CharShift)));
        AS.CharSetNames.Append("Mapped " + to_string(number+1));
        break;
    }

    case AllSets::StudentType:
    {
        cout << "Wait a minute! In this section I want to offer you one cool opportunity:\n"
             << "Give each student surname of one unppular Austrian Painter!!!"
                "Choose Set ";
        cout << "from 1 to " << AS.StudentSets.GetSize() << " to transform it.\n";
        cin >> number;
        while (number < 1 && AS.StudentSets.GetSize() < number)
        {
            cout << "Wrong! From 1 to " << AS.StudentSets.GetSize() << "\n";
            cin >> number;
        }        
        number -= 1;

        AS.StudentSets.Append(new Set<Student>(AS.StudentSets.Get(number)->Map(MakeAustrianPainter)));
        AS.StudentSetNames.Append("Mapped " + to_string(number+1));
        break;
    }

    default:
        cout << "unknown set type";
    }
    cout << "Ready!\n"
         << "Name of new set: Mapped " + to_string(number+1); 
}

bool OnlyEven(int x)
{
    return ((x%2) == 0);
}

bool OnlyDigits(char x)
{
    if (48 <= x && x <= 57)
        return true;
    return false;
}

bool OnlySmart(Student x)
{
    if (x.IQ >= 75)
        return true;
    return false;
}

void WhereOperation_Function()
{
    int number;
    switch (AS.type)
    {
    case AllSets::IntType:
    {
        cout << "In this section we can remove all uneven numbers from set.\n"
                "Choose Set ";
        cout << "from 1 to " << AS.IntSets.GetSize() << ".\n";
        cin >> number;
        while (number < 1 && AS.IntSets.GetSize() < number)
        {
            cout << "Wrong! From 1 to " << AS.IntSets.GetSize() << "\n";
            cin >> number;
        }        
        number -= 1;
        AS.IntSets.Append(new Set<int>(AS.IntSets.Get(number)->Where(OnlyEven)));
        AS.IntSetNames.Append("Whered " + to_string(number+1));
        break;
    }

    case AllSets::CharType:
    {
        cout << "In this section we can remove everything but digits numbers from set.\n"
                "Choose Set ";
        cout << "from 1 to " << AS.CharSets.GetSize() << " to transform it.\n";
        cin >> number;
        while (number < 1 && AS.CharSets.GetSize() < number)
        {
            cout << "Wrong! From 1 to " << AS.CharSets.GetSize() << "\n";
            cin >> number;
        }        
        number -= 1;
        AS.CharSets.Append(new Set<char>(AS.CharSets.Get(number)->Where(OnlyDigits)));
        AS.CharSetNames.Append("Whered " + to_string(number+1));
        break;
    }

    case AllSets::StudentType:
    {
        cout << "In this section we can remove every student with IQ < 75 from set.\n"
                "Choose Set ";
        cout << "from 1 to " << AS.StudentSets.GetSize() << " to transform it.\n";
        cin >> number;
        while (number < 1 && AS.StudentSets.GetSize() < number)
        {
            cout << "Wrong! From 1 to " << AS.StudentSets.GetSize() << "\n";
            cin >> number;
        }        
        number -= 1;

        AS.StudentSets.Append(new Set<Student>(AS.StudentSets.Get(number)->Where(OnlySmart)));
        AS.StudentSetNames.Append("Whered " + to_string(number+1));
        break;
    }

    default:
        cout << "unknown set type";
    }
    cout << "Ready!\n"
         << "Name of new set: Whered " + to_string(number+1); 
}

void Tests_Function()
{
    StartAllTests();
}

void Exit_Function()
{
    cout << "Confirm exit from the program. Type EXIT\n";
    string UserText; 
    cin.clear();
    cin.sync();
    getline(cin, UserText);
    if (UserText == "EXIT")
    {
        cout << "So sad.. Bye!\n"; 
        exit(1);
    }
    else 
    {
        cout << "Then.. let's stay together!\n";
    }
}

int main()
{
    Head =                    new Shell("Head Window",            Head_Function,                      new Connector);
    ChooseType =              new Shell("Choose Type",            ChooseType_Function,                new Connector);
    CreateSet =               new Shell("Create Set",             CreateSet_Function,                 new Connector);
    ListOfSets =              new Shell("List of Sets",           ListOfSets_Function,                new Connector);
    SetOperations =           new Shell("Set Operations",         nullptr,                            new Connector);
    CreateFromLineOperation = new Shell("Create Set from Line",   CreateFromLineOperation_Function,   new Connector);
    InsertOperation =         new Shell("Insert in Set",          InsertOperation_Function,           new Connector);
    RemoveOperation =         new Shell("Remove from Set",        RemoveOperation_Function,           new Connector);
    UnionOperation =          new Shell("Union Sets",             UnionOperation_Function,            new Connector);
    IntersectionOperation =   new Shell("Intersect Sets",         IntersectionOperation_Function,     new Connector);
    SubtractionOperation =    new Shell("Subtract Sets",          SubtractionOperation_Function,      new Connector);
    MapOperation =            new Shell("Map-ify Set",            MapOperation_Function,              new Connector);
    WhereOperation =          new Shell("Where-ify Set",          WhereOperation_Function,            new Connector);
    Tests =                    new Shell("Tests",                 Tests_Function,                     new Connector);
    Exit =                    new Shell("Exit",                   Exit_Function,                      new Connector);

    Head->Get_Connector()->Append_Shell(ChooseType);


    ChooseType->Get_Connector()->Append_Shell(Head);
    
    CreateSet->Get_Connector()->Append_Shell(Head);

    ListOfSets->Get_Connector()->Append_Shell(Head);

    SetOperations->Get_Connector()->Append_Shell(CreateFromLineOperation);
    SetOperations->Get_Connector()->Append_Shell(InsertOperation);
    SetOperations->Get_Connector()->Append_Shell(RemoveOperation);
    SetOperations->Get_Connector()->Append_Shell(UnionOperation);
    SetOperations->Get_Connector()->Append_Shell(IntersectionOperation);
    SetOperations->Get_Connector()->Append_Shell(SubtractionOperation);
    SetOperations->Get_Connector()->Append_Shell(MapOperation);
    SetOperations->Get_Connector()->Append_Shell(WhereOperation);
    SetOperations->Get_Connector()->Append_Shell(Head);

    CreateFromLineOperation->Get_Connector()->Append_Shell(Head);

    InsertOperation->Get_Connector()->Append_Shell(InsertOperation);
    InsertOperation->Get_Connector()->Append_Shell(Head);

    RemoveOperation->Get_Connector()->Append_Shell(RemoveOperation);
    RemoveOperation->Get_Connector()->Append_Shell(Head);
    
    UnionOperation->Get_Connector()->Append_Shell(Head);
    
    IntersectionOperation->Get_Connector()->Append_Shell(Head);

    SubtractionOperation->Get_Connector()->Append_Shell(Head);

    MapOperation->Get_Connector()->Append_Shell(Head);

    WhereOperation->Get_Connector()->Append_Shell(Head);
        
    Tests->Get_Connector()->Append_Shell(Head);

    Exit->Get_Connector()->Append_Shell(Head);

    ActiveShell Active(Head, ActiveShell::VScode);
    Active.StartUI();
}