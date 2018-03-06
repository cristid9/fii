#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <aclapi.h>
#include <lm.h>

using namespace std;

#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "netapi32.lib")

bool is_user_admin()
{
	bool result;
	DWORD rc;
	wchar_t user_name[256];
	USER_INFO_1 *info;
	DWORD size = sizeof(user_name);

	GetUserNameW(user_name, &size);

	rc = NetUserGetInfo(NULL, user_name, 1, (byte **) &info);
	if (rc != NERR_Success)
		return false;

	result = info->usri1_priv == USER_PRIV_ADMIN;

	NetApiBufferFree(info);
	return result;
}

int main()
{
	DWORD dwRes, dwDisposition;
	PSID pOwnersSid = NULL, pEveryoneSid = NULL;
	PACL pACL = NULL;
	PSECURITY_DESCRIPTOR pSD = NULL;
	EXPLICIT_ACCESS ea[2];
	SID_IDENTIFIER_AUTHORITY SIDAuthWorld =
		SECURITY_WORLD_SID_AUTHORITY;
	SID_IDENTIFIER_AUTHORITY SIDAuthNT = SECURITY_NT_AUTHORITY;
	SECURITY_ATTRIBUTES sa;
	LONG lRes;
	HKEY hkSub = NULL;
	
	if (!AllocateAndInitializeSid(&SIDAuthNT, 2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&pOwnersSid))
	{
		_tprintf(_T("AllocateAndInitializeSid Error %u\n"), GetLastError());
	}

	DWORD SidSize;
	
	if (!is_user_admin())
	{
		_tprintf(L"Not admin\n");
		if (!CreateWellKnownSid(WinCreatorOwnerSid, NULL, pOwnersSid, &SidSize))
		{
			fprintf(stderr,
				"CreateWellKnownSid Error %u",
				GetLastError());
		}
	}

	ZeroMemory(&ea, 2 * sizeof(EXPLICIT_ACCESS));
	ea[0].grfAccessPermissions = KEY_READ | KEY_WRITE;
	ea[0].grfAccessMode = SET_ACCESS;
	ea[0].grfInheritance = NO_INHERITANCE;
	ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
	ea[0].Trustee.ptstrName = (LPTSTR) pOwnersSid;
	
	if (!AllocateAndInitializeSid(&SIDAuthNT, 2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&pEveryoneSid))
	{
		_tprintf(_T("AllocateAndInitializeSid Error %u\n"), GetLastError());
	}

	DWORD SidSize2;
	if (!CreateWellKnownSid(WinWorldSid, NULL, pEveryoneSid, &SidSize2))
	{
		fprintf(stderr,
			"CreateWellKnownSidss Error %u",
			GetLastError());
	}

	ea[1].grfAccessPermissions = KEY_READ;
	ea[1].grfAccessMode = SET_ACCESS;
	ea[1].grfInheritance = NO_INHERITANCE;
	ea[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea[1].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
	ea[1].Trustee.ptstrName = (LPTSTR) pEveryoneSid;
	
	dwRes = SetEntriesInAcl(2, ea, NULL, &pACL);
	if (ERROR_SUCCESS != dwRes)
	{
		_tprintf(_T("SetEntriesInAcl Error %u\n"), GetLastError());
	}

	pSD = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR,
		SECURITY_DESCRIPTOR_MIN_LENGTH);
	if (NULL == pSD)
	{
		_tprintf(_T("LocalAlloc Error %u\n"), GetLastError());
	}

	if (!InitializeSecurityDescriptor(pSD,
		SECURITY_DESCRIPTOR_REVISION))
	{
		_tprintf(_T("InitializeSecurityDescriptor Error %u\n"),
			GetLastError());
	}

	if (!SetSecurityDescriptorDacl(pSD,
		TRUE,
		pACL,
		FALSE))
	{
		_tprintf(_T("SetSecurityDescriptorDacl Error %u\n"),
			GetLastError());
	}

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = pSD;
	sa.bInheritHandle = FALSE;

	HKEY hkey;
	DWORD disp;

	LONG result = RegCreateKeyEx(
		HKEY_CURRENT_USER,
		L"Software\\123",
		0,
		0,
		REG_OPTION_NON_VOLATILE,
		KEY_WRITE,
		&sa,
		&hkey,
		&disp
	);

	if (result == ERROR_SUCCESS)
	{
		cout << "key created" << endl;

		/*
		dwRes = SetEntriesInAcl(1, ea, NULL, &pACL);
		if (ERROR_SUCCESS != dwRes)
		{
			_tprintf(_T("The rest of changes %u\n"), GetLastError());
		}
		*/
	}
	else
	{
		cout << "erorr " << endl;
	}
	
	return 0;
}


