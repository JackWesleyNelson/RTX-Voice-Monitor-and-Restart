#include <windows.h>
#include <tlhelp32.h>
#include <string>

int main() {
	std::wstring RTXVoiceProcessName = L"NVIDIA RTX Voice.exe";

	while (true) {
		bool wasRTXVoiceProcessFound = false;
		HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (snapshotHandle != INVALID_HANDLE_VALUE) {
			PROCESSENTRY32 processEntry = {};
			processEntry.dwSize = sizeof(PROCESSENTRY32);
			if (Process32First(snapshotHandle, &processEntry)) {
				wasRTXVoiceProcessFound = (!RTXVoiceProcessName.compare(processEntry.szExeFile));
			}
			while (!wasRTXVoiceProcessFound && Process32Next(snapshotHandle, &processEntry)) {
				wasRTXVoiceProcessFound = (!RTXVoiceProcessName.compare(processEntry.szExeFile));
			}
			if (!wasRTXVoiceProcessFound) {
				ShellExecute(NULL,
					L"open",
					L"C:/Program Files/NVIDIA Corporation/NVIDIA RTX Voice/NVIDIA RTX Voice.exe",
					NULL,
					L"C:/Program Files/NVIDIA Corporation/NVIDIA RTX Voice/",
					SW_MINIMIZE);
			}
		}
		Sleep(5000);
	}
	return 0;
}
