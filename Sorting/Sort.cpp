#include "Sort.h"


int getRand(int low, int high)
{
	static std::random_device rd;
	static std::mt19937 mt(rd());
	std::uniform_int_distribution<> dist(low, high);
	return dist(mt);
}

std::vector<int> generate(int size)
{
	std::vector<int> r(size);
	for (auto & e : r)
	{
		e = getRand(0, size);
	}
	return r;
}

void timeSort(int size, std::function<void(std::vector<int>&)> function)
{
	auto v = generate(size);
	auto start = std::chrono::system_clock::now();
	function(v);
	auto end = std::chrono::system_clock::now();
	auto duration = end - start;
	auto sec = std::chrono::duration_cast<std::chrono::duration<float>>(duration);
	std::cout << "Size: " << size << "\tTime: " << sec.count() << std::endl;
	
}

void testFunction(std::string name, std::function<void(std::vector<int>&)> f)
{
	std::cout << name << std::endl;
	for (auto size = 100u; size <= 100000; size *= 10)
		timeSort(size, f);
}

void stdSort(std::vector<int> & r)
{
	std::sort(r.begin(), r.end());
}
void bubbleSort(std::vector<int> a)
{
	auto swapped = true;
	while (swapped)
	{
		swapped = false;
		for (size_t i = 0; i < a.size() - 1; i++)
		{
			
			if (a[i] > a[i + 1])
			{
				std::swap(a[i], a[i + 1]);
				swapped = true;
			}
		}
	}
}

void insertionSort(std::vector<int>& a)
{
	for (size_t i = 1; i < a.size(); i++)
		for (size_t j = 0; j < i; j++)
			if (a[j] < a[i])
			{
				std::swap(a[j], a[i]);
			}
}

int min(std::vector <int>& a, int start)
{
	auto min = std::numeric_limits<int>::max();
	auto cur = -1;
	for (size_t i = start; i < a.size(); i++)
	{
		if (min > a[i])
		{
			min = a[i];
			cur = 1;
		}
	}
	return cur;
}
void selectionSort(std::vector<int>& a)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		auto smallest = min(a, i);
		std::swap(a[i], a[smallest]);
	}
}

std:: vector<int> merge(std::vector<int> &a, std::vector<int>& b)
{
	size_t i = 0; 
	size_t j = 0; 
	std::vector<int> memory;
	memory.reserve(a.size() + b.size());
	while (i < a.size() && j < b.size())
	{
		if (a[i] < b[j])
		{
			memory.push_back(a[i]); i++;
		}
		else
		{
			memory.push_back(b[j]); j++;
		}
	}
	if (i < a.size())
	{
		for (size_t k = i; k < a.size(); k++)
			memory.push_back(a[k]);
	}
	else
	{
		for (size_t k = j; k < b.size(); k++)
			memory.push_back(b[k]);
	}
	if (i == a.size())
	{
		while (j < b.size())
		{
			memory.push_back(b[j]);
			j++;
		}
	}
	return memory;
}

void mergeSort(std::vector<int> & v)
{
	if (v.size() < 1) return;
	auto mid = v.size() / 2;
	std::vector<int> a(v.begin(), v.begin() + mid);
	std::vector<int> b(v.begin() + mid + 1, v.end());
	mergeSort(a);
	mergeSort(b);
	v = merge(a, b);
}

int partition(std::vector<int> &v, int start, int end)
{
	int pivotValue = v[end];
	int left = start;
	for (auto i = start; i < end; i++)
	{
		if (v[i] <= pivotValue)
		{
			std::swap(v[left], v[i]);
			left++;
		}
	}
	
	std::swap(v[left], v[end]);

	return left;
}

void quickSort(std::vector<int> &v, int start, int end)
{
	if (start < end)
	{
		int p = partition(v, start, end);
		quickSort(v, start, p - 1);
		quickSort(v, p + 1, end);
	}
	return;
}

void quickSortWrapper(std::vector<int> &v)
{
	quickSort(v, 0, v.size()-1);
}
