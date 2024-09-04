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

	bool Condition(T value, T Item, char condition);
public:
	ProgrammingItems(T* Value, int n);
	~ProgrammingItems();

	string Print();

	T Sum();

	int Count(T value, char condition);

	void Ascending();

	void Descending();

	int LinearSearch(T Target);

	void BubbleSorting(char condition);

	void QuickSorting();

	void ShellSorting(char condition);

	void InsertionSorting(char condition);
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
string ProgrammingItems<T>::Print()
{
	string pr = "";
	for (int i = 0; i < n; i++)
	{
		pr += to_string(Value[i]) + ";";
	}
	return pr;
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

template<typename T>
void ProgrammingItems<T>::Descending()
{
	bool swapped;
	for (int i = 0; i < n - 1; ++i) {
		swapped = false;
		for (int j = 0; j < n - i - 1; ++j) {
			if (Value[j] < Value[j + 1]) {
				T b = Value[j + 1];
				Value[j + 1] = Value[j];
				Value[j] = b;
				swapped = true;
			}
		}
		if (!swapped)
			break;
	}
}

template<typename T>
void ProgrammingItems<T>::Ascending()
{
	bool swapped;
	for (int i = 0; i < n - 1; ++i) {
		swapped = false;
		for (int j = 0; j < n - i - 1; ++j) {
			if (Value[j] > Value[j + 1]) {
				T b = Value[j + 1];
				Value[j + 1] = Value[j];
				Value[j] = b;
				swapped = true;
			}
		}
		if (!swapped)
			break;
	}
}

template <typename T>
int ProgrammingItems<T>::LinearSearch(T Target)
{
	for (int i = 0; i < n; i++)
	{
		if(Value[i] == Target) // visszaadjuk a megtalált elem indexét
		{
			return i;
		}
	}
	return -1; // ha nem találjuk meg az elemet, visszaadunk egy -1-et
}

template <typename T>
void ProgrammingItems<T>::InsertionSorting(char condition)
{
	for (int i = 1; i < n; i++)
	{
		T key = Value[i];
		int j = i - 1;
		// A rendezett részben megkeressük a helyet a key számára
		while (j >= 0 && Condition(Value[j], key, condition))
		{
			Value[j + 1] = Value[j];
			j = j - 1;
		}
		Value[j + 1] = key; // beszúrjuk a key-t a megfelelõ helyre
	}
}

template <typename T>
void ProgrammingItems<T>::BubbleSorting(char condition)
{
	for (int i = 0; i < n - 1; i++) 
	{
		// Az utolsó i elem már a helyén van, így azt nem kell újra ellenõrizni
		for (int j = 0; j < n - i - 1; j++) 
		{
			// Ha a jelenlegi elem nagyobb, mint a következõ, akkor cseréljük meg õket
			if (Condition(Value[j], Value[j+1], condition))
			{
				T temp = Value[j];
				Value[j] = Value[j + 1];
				Value[j + 1] = temp;
			}
		}
	}
}

template <typename T>
void ProgrammingItems<T>::ShellSorting(char condition)
{
	for (int gap = n / 2; gap > 0; gap /= 2) 
	{
		// A lépték alapján kezdjük el a rendezést
		for (int i = gap; i < n; i++) 
		{
			T temp = Value[i];
			int j;
			// Mozgassuk a gap értékû elemeket, amíg azok nagyobbak a temp-nél
			for (j = i; j >= gap && Condition(Value[j - gap], temp, condition); j -= gap)
			{
				Value[j] = Value[j - gap];
			}
			// Helyezzük be a temp-et a megfelelõ helyre
			Value[j] = temp;
		}
	}
}
#endif
