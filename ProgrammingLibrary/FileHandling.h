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
		int MAX_SIZE = 200;
		char* DataArray = NULL;
		FileHandler(string FilePath)
		{
			this->FilePath = FilePath;
			DataArray = new char[MAX_SIZE];
		};

		FileHandler(string FilePath,int MAX_SIZE)
		{
			this->FilePath = FilePath;
			this->MAX_SIZE = MAX_SIZE;
			DataArray = new char[MAX_SIZE];
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
		while (inFile.get(ch) && i != MAX_SIZE)
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
	for (int i = 0; i < MAX_SIZE; i++)
	{
		cout << DataArray[i];
	}
}
#endif

