#include "stdafx.h"
#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	// allocate memory for the point b) as well
	DWORD memSize = 800 * sizeof(DWORD); 
	HANDLE map_file = CreateFileMapping(NULL, NULL, PAGE_READWRITE, 0, memSize, TEXT("mem1"));

	if (map_file == NULL)
	{
		_tprintf(_T("(Parent) File mapping is null\n"));
		return 1;
	}

	char* map_ptr = (char *) MapViewOfFile(map_file, FILE_MAP_WRITE, 0, 0, 0);
	if (map_ptr == NULL)
	{
		_tprintf(_T("(Parent) PTR is null \n"));
	}

	_tprintf(_T("Initializing the memory"));

	for (int i = 0; i <= 200; ++i)
	{
		DWORD placeholder = -1;
		CopyMemory((LPVOID)map_ptr, &placeholder, sizeof(DWORD));
		map_ptr += sizeof(DWORD);

		CopyMemory((LPVOID)map_ptr, &placeholder, sizeof(DWORD));
		map_ptr += sizeof(DWORD);
	}

	map_ptr -= sizeof(DWORD) * 402; // reset the pointer

	HANDLE hMutex = CreateMutex(NULL, FALSE, _T("mt"));
	LPTSTR szCmdline = _tcsdup(TEXT("C:\\Users\\cristi\\source\\repos\\process_synchronization_reader\\Debug\\process_synchronization_reader.exe"));
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(NULL, szCmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		_tprintf(_T("Process created\n"));
	}

	_tprintf(_T("pare ca s-a creat"));
	for (int i = 1; i <= 200; ++i)
	{
		WaitForSingleObject(hMutex, INFINITE);
		
		_tprintf(_T("(Parent %d) writing from the parent\n"), i);
		DWORD a = i, b = 2 * i;
		
		CopyMemory((LPVOID) map_ptr, &a, sizeof(DWORD));
		map_ptr += sizeof (DWORD);
	
		CopyMemory((LPVOID) map_ptr, &b, sizeof(DWORD));
		map_ptr += sizeof (DWORD);
		
		ReleaseMutex(hMutex);
	 }

	CloseHandle(hMutex);

	// Now do the same thing using events
	HANDLE writeEvent = CreateEvent(NULL, TRUE, TRUE, TEXT("write_event"));
	HANDLE readEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("read_event"));

	for (int i = 201; i <= 400; ++i)
	{
		WaitForSingleObject(writeEvent, INFINITE);

		DWORD a = i, b = 2 * i;
		
		CopyMemory((LPVOID)map_ptr, &a, sizeof(DWORD));
		map_ptr += sizeof (DWORD);
	
		CopyMemory((LPVOID) map_ptr, &b, sizeof(DWORD));
		map_ptr += sizeof(DWORD);

		SetEvent(readEvent);
	}


	int n;
	cin >> n;

	CloseHandle(hMutex);
	CloseHandle(writeEvent);
	CloseHandle(readEvent);
	CloseHandle(map_ptr);
	CloseHandle(map_file);

	return 0;
}
