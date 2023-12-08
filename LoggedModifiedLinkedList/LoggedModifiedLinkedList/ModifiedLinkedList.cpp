/*
 *  Name: Natanan Phopradit
 *  Student ID: 6509611452
 */

#include "ModifiedLinkedList.h"
#include <iostream>

void ModifiedLinkedList::add(double n) {
	counter++;
	if (counter == 0) {
		head = mid = new Node(n);
	}
	else {
		Node* newNode = new Node(n);
		newNode->next = head;
		head = newNode;

		mid = head;
		for (int i = 0; i < ((counter+1)/2)-1; i++) {
			mid = mid->next;
		}
	}
}

void ModifiedLinkedList::getData(double* & result, int & count) {
	result = new double[counter];
	Node* tmp = head;
	for (int i = 0; tmp != NULL; i++) {
		result[i] = tmp->data;
		tmp = tmp->next;
	}
	count = counter;
}

ModifiedLinkedList* ModifiedLinkedList::clone() {
	ModifiedLinkedList* copyList = new ModifiedLinkedList();
	double* listData;
	getData(listData, counter);
	for (int i = counter-1; i >= 0; i--) {
		copyList->add(listData[i]);
	}
	return copyList;
}

ModifiedLinkedList* ModifiedLinkedList::mergeWith(ModifiedLinkedList* inputList) {
	ModifiedLinkedList* tmpList = inputList->clone();
	double* listData;
	getData(listData, counter);

	for (int i = counter - 1; i >= 0; i--) {
		tmpList->add(listData[i]);
	}

	return tmpList;
}

int ModifiedLinkedList::cut(int pos, ModifiedLinkedList* &left, ModifiedLinkedList* &right) {
	if (pos >= counter || pos <= 0) {
		throw "Position to cut is out of range (must be between 0 and size of list (exclusive))";
	}
	else {
		Node* tmp = head;
		double* listData;
		int i;

		left = new ModifiedLinkedList();
		right = new ModifiedLinkedList();

		getData(listData, counter);
		for (i = pos - 1; i >= 0; i--) {
			left->add(listData[i]);
		}
		for (i = counter - 1; i >= pos; i--) {
			right->add(listData[i]);
		}
		return pos;
	}
}

void ModifiedLinkedList::removeAllNodes() {
	Node* tmp;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		delete tmp;
	}
	counter = 0;
	head = NULL;
	mid = NULL;
}

void ModifiedLinkedList::print() {
	Node* tmp = head;
	while (tmp != mid) {
		std::cout << tmp->data << " ";
		tmp = tmp->next;
	}
	std::cout << "[" << tmp->data << "] ";
	tmp = tmp->next;
	while (tmp != NULL) {
		std::cout << tmp->data << " ";
		tmp = tmp->next;
	}
	std::cout << ", Mid = :" << mid->data << std::endl;
}



