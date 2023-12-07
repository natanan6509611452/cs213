#include "SortAlgorithm.h"
#include <iostream>

using namespace std;

void SortAlgorithm::mergesort(int* start, int* end)
{
	int* mid = start + (int)ceil(distance(start, end) / 2);
	if (start < mid){
		mergesort(start, mid);
		mergesort(mid, end);
		merge(start, end);
	}
}
void SortAlgorithm::merge(int* start, int* end)
{
	int* aux = new int[distance(start, end)];
	int* auxMid = aux + (int)ceil(distance(start, end) / 2);
	int* auxEnd = aux + distance(start, end);
	copy(start, end, aux);
	reverse(auxMid, auxEnd);

	auxEnd--;
	for (; start < end;) {
		*start++ = *aux <= *auxEnd ? *aux++ : *auxEnd--;
	}
}

void SortAlgorithm::quicksort(int* start, int* end)
{
	int* pivot;
	if (start < end) {
		pivot = partition(start, end - 1);
		quicksort(start, pivot);
		quicksort(pivot+1, end);
	}
}

int* SortAlgorithm::partition(int* start, int* end)
{
	int* pivot = end;
	start--;
	while (start < end) {
		while (*(++start) < *pivot) {

		}
		while (*(--end) > *pivot) {
			if (start == end) {
				break;
			}
		}
		if (start >= end) {
			break;
		}
		swap(*start, *end);
	}
	swap(*pivot, *start);
	return start;
}