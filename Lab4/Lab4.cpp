// Lab4.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Lab4.h"
#include "HashTable.h"

bool databaseOpened = false;

void CloseDatabase();

void OpenDatabase();

std::vector<Record>* dataBase;

HashTable* hashTable;


BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		if (!databaseOpened)
			OpenDatabase();

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		if (databaseOpened)
			CloseDatabase();
		break;
	}
	return TRUE;
}

BOOL ReadLine(HANDLE hFile, char *pszBuffer, DWORD dwSize)
{
	DWORD i, dwRead;
	
	if (!ReadFile(hFile, pszBuffer, dwSize, &dwRead, NULL) || (dwRead == 0))
	{
		SetLastError(ERROR_HANDLE_EOF);
		return FALSE;
	}

	for (i = 0; i < dwRead; i++)
	{
		BYTE c = ((BYTE *)pszBuffer)[i];
		if (c == '\r')
		{
			((BYTE *)pszBuffer)[i] = 0;
			if (i + 1 < dwRead && ((BYTE *)pszBuffer)[i + 1] == '\n')
			{
				i++;
			}
			break;
		}
		else if (c == '\n')
		{
			((BYTE *)pszBuffer)[i] = 0;
			break;
		}
	}

	if (i >= dwRead)
	{
		((BYTE *)pszBuffer)[i] = 0;
	}
	else
	{
		i++;
	}

	SetFilePointer(hFile, i - dwRead, NULL, FILE_CURRENT);

	return TRUE;
}

void OpenDatabase()
{
	HANDLE hFile;
	hFile = CreateFile(TEXT("telbase.txt"), GENERIC_READ,  0,   NULL, OPEN_EXISTING,  FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		SetLastError(ERROR_FILE_INVALID);
		return;
	}
	
	hashTable = new HashTable();
	dataBase = new std::vector<Record>();

	char string[255];
	int size = 255;
	while (ReadLine(hFile, string, size))
	{
		char element[255];
		int elementStart = 0;
		Record record;
		
		elementStart = ReadElement(element, string, elementStart);
		record.Index = atoi(element);

		elementStart = ReadElement(element, string, elementStart);
		record.Surname = std::string(element);

		elementStart = ReadElement(element, string, elementStart);
		record.Name = std::string(element);

		elementStart = ReadElement(element, string, elementStart);
		record.SecName = std::string(element);

		elementStart = ReadElement(element, string, elementStart);
		record.Streat = std::string(element);

		elementStart = ReadElement(element, string, elementStart);
		record.House = atoi(element);

		elementStart = ReadElement(element, string, elementStart);
		record.Building = atoi(element);

		elementStart = ReadElement(element, string, elementStart);
		record.Flat = atoi(element);

		int index = dataBase->size();
		dataBase->push_back(record);
		hashTable->AddElement(record.Surname, index);
	}
	databaseOpened = true;
	CloseHandle(hFile);
}

int ReadElement(char *element, char* string, int start)
{
	int i = start;
	int elementIndex = 0;
	while (string[i] != ';') 
	{
		element[elementIndex++] = string[i++];
	}
	element[elementIndex] = 0;
	return i+1;
}

void CloseDatabase()
{
	delete hashTable;
	delete dataBase;
	databaseOpened = false;
}

LAB4_API void Search(char* surname, Record* buf)
{
	return;
}

LAB4_API void Change(Record oldRecord, Record newRecord)
{
	int a = 42;
}

LAB4_API void Add( Record record)
{
	int a = 42;
}

LAB4_API void Delete(Record record)
{
	int a = 42;
}