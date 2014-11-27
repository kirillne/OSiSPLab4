#include "stdafx.h"
#include "HashTable.h"

#define TABLESIZE 255 

HashTable::HashTable()
{
	headers = (std::vector<ListElement>**)calloc(sizeof(ListElement*), TABLESIZE);
	for (int i = 0; i < TABLESIZE; i++)
	{
		headers[i] = new std::vector<ListElement>();
	}
}

void HashTable::AddElement(std::string value, int index)
{
	int hash = GetHash(value);

	HashTable::ListElement element;
	element.Index = index;
	element.Value = value;
	headers[hash]->push_back(element);
}

int HashTable::GetHash(std::string value)
{
	int hash = 0;
	for (int i = 0; i < (value.size() > 3 ? 3 : value.size()); i++)
	{
		hash += -(int)(value[i]);
	}
	hash %= TABLESIZE;
	return hash;
}

void  HashTable::GetIndex(std::string value, int* buf)
{
	int hash = GetHash(value);
	int foundedCount = 0;
	for (std::vector<HashTable::ListElement>::const_iterator it = headers[hash]->begin(); 
		it != headers[hash]->end(); ++it)
	{
		if (!std::strncmp(it->Value.c_str(), value.c_str(), value.size()))
		{
			buf[foundedCount++] = it->Index;
		}
	}
	buf[foundedCount] = -1;
}

HashTable::~HashTable()
{
	for (int i = 0; i < TABLESIZE; i++)
	{
		delete headers[i];
	}
	free(headers);
}