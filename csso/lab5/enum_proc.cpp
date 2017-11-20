#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <cstring>
#include <TlHelp32.h>
#include <cstdlib>
#include <vector>

using std::vector;
using std::cin;

#define ERROR 1000

struct Entry
{
	DWORD pid;
	DWORD ppid;
	WCHAR procName[261];
};

int main()
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
	vector<Entry> entries;
	
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot failed.err = %d \n", GetLastError());
		return (-1);
	}
	
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcessSnap, &pe32))
	{
		printf("Process32First failed. err = %d \n", GetLastError());
		CloseHandle(hProcessSnap); 
		return -1;
	}

	int i = 0;
	do
	{
		Entry e;
		e.pid = pe32.th32ProcessID;
		e.ppid = pe32.th32ParentProcessID;
		wcscpy_s(e.procName, pe32.szExeFile);
		entries.push_back(e);
	} while (Process32Next(hProcessSnap, &pe32)); 

	DWORD memSize = 2 * (entries.size() * sizeof(DWORD)) + (entries.size() * 261 * sizeof(WCHAR)) + ERROR;
	//_tprintf(_T("==>%d<==\n"), memSize);
	//_tprintf(_T("%d\n"), entries.size());
	HANDLE map_file = CreateFileMapping(NULL, NULL, PAGE_READWRITE, 0, memSize, TEXT("mem"));

	if (map_file == NULL)
	{
		_tprintf(_T("File mapping is null\n"));
		return 1;
	}

	char* map_ptr = (char *) MapViewOfFile(map_file, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0);

	if (map_ptr == NULL)
	{
		_tprintf(_T("PTR is null \n"));
	}
	

	DWORD entriesSize = entries.size();
	CopyMemory((LPVOID) map_ptr, &entriesSize, sizeof(DWORD));
	map_ptr += sizeof(DWORD);

	for (int i = 0; i < entries.size(); ++i)
	{
		CopyMemory((LPVOID) map_ptr, &entries[i].pid, sizeof(DWORD));
		map_ptr += sizeof(DWORD);
	
		CopyMemory((LPVOID) map_ptr, &entries[i].ppid, sizeof(DWORD));
		map_ptr += sizeof(DWORD);
	
		CopyMemory((LPVOID) map_ptr, entries[i].procName, 261 * sizeof(WCHAR));
		map_ptr += (261 * sizeof(WCHAR));
	}
	
	cin.get();

	CloseHandle(hProcessSnap);
	UnmapViewOfFile(map_ptr);
	CloseHandle(map_file);

	return 0;
}


