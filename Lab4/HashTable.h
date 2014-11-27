#pragma once
class HashTable
{
public:
	struct ListElement
	{
		int Index;
		std::string Value;
	};
	HashTable();
	~HashTable();
	void AddElement(std::string value, int index);
	void GetIndex(std::string value, int* buf);
private:
	std::vector<ListElement>** headers;
	int GetHash(std::string value);
};

