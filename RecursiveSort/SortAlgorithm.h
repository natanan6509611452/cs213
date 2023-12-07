#pragma once
#include <iterator>
using namespace std;
class SortAlgorithm
{
public :
	static void mergesort(int* start, int* end);
	static void quicksort(int* start, int* end);
private :
	static void merge(int* start, int* end);
	static int* partition(int* start, int* end);
};