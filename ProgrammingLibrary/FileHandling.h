#pragma once
#ifndef FileReader_H
#define FileReader_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class FileHandler
{
	public:
		string FilePath;
		int n;
		char* DataArray = new char[n];
		FileHandler(string FilePath)
		{
			this->FilePath = FilePath;
		};
		~FileHandler()
		{
			delete[] DataArray;
		};
		void FileReader();
		void FileWritter();
		void Print();
};
void FileHandler::FileReader()
{
	char ch = ' ';
	ifstream inFile(FilePath);
	if (inFile.is_open())
	{
		int i = 0;
		while (inFile.get(ch))
		{
			DataArray[i] = ch;
			i++;
		}
		inFile.close();  // Fájl lezárása
	}
	else 
	{
		cerr << "Nem lehet megnyitni a fájlt olvasásra." << std::endl;
	}
}
void FileHandler::FileWritter()
{
	
}

void FileHandler::Print()
{
	for (int i = 0; i < n; i++)
	{
		cout << DataArray[i] << endl;
	}
}
#endif

