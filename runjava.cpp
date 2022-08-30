#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <string>
#include <filesystem>

using namespace std;
void executeCommand(wstring commandLine);

wstring getExecutablePath() {
	wchar_t* cpath = new wchar_t[2048];
	int exePathSize = GetModuleFileNameW(NULL, cpath, 2048);
	wstring path = wstring(cpath, exePathSize);
	int ind = path.find_last_of('\\');
	return path.substr(0,ind);
}

wstring getExecutableName(wchar_t** argv) {
	wstring cmd(argv[0]);
	int ind = cmd.find_last_of('\\');
	++ind;
	return cmd.substr(ind, cmd.length() - ind - 4);
}

wstring getJarFilePath(wstring exePath, wstring exeName) {
	wstring path = wstring();
	path.append(exePath);
	path.append(L"\\");
	path.append(exeName);
	return path;
}

int wmain(int argc, wchar_t** argv) {
	wstring exeName = getExecutableName(argv);
	wstring exePath = getExecutablePath();
	wstring jarPath = getJarFilePath(exePath, exeName);
	wstring commandLine = wstring();
	commandLine.append(L"java.exe -jar ");
	commandLine.append(jarPath);
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


void executeCommand(wstring commandLine) {
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
