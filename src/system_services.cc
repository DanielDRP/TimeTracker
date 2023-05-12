#include <Windows.h>
#include <psapi.h>


std::string getActiveWindow() {
  HWND foreground = GetForegroundWindow();
  if (foreground) {
    char windowTitle[256];
    GetWindowTextA(foreground, windowTitle, sizeof(windowTitle));
    return std::string(windowTitle);
  }

  return "";
}



std::string getActiveProgram() {
  TCHAR buffer[MAX_PATH] = {0};
  DWORD dwProcId = 0;
  GetWindowThreadProcessId(GetForegroundWindow(), &dwProcId);
  HANDLE hProc =
      OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcId);

  if (hProc) {
    HMODULE hMods[1024];
    DWORD cbNeeded;

    if (EnumProcessModules(hProc, hMods, sizeof(hMods), &cbNeeded)) {
      if (GetModuleFileNameEx(hProc, hMods[0], buffer, MAX_PATH)) {
        std::string programName(buffer);
        CloseHandle(hProc);
        programName =
            programName.substr(programName.find_last_of("\\") + 1);
        return programName;
      }
    }
    CloseHandle(hProc);
  }

  return "";
}