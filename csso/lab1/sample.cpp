#include "stdafx.h"
#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	// L-o creat in Wow64Node
	//PHKEY hkey = new HKEY; // PHKEY = HKEY*
	// x64 -> rulea programe compilate pe x64
	// aplicatiile de x86 le pune in wow6432node
	// scade puncte daca nu inchizi handle-ul
	// data viitoare tema

/*	HKEY hkey;
	DWORD disp;

	LONG result = RegCreateKeyEx(
		HKEY_LOCAL_MACHINE,
		L"Software\\123",
		0,
		0,
		REG_OPTION_NON_VOLATILE,
		KEY_WRITE,
		0,
		&hkey,
		&disp
	);

	if (result == ERROR_SUCCESS)
	{
		cout << "cheie create" << endl;
	}
	else
	{
		cout << "eroare " << endl;
	}
	*/
	HKEY hkey;
	DWORD result;
	result = RegOpenKeyEx(
		HKEY_CURRENT_USER,
		L"Software",
		0,
		KEY_READ,
		&hkey);

	if (result == ERROR_SUCCESS)
	{
		cout << "success" << endl;
	}
	else
	{
		cout << "eroare" << endl;
		return 0;
	}

	DWORD subkeys;
	DWORD skLen;
	DWORD values;
	DWORD valMaxLen;
	DWORD maxValLen;

	result = RegQueryInfoKey(
		hkey,
		0,
		0,
		0,
		&subkeys,
		&skLen,
		0,
		&values,
		&valMaxLen,
		&maxValLen,
		0,
		0
	);

	if (result == ERROR_SUCCESS)
	{
		cout << "success on queryInfoKey" << endl;
	}
	else
	{
		cout << "Error on queryInfoKey" << endl;
		return 0;
	}

	cout << subkeys << endl;
	cout << values << endl;

	LPWSTR subkeyName = new WCHAR[valMaxLen + 1];
	// crapa
	for (int i = 0; i < subkeys; ++i) {
		DWORD keyNameLen = skLen + 1;
		
		result = RegEnumKeyEx(
			hkey,
			i,
			subkeyName,
			&keyNameLen,
			NULL,
			NULL,
			NULL,
			NULL
		);


		if (result = ERROR_SUCCESS)
		{
			cout << skLen << endl;
			cout << result << endl;
		}
		else
		{
			cout << "subkey query error" << endl;
			cout << result << endl;
			return 0;
		}
	}

	LPWSTR valueName = new WCHAR[valMaxLen + 1];
	for (int i = 0; i < values; ++i)
	{
		DWORD valNameLen;
		DWORD type;
		DWORD maxLen = valMaxLen;
		LPBYTE data = new BYTE[valMaxLen];
		result = RegEnumValue(
			hkey,
			i,
			valueName,
			&valNameLen,
			NULL,
			&type,
			data,
			&maxLen
		);

		if (result == ERROR_SUCCESS) {

			switch (type)
			{
			case REG_SZ:
				cout << valueName << "\t\t" << (char*)data << endl;
			default:
				cout << valueName << endl;
				break;
			}
		}
		else
		{
			cout << "Subvalue info query error" << endl;
			return 0;
		}
	}

    return 0;
}

