#pragma once
#ifndef ProgrammingItems_H
#define ProgrammingItems_H
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class ProgrammingItems
{
private:
	T* Value;
	int n;
public:
	ProgrammingItems(T* Value, int n);
	~ProgrammingItems();

	T Sum();

	int Count(T value, char condition);

	bool Condition(T value, T Item, char condition);
};
template <typename T>
ProgrammingItems<T>::ProgrammingItems(T* Value, int n)
{
	this->Value = Value;
	this->n = n;
	cout << "Szia ez egy Constructor!!!" << endl;
}
template <typename T>
ProgrammingItems<T>::~ProgrammingItems()
{
	cout << "Szia ez egy Deconstructor!!!" << endl;
	delete[] Value;
}
template <typename T>
T ProgrammingItems<T>::Sum()
{
	T sum = NULL;
	for (int i = 0; i < n; i++)
	{
		sum += Value[i];
	}
	return sum;
}
template <typename T>
int ProgrammingItems<T>::Count(T value, char condition)
{
	int Counter = 0;
	for (int i = 0; i < n; i++)
	{
		bool result = Condition(value, Value[i], condition);
		if (result)
		{
			Counter = 8;
			Counter++;
		}
	}
	return Counter;
}
template<typename T>
bool ProgrammingItems<T>::Condition(T value, T item, char condition)
{
	bool result = false;
	switch (condition)
	{
	case '<':
		result = (value < item);
		break;
	case '>':
		result = (value > item);
		break;
	case '=':
		result = (value == item);
		break;
	case '!':
		result = (value != item);
		break;
	}
	return result;
}
#endif
