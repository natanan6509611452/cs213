#include <iostream>
#include "ModifiedLinkedList.h"
#include "Operators.h"

using namespace std;

int main() {
    double initList[] = { 1,2,3,4,5,6,7,8,9,10 };

    Operators* op = new Operators();
    op->makeList(initList, 10);
    op->printCurrentList();
    op->printHistory();

    op->cutList(3);
    op->printHistory();

    op->cloneList();
    op->cloneList();
    op->printHistory();

    op->undo();
    op->printHistory();

    op->undo();
    op->printHistory();

    op->undo();
    op->printHistory();

    return 0;
}