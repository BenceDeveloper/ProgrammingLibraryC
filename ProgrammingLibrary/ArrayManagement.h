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
		if(Value[i] == Target) // visszaadjuk a megtal�lt elem index�t
		{
			return i;
		}
	}
	return -1; // ha nem tal�ljuk meg az elemet, visszaadunk egy -1-et
}

template <typename T>
void ProgrammingItems<T>::InsertionSorting(char condition)
{
	for (int i = 1; i < n; i++)
	{
		T key = Value[i];
		int j = i - 1;
		// A rendezett r�szben megkeress�k a helyet a key sz�m�ra
		while (j >= 0 && Condition(Value[j], key, condition))
		{
			Value[j + 1] = Value[j];
			j = j - 1;
		}
		Value[j + 1] = key; // besz�rjuk a key-t a megfelel� helyre
	}
}

template <typename T>
void ProgrammingItems<T>::BubbleSorting(char condition)
{
	for (int i = 0; i < n - 1; i++) 
	{
		// Az utols� i elem m�r a hely�n van, �gy azt nem kell �jra ellen�rizni
		for (int j = 0; j < n - i - 1; j++) 
		{
			// Ha a jelenlegi elem nagyobb, mint a k�vetkez�, akkor cser�lj�k meg �ket
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
		// A l�pt�k alapj�n kezdj�k el a rendez�st
		for (int i = gap; i < n; i++) 
		{
			T temp = Value[i];
			int j;
			// Mozgassuk a gap �rt�k� elemeket, am�g azok nagyobbak a temp-n�l
			for (j = i; j >= gap && Condition(Value[j - gap], temp, condition); j -= gap)
			{
				Value[j] = Value[j - gap];
			}
			// Helyezz�k be a temp-et a megfelel� helyre
			Value[j] = temp;
		}
	}
}
#endif
