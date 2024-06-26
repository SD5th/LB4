#include <iostream>

using namespace std;

class Student
{
    public:
        Student():
            name("Unknown Artist"),
            IQ(75),
            grade(4)
        { }
        Student(string name, int IQ, float grade):
            name(name),
            IQ(IQ),
            grade(grade)
        { }

        string name;
        int IQ;
        float grade;

    bool operator == (const Student & student) const
    {
        if (IQ == student.IQ && grade == student.grade)
            return true;
        return false;
    }
    
    bool operator != (const Student & student) const
    {
        if (IQ == student.IQ && grade == student.grade)
            return false;
        return true;
    }

    bool operator > (const Student & student) const
    {
        if (IQ > student.IQ)
            return true;
        if (IQ == student.IQ)
            if (grade > student.grade)
                return true;
        return false;
    }
    bool operator >= (const Student & student) const
    {
        if (IQ >= student.IQ)
            return true;
        return false;
    }
    bool operator < (const Student & student) const
    {
        if (IQ < student.IQ)
            return true;
        if (IQ == student.IQ)
            if (grade < student.grade)
                return true;        
        return false;
    }
    bool operator <= (const Student & student) const
    {
        if (IQ <= student.IQ)
            return true;
        return false;
    }

};