#pragma once
#include <array>
using namespace std;

class Container
{
public: 
	int** arr;
	Container(int row, int col) {
		arr = new int*[row];
		for (int i = 0; i < row; i++) {
			arr[i] = new int[col];
		}
	}
	void mergeSort();
	void quickSort();

};

