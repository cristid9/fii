#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <strsafe.h>
#include <iostream>

using namespace std;

void traverseDir(LPTSTR lpFolder, LPTSTR lpBranch)
{
	WCHAR fullPath[MAX_PATH];
	wcscpy_s(fullPath, lpFolder);
	
	if (wcscmp(lpBranch, L"") != 0)
	{
		wcscat_s(fullPath, L"\\");
	}
	wcscat_s(fullPath, (LPCWSTR)lpBranch);
	wcscat_s(fullPath, L"\\\*");

	WCHAR key[MAX_PATH];
	wcscpy_s(key, L"Software\\CSSO\\");
	wcscat_s(key, (LPCWSTR)lpBranch);

	HKEY hkey;
	DWORD disp;

	LONG result = RegCreateKeyEx(
		HKEY_CURRENT_USER,
		key,
		0,
		0,
		REG_OPTION_NON_VOLATILE,
		KEY_WRITE,
		0,
		&hkey,
		&disp
	);

	_tprintf(_T("%s\n"), fullPath);

	WIN32_FIND_DATA ffd;
	HANDLE h = FindFirstFile(fullPath, &ffd);

	if (h == INVALID_HANDLE_VALUE) 
	{
		_tprintf(L"An error has occured while trying to open one of the provided files");
		return;
	}

	do
	{
		if (wcscmp(ffd.cFileName, _T(".")) ==  0 || wcscmp(ffd.cFileName, _T("..")) == 0)
		{
			continue;
		}

		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			_tprintf(_T("[dir]%s\n"), ffd.cFileName);
		
			WCHAR passFullPath[MAX_PATH];
			wcscpy_s(passFullPath, lpBranch);
			wcscat_s(passFullPath, L"\\");
			wcscat_s(passFullPath, ffd.cFileName);
		
			traverseDir(lpFolder, passFullPath);
		}
		else
		{
			_tprintf(_T("%s\n"), ffd.cFileName);
			
			LONG status;
			HKEY hKey;

			status = RegOpenKeyEx(HKEY_CURRENT_USER, key, 0, KEY_ALL_ACCESS, &hKey);
			if ((status == ERROR_SUCCESS) && (hKey != NULL))
			{

				_tprintf(L"%d", ffd.nFileSizeLow);
				DWORD size = ffd.nFileSizeLow;

				status = RegSetValueEx(hKey, ffd.cFileName, 0, REG_DWORD, (BYTE*)&size, sizeof(ffd.nFileSizeLow));
				RegCloseKey(hKey);
			}
			else
			{
				cout << "An error has occured while trying to set a registry value" << endl;
			}

		}
	} while (FindNextFile(h, &ffd));
	
	CloseHandle(h);
}

int _tmain(int argc, TCHAR *argv[])
{
	traverseDir(_T("C:\\"), _T("tema1"));
	return 0;
}

