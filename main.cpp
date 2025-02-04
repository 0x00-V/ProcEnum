#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <wchar.h>


void listAll_proc_and_name(DWORD dwProcId)
{
	HANDLE hProc;
	BOOL bEnumProcessModule = FALSE;
	HMODULE hMod;
	DWORD bytesneeded = 0;
	wchar_t chProcName[MAX_PATH] = L"UNKNOWN";
	wchar_t chProcPath[MAX_PATH] = L"UNKNOWN PTH";
	hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcId);
	if (NULL != hProc)
	{
		bEnumProcessModule = EnumProcessModulesEx(hProc, &hMod, sizeof(hMod), &bytesneeded, LIST_MODULES_ALL);
		if (bEnumProcessModule == TRUE)
		{
			GetModuleBaseName(hProc, hMod, chProcName, sizeof(chProcName)/sizeof(wchar_t));
			GetModuleFileNameEx(hProc, hMod, chProcPath, sizeof(chProcPath) / sizeof(wchar_t));
		}
	}

	std::cout << "\nModuleBaseName - " << chProcName << "\nchProcPath - " << chProcPath << '\n';
	std::cout << "ProcessID - " << dwProcId << '\n';
	CloseHandle(hProc);
}


int main()
{
	DWORD aProcs[2048]{ 0 };
	BOOL bEnumProc = FALSE;
	DWORD bytesneeded{ 0 };
	DWORD TotalProcs{ 0 };

	bEnumProc = EnumProcesses(aProcs, sizeof(aProcs), &bytesneeded);
	if (FALSE == bEnumProc)
	{
		std::cout << "Process Enumeration Failed.\n";
		std::cout << "Error #" << GetLastError << '\n';
	}
	std::cout << "Process Enumeration Successful!\n";

	TotalProcs = bytesneeded / sizeof(DWORD);

	

	for (size_t i{ 0 }; i < TotalProcs; i++)
	{
		listAll_proc_and_name(aProcs[i]);
	}
	std::cout << "\nTotal Process Count: " << TotalProcs << " Processes \n";
	system("PAUSE");
	return 0;


}