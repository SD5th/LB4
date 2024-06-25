#include "Set.h"
#include <cassert>

void Test_DefaultConstructor_ArraySequence()
{
    ArraySequence<int> sequence;
    assert(sequence.GetSize() == 0);

    std::cout << "TestDefaultConstructor_ArraySequence: OK\n";
}