#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


void quickSort(vector<int>& arr, int low, int high);
void mergeSort(vector<int>& arr, int left, int right);
void heapSort(vector<int>& arr);
void shellSort(vector<int>& arr);


long long calcularMemoriaBytes(const vector<int>& arr, bool esMergeSort);

#endif
