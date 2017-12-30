#include "stdafx.h"
#include <windows.h>

int main()
{
	Sleep(100);
	HANDLE map_file = OpenFileMapping(FILE_MAP_READ, FALSE, TEXT("mem1"));

	if (map_file == NULL)
	{
		_tprintf(_T("(Child) File mapping is null\n"));
		return 1;
	}

	char* map_ptr = (char *) MapViewOfFile(map_file, FILE_MAP_READ, 0, 0, 0);
	 
	if (map_ptr == NULL)
	{
		_tprintf(_T("(Child) PTR is null \n"));
	}

	_tprintf(_T("(CHILD) BEfore reading the first number\n"));
	HANDLE hMutex = OpenMutex(SYNCHRONIZE, TRUE, _T("mt"));
	for (int i = 1; i <= 200; i++)
	{		
		WaitForSingleObject(hMutex, INFINITE);
		DWORD a, b;

		CopyMemory((LPVOID) &a, map_ptr, sizeof (DWORD));
		map_ptr += sizeof (DWORD);

		CopyMemory((LPVOID) &b, map_ptr, sizeof (DWORD));
		map_ptr += sizeof (DWORD);

		if (a == -1)
		{
			// we can make assumptions on a single variable since the other process writes 
			// both values atomically
			i--;
			map_ptr -= sizeof (DWORD) * 2;
			_tprintf(_T("Oh, Oh, am comis-o din nou\n"));
		}


		_tprintf(_T("[================================================]\n"));
		_tprintf(_T("( %d %d )\n"), a, b);
		if (b != 2 * a)
		{
			_tprintf(_T("!!!!!!!!!!Incorrect!!!!!!!!!!\n"));
		}
		_tprintf(_T("[=================================================]\n"));

		ReleaseMutex(hMutex);
	}

	_tprintf(TEXT("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n"));
	HANDLE writeEvent = OpenEvent(NULL, TRUE, TEXT("write_event"));
	HANDLE readEvent = OpenEvent(NULL, TRUE, TEXT("read_event"));

	for (int i = 201; i <= 400; ++i)
	{
		WaitForSingleObject(writeEvent, INFINITE);
		DWORD a, b;

		CopyMemory((LPVOID) &a, map_ptr, sizeof (DWORD));
		map_ptr += sizeof (DWORD);

		CopyMemory((LPVOID) &b, map_ptr, sizeof (DWORD));
		map_ptr += sizeof (DWORD);

		_tprintf(_T("<================================================>\n"));
		_tprintf(_T("( %d %d )\n"), a, b);
		if (b != 2 * a)
		{
			_tprintf(_T("!!!!!!!!!!Incorrect!!!!!!!!!!\n"));
		}
		_tprintf(_T("<=================================================>\n"));

		SetEvent(readEvent);
	}


	CloseHandle(map_file);
	CloseHandle(map_ptr);
	CloseHandle(hMutex);
	CloseHandle(writeEvent);
	CloseHandle(readEvent);

	return 0;
}

