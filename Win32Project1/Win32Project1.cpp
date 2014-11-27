// Win32Project1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


typedef struct  Record
{
	std::string Surname;
	std::string Name;
	std::string SecName;
	int PhoneNumber;
	std::string Streat;
	int House;
	int Building;
	int Flat;
};

typedef  int (*SearchSurnameType)(char* surname, Record* buf);

typedef  int(*SearchPhoneType)(int number, Record* buf);

typedef  void (*ChangeType)(Record oldRecord, Record newRecord);

typedef  void AddType(Record record);

typedef  void DeleteType(Record record);

SearchSurnameType SearchSurname;

SearchPhoneType SearchPhone;


ChangeType Change;


bool LoadDatabaseDLL(void)
{
	HMODULE hModule = LoadLibrary(TEXT("Lab4.dll"));
	DWORD error = 0;

	if (hModule == NULL)
		error = GetLastError();
	else {
		SearchSurname = (SearchSurnameType)GetProcAddress(hModule, "?SearchSurname@@YAHPADPAURecord@@@Z");
		SearchPhone = (SearchPhoneType)GetProcAddress(hModule, "?SearchPhoneNumber@@YAHHPAURecord@@@Z");
		Change = (ChangeType)GetProcAddress(hModule, "?Change@@YAXURecord@@0@Z");
	}

	if (error) {
		DWORD systemLocale = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);
		HLOCAL hlocal = NULL;


		return FALSE;
	}
	else
		return TRUE;
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, ".1251");
	LoadDatabaseDLL();
	Record res[255];
	int count = 0;
	char* surname = "блб";
	count = SearchSurname(surname, res);
	for (int i = 0; i < count; i++)
	{
		std::cout << res[i].PhoneNumber << " " << res[i].Surname << " " << res[i].Name << " " << res[i].SecName << " " << res[i].Streat << " " << res[i].House << " " << res[i].Building << " " << res[i].Flat << std::endl;
	}
	Record newres = res[0];
	newres.Flat = 15;

	Change(res[0], newres);

	count = SearchPhone(212036, res);
	for (int i = 0; i < count; i++)
	{
		std::cout << res[i].PhoneNumber << " " << res[i].Surname << " " << res[i].Name << " " << res[i].SecName << " " << res[i].Streat << " " << res[i].House << " " << res[i].Building << " " << res[i].Flat << std::endl;
	}
	int a;
	std::cin >> a;
	return 0;
}

