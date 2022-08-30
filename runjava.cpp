#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <string>

using namespace std;
void executeCommand(wstring& commandLine);

int wmain(int argc, wchar_t** argv) {
	wchar_t* cpath = new wchar_t[1024];
	int exePathSize = GetModuleFileNameW(NULL, cpath, 1024);
	wstring path = wstring(cpath, exePathSize);
	int ind = path.find_last_of('\\');
	wstring jarDir = path.substr(0, ind);
	wstring cmd(argv[0]);
	wstring commandLine;
	ind = cmd.find_last_of('\\');
	++ind;
	wstring name = cmd.substr(ind, cmd.length() - ind - 4);
	commandLine.append(L"java.exe -jar ");
	commandLine.append(jarDir);
	commandLine.append(L"\\");
	commandLine.append(name);
	commandLine.append(L".jar ");
	for (int i = 1; i < argc; ++i) {
		commandLine.append(L"\"");
		commandLine.append(argv[i]);
		commandLine.append(L"\"");
		commandLine.append(L" ");
	}
	wcout << commandLine << endl;
	executeCommand(commandLine);
}

void executeCommand(wstring& commandLine) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if (!CreateProcess(NULL,
		(LPWSTR)commandLine.c_str(),
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		) {
		cout << "CreateProcess failed, error code " << GetLastError() << "\n";
		return;
	}

	// Wait until child process exit.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
