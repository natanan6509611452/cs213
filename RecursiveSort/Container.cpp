#include <iostream>
#include <algorithm>
#include "SortAlgorithm.h"
using namespace std;

int main() {
	int arr[] = {5,85,1,65,4,8,0,55,6,33,23,35,57,84,86,67,2,9};
	cout << "==========" << "before merge" << "==========" << endl;
	for (int a : arr) {
		cout << a << " ";
	}
	cout << endl;

	SortAlgorithm::mergesort(begin(arr), end(arr));
	cout << "==========" << "after merge" << "==========" << endl;
	for (int a : arr) {
		cout << a << " ";
	}
	cout << endl;

	cout << "==========" << "before quick" << "==========" << endl;
	random_shuffle(begin(arr), end(arr));
	
	for (int a : arr) {
		cout << a << " ";
	}
	cout << endl;

	SortAlgorithm::quicksort(begin(arr), end(arr));
	cout << "==========" << "after quick" << "==========" << endl;
	for (int a : arr) {
		cout << a << " ";
	}
	cout << endl;
	
}
