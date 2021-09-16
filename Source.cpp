#include <windows.h>
#include <tlhelp32.h>
#include <chrono>
#include <string>

int main() {
	std::wstring RTXVoiceProcessName = L"NVIDIA RTX Voice.exe";

	while (true) {
		bool wasRTXVoiceProcessFound = false;
		//Time how long it takes to get all our processes
		auto start = std::chrono::high_resolution_clock::now();

		//Get a handle to all processes in the system snapshot.
		HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		//Make sure we got a valid snapshot handle
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

				Sleep(10000);
			}
		}
		//Finish the timing after we've performed the tasks.
		auto end = std::chrono::high_resolution_clock::now();
		auto timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		Sleep(5000);
	}
	return 0;
}
