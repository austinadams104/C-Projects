#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <algorithm>
#include <functional>
#include <chrono>
#include <vector>
#include <random>
#include <string>

int getRand(int low, int high);
void timeSort(int size, std::function<void(std::vector<int>&)> function);
void testFunction(std::string name, std::function<void(std::vector<int>&)> f);
void stdSort(std::vector<int> & r);
void bubbleSort(std::vector<int> a);
void insertionSort(std::vector<int>& a);
int min(std::vector <int>& a, int start);
void selectionSort(std::vector<int>& a);
std::vector<int> merge(std::vector<int> &a, std::vector<int>& b);
void mergeSort(std::vector<int> & v);
int partition(std::vector<int> & v, int start, int end);
void quickSort(std::vector<int>&v, int start, int end);
void quickSortWrapper(std::vector<int> &v);

#endif;