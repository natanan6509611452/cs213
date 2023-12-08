/*
 *  Name: Natanan Phopradit
 *  Student ID: 6509611452
 */

#include "ModifiedLinkedList.h"
#include "Operators.h"
#include <iostream>
using namespace std;

void Operators::cutList(int pos) {
	try {
		if (!(topList < (maxTopLists - 2))) {
			cout << "List stack is not enough to store CUT results" << endl;
		}
		else if (!(topOp < maxTopOps - 1)) { //redundant but for inclusive
			cout << "Operation stack is full" << endl;
		}
		else {
			ModifiedLinkedList* operandList = lists[topList];
			ModifiedLinkedList* left = new ModifiedLinkedList;
			ModifiedLinkedList* right = new ModifiedLinkedList;
			operandList->cut(pos, left, right);
			lists[topList] = left;
			lists[++topList] = right;
			ops[++topOp] = new Op(pos);
			cout << "CUT Operation has been done." << endl;
		}
	}
	catch (const char* e) {
		cout << e << endl;
	}
}
void Operators::cloneList() {
	if (!(topList < maxTopLists-1)){
		cout << "List stack is not enough to CLONE" << endl;
	}
	else if (!(topOp < maxTopOps-1)) {
		cout << "Operation stack is full" << endl;
	}
	else {
		ModifiedLinkedList* operandList = lists[topList]->clone();
		lists[++topList] = operandList;
		ops[++topOp] = new Op(-1);
		cout << "CLONE Operation has been done." << endl;
	}
}
void Operators::undo() {
	if (topOp < 0) {
		cout << "There's no operation to be undone" << endl;
	}
	else {
		if (ops[topOp]->op == "CUT") {
			ModifiedLinkedList* tmpList = lists[topList-1]->mergeWith(lists[topList]);
			lists[topList]->removeAllNodes();
			topList--;
			lists[topList] = tmpList;
			cout << "Undone [CUT] Operator ..." << endl;
		}
		if (ops[topOp]->op == "CLONE") {
			lists[topList]->removeAllNodes();
			topList--;
			cout << "Undone [CLONE] Operator ..." << endl;
		}
		delete ops[topOp];
		topOp--;
	}
}
void Operators::printCurrentList() {
	lists[topList]->print();
}
void Operators::printHistory() {
	cout << "===The lists in the history stack: ===" << endl;
	if (topList >= 0) {
		for (int i = topList; i >= 0; i--) {
			cout << "Index in the stack: " << i << endl;
			lists[i]->print();
		}
	}
	else {
		cout << "[X] Nothing in this stack ..." << endl;
	}
	cout << "============================================" << endl;

	cout << "===The operators in the history stack: ===" << endl;
	if (topOp >= 0) {
		for (int i = topOp; i >= 0; i--) {
			cout << "Index in the stack: " << i << endl;
			 if (ops[i]->op == "CLONE") {
				cout << "Operator: " << ops[i]->op;
			 }
			 else {
				cout << "Operator: " << ops[i]->op << " at position : " << ops[i]->pos;
			 }
			cout << endl;
		}
	}
	else {
		cout << "[X] Nothing in this stack ..." << endl;
	}
	cout << "============================================" << endl;
}

void Operators::makeList(double listValue[], int listSize) {
	if (topList == -1) {
		if (listValue != NULL) {
			ModifiedLinkedList* operandList = new ModifiedLinkedList();
			for (int i = 0; i < listSize; i++) {
				operandList->add(listValue[i]);
			}
			topList++;
			lists[topList] = operandList;
		}
		else {
			cout << "Input list must not be NULL" << endl;
		}
	}
	else {
		cout << "List stack is not empty.";
	}
}

void Operators::reset() {
	while (topOp >= 0) {
		undo();
	}
	topList = -1;
	topOp = -1;
	ModifiedLinkedList* tmpList = lists[0];
	tmpList->removeAllNodes();
	cout << "Stack has been cleared ..." << endl;
}

void Operators::undoAll() {
	while (topOp >= 0) {
		undo();
	}
	cout << "Undo all operations ..." << endl;
}
