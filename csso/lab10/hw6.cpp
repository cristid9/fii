nclude "stdafx.h"
#include <thread>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <Wininet.h>
#include <map>
#include <mutex>
#include <set>
#include <regex>
#include <codecvt>

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "advapi32.lib") 


using namespace std;


HANDLE map_file;
char* map_ptr;



#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

map<wstring, int> sites_info;
mutex sites_mutex;
mutex signal_new_file_mutex;
bool signal_new_file = false;

vector<wstring> QueryKey(HKEY hKey)
{
	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
	DWORD    cbName;                   // size of name string 
	TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
	DWORD    cchClassName = MAX_PATH;  // size of class string 
	DWORD    cSubKeys = 0;               // number of subkeys 
	DWORD    cbMaxSubKey;              // longest subkey size 
	DWORD    cchMaxClass;              // longest class string 
	DWORD    cValues;              // number of values for key 
	DWORD    cchMaxValue;          // longest value name 
	DWORD    cbMaxValueData;       // longest value data 
	DWORD    cbSecurityDescriptor; // size of security descriptor 
	FILETIME ftLastWriteTime;      // last write time 

	DWORD i, retCode;

	TCHAR  achValue[MAX_VALUE_NAME];
	DWORD cchValue = MAX_VALUE_NAME;

	// Get the class name and the value count. 
	retCode = RegQueryInfoKey(
		hKey,                    // key handle 
		achClass,                // buffer for class name 
		&cchClassName,           // size of class string 
		NULL,                    // reserved 
		&cSubKeys,               // number of subkeys 
		&cbMaxSubKey,            // longest subkey size 
		&cchMaxClass,            // longest class string 
		&cValues,                // number of values for this key 
		&cchMaxValue,            // longest value name 
		&cbMaxValueData,         // longest value data 
		&cbSecurityDescriptor,   // security descriptor 
		&ftLastWriteTime);       // last write time 

								 // Enumerate the subkeys, until RegEnumKeyEx fails.

	vector<wstring> keys;
	if (cSubKeys)
	{
		printf("\nNumber of subkeys: %d\n", cSubKeys);

		for (i = 0; i<cSubKeys; i++)
		{
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hKey, i,
				achKey,
				&cbName,
				NULL,
				NULL,
				NULL,
				&ftLastWriteTime);
			if (retCode == ERROR_SUCCESS)
			{
			}
		}
	}

	// Enumerate the key values. 

	if (cValues)
	{
		for (i = 0, retCode = ERROR_SUCCESS; i<cValues; i++)
		{
			cchValue = MAX_VALUE_NAME;
			achValue[0] = '\0';
			retCode = RegEnumValue(hKey, i,
				achValue,
				&cchValue,
				NULL,
				NULL,
				NULL,
				NULL);

			if (retCode == ERROR_SUCCESS)
			{
				keys.push_back(wstring(achValue));
			}
		}
	}

	return keys;
}

std::wstring convert(const std::string& input)
{
	try
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(input);
	}
	catch (std::range_error& e)
	{
		size_t length = input.length();
		std::wstring result;
		result.reserve(length);
		for (size_t i = 0; i < length; i++)
		{
			result.push_back(input[i] & 0xFF);
		}
		return result;
	}
}

std::set<wstring> extract_hyperlinks(std::string text)
{
	static const std::regex hl_regex("<a href=\"(.*?)\">", std::regex_constants::icase);

	set<string> tmp = { std::sregex_token_iterator(text.begin(), text.end(), hl_regex, 1),
		std::sregex_token_iterator{} };

	set<wstring> retval;
	set<string>::iterator it;
	for (it = tmp.begin(); it != tmp.end(); ++it)
	{
		cout << *it << endl;
		retval.insert(convert(*it));
	}


	return retval;
}

void walk_site(vector<wstring> sites)
{
	for (int i = 0; i < sites.size(); ++i)
	{
	
		vector<wstring> other_sites;

		HINTERNET hInternet, hFile;
		char buf[1024];
		DWORD bytes_read;
		int finished = 0;
		hInternet = InternetOpen(L"", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
		if (hInternet == NULL) {
			cout << GetLastError() << endl;
			printf("InternetOpen failed\n");
		}
		hFile = InternetOpenUrl(hInternet, &sites[i][0], NULL, 0L, 0, 0);
		if (hFile == NULL) {
			cout << GetLastError() << endl;
			printf("InternetOpenUrl failed\n");
		}
		int total_bytes = 0;
		while (!finished) {
			if (InternetReadFile(hFile, buf, sizeof(buf), &bytes_read)) {
				if (bytes_read > 0) {
					total_bytes += bytes_read;
					// printf("%.*s", bytes_read, buf);
				}
				else {
					finished = 1;
				}
			}
			else {
				printf("InternetReadFile failed\n");
				finished = 1;
			}
			set<wstring> links = extract_hyperlinks(string(buf));
			set<wstring>::iterator it;
			for (it = links.begin(); it != links.end(); ++it) {
				wcout << *it << endl;
				other_sites.push_back(*it);
			}
		}

		sites_mutex.lock();
		sites_info[sites[i]] = total_bytes;
		sites_mutex.unlock();

		signal_new_file_mutex.lock();
		signal_new_file = false;
		signal_new_file_mutex.unlock();

		InternetCloseHandle(hInternet);
		InternetCloseHandle(hFile);

		walk_site(other_sites);

	}
}

void thread1()
{
	while (true)
	{
		Sleep(10000);
		HKEY hTestKey;
		vector<wstring> sites;
		if (RegOpenKeyEx(HKEY_CURRENT_USER,
			TEXT("WebCrawler"),
			0,
			KEY_READ,
			&hTestKey) == ERROR_SUCCESS
			)
		{
			 sites = QueryKey(hTestKey);
			for (int i = 0; i < sites.size(); ++i)
			{
				wcout << sites[i] << endl;
			}
		}
		else
		{
			cout << GetLastError() << endl;
		}

		RegCloseKey(hTestKey);

		// traverse the site lists
		walk_site(sites);
	}

}

void thread2()
{
	HANDLE writeEvent = CreateEvent(NULL, TRUE, TRUE, TEXT("write_event"));
	HANDLE readEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("read_event"));

	signal_new_file_mutex.lock();
	while (true)
	{

		if (signal_new_file)
		{
		
			WaitForSingleObject(writeEvent, INFINITE);

			// here write to the memory mapped file

			wstring site_name = (--sites_info.end())->first;
			DWORD site_dim = (--sites_info.end())->second;

			CopyMemory((LPVOID)map_ptr, &site_dim, sizeof(DWORD));
			map_ptr += sizeof(DWORD);

			CopyMemory((LPVOID)map_ptr, site_name.c_str(), sizeof(CHAR));
			map_ptr += site_name.size();

			CopyMemory((LPVOID)map_ptr, &site_dim, sizeof(DWORD));
			map_ptr += sizeof(DWORD);
		}
	}
	signal_new_file_mutex.unlock();

	CloseHandle(writeEvent);
	CloseHandle(readEvent);
}

int main()
{

	map_file = CreateFileMapping(NULL, NULL, PAGE_READWRITE, 0, 10000, TEXT("mem"));

	if (map_file == NULL)
	{
		_tprintf(_T("File mapping is null\n"));
		return 0;
	}

	map_ptr = (char *)MapViewOfFile(map_file, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0);

	if (map_ptr == NULL)
	{
		_tprintf(_T("PTR is null \n"));
	}


	// main starting point
	std::thread t1(thread1);
	std::thread t2(thread2);
	
	t1.join();
	t2.join();


	return 0;
}


