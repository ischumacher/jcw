#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <string>

using namespace std;

void executeCommand(wstring &commandLine);

int wmain(int argc, wchar_t **argv) {
	wstring cmd(argv[0]);
	wstring commandLine;
	int ind = cmd.find_last_of('\\');
	wstring path = cmd.substr(0, ind);
	++ind;
	wstring name = cmd.substr(ind, cmd.length() - ind - 4);
	commandLine.append(L"java.exe -jar ");
	commandLine.append(path);
	commandLine.append(L"\\");
	commandLine.append(name);
	commandLine.append(L".jar ");
	for (int i = 1; i < argc; ++i) {
		commandLine.append(argv[i]);
		commandLine.append(L" ");
	}
	executeCommand(commandLine);
}

void executeCommand(wstring &commandLine) {
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
