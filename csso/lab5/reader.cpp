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
#include <Wdbgexts.h>

using std::vector;

struct Entry
{
	DWORD pid;
	DWORD ppid;
	WCHAR procName[261];
};

struct Node
{
	DWORD pid;
	DWORD ppid;
	WCHAR procName[261];
	vector<Node*> children;
};

class ProcTree
{
private:
	Node *root;

	bool internalHasRootOf(DWORD ppid, Node* node)
	{
		if (node->pid == ppid)
			return true;

		bool has = false;
		for (int i = 0; i < node->children.size(); ++i)
		{
			has = has || internalHasRootOf(ppid, node->children[i]);
		}

		return has;
	}

	void internalInsertChild(DWORD ppid, DWORD pid, WCHAR* procName, Node* node)
	{
		if (node->pid == ppid)
		{
			Node *newNode = new Node();
			newNode->pid = pid;
			newNode->ppid = ppid;
			wcscpy_s(newNode->procName, procName);
			node->children.push_back(newNode);
		}

		for (int i = 0; i < node->children.size(); ++i)
		{
			internalInsertChild(ppid, pid, procName, node->children[i]);
		}
	}

	void internalDumpTreeContent(Node *node, int padTabs)
	{
		for (int i = 0; i < padTabs; ++i)
		{
			_tprintf(_T("    "));
		}
		_tprintf(_T("<%d><%d><%s>\n"), node->pid, node->ppid, node->procName); 

		for (int i = 0; i < node->children.size(); ++i)
		{
			internalDumpTreeContent(node->children[i], padTabs + 1);
		}
	}

	void internalKill(Node *node)
	{
		for (int i = 0; i < node->children.size(); ++i)
		{
			internalKill(node->children[i]);
		}

		HANDLE handy = OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, TRUE, node->pid);
		TerminateProcess(handy, 0);
	}

public:
	ProcTree(DWORD pid, WCHAR* procName)
	{
		root = new Node();
		root->pid = pid;
		root->ppid = -1;
		wcscpy_s(root->procName, procName);
	}

	DWORD getRootPid() 
	{
		return root->pid;
	}

	bool hasRootOf(DWORD ppid)
	{	
		return internalHasRootOf(ppid, root);
	}

	void insert(DWORD pid, DWORD ppid, WCHAR *procName)
	{
		internalInsertChild(ppid, pid, procName, root);
	}

	void dumpTree(int i)
	{
		_tprintf(_T("Tree number: %d\n"), i);
		internalDumpTreeContent(root, 0);
	}
	
	void kill()
	{
		internalKill(root);
	}
};

int main()
{
	HANDLE ph;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &ph);

	LUID luid;

	TOKEN_PRIVILEGES tp;

	if (LookupPrivilegeValueW(NULL, SE_DEBUG_NAME, &luid))
	{

		tp.PrivilegeCount = 1;
		tp.Privileges[0].Luid = luid;

		AdjustTokenPrivileges(
			ph,
			false,
			&tp,
			sizeof(tp),
			(PTOKEN_PRIVILEGES) NULL,
			(PDWORD) NULL
		);
	}


	HANDLE map_file = OpenFileMapping(FILE_MAP_READ, false, TEXT("mem"));

	if (map_file == NULL)
	{
		_tprintf(_T("File mapping is null\n"));
		return 1;
	}

	char* map_ptr = (char *) MapViewOfFile(map_file, FILE_MAP_READ, 0, 0, 0);

	if (map_ptr == NULL)
	{
		_tprintf(_T("PTR is null \n"));
	}
	
	vector<Entry> entries;

	DWORD sz;
	DWORD actualRead;

	CopyMemory((LPVOID)&sz, map_ptr, sizeof(DWORD));
	map_ptr += sizeof(DWORD);

	for (int i = 0; i < sz; ++i)
	{
		Entry tmp;
		
		CopyMemory((LPVOID) &tmp.pid, map_ptr, sizeof(DWORD));
		map_ptr += sizeof(DWORD);

		CopyMemory((LPVOID) &tmp.ppid, map_ptr, sizeof(DWORD));
		map_ptr += sizeof(DWORD);

		CopyMemory((LPVOID) tmp.procName, map_ptr, sizeof(WCHAR) * 261);
		map_ptr += sizeof(WCHAR) * 261;

		if (tmp.pid == 0)
		{
			continue;
		}
		entries.push_back(tmp);
	}

	sz -= 1;

	// filter root nodes
	vector<ProcTree*> procTrees;
	vector<DWORD> roots;

	for (int i = 0; i < sz; ++i)
	{		
		//_tprintf(_T("%d %d %s\n"), entries[i].pid, entries[i].ppid, entries[i].procName);
		bool foundRoot = true;
		for (int j = 0; j < sz; ++j)
		{
			if (i == j)
			{
				continue;
			}
			
			if (entries[i].ppid == entries[j].pid)
			{
				foundRoot = false;
				break;
			}
		}
	
		if (foundRoot)
		{
			procTrees.push_back(new ProcTree(entries[i].pid, entries[i].procName));
			roots.push_back(entries[i].pid);
			_tprintf(_T("Aici\n"));
		}
	}

	
	// distribute each process in it's corresponding tree process
	int allDistributed = sz - procTrees.size();

	while (allDistributed > 0)
	{
		for (int i = 0; i < sz; ++i)
		{
			// check if root
			for (int j = 0; j < procTrees.size(); ++j)
			{
				if (procTrees[j]->getRootPid() == entries[i].pid)
					// root found
					break;

				if (procTrees[j]->hasRootOf(entries[i].ppid))
				{
					procTrees[j]->insert(entries[i].pid, entries[i].ppid, entries[i].procName);
					allDistributed--;
					_tprintf(_T("Looks like it works %d\n"), i);
				}
			}
		}
	}
	
	for (int i = 0; i < procTrees.size(); ++i)
	{
		procTrees[i]->dumpTree(i + 1);
	}

	int n;

	std::cin >> n;

	procTrees[n - 1]->kill();

	return 0;
}


