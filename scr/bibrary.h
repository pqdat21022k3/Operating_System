#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <direct.h>
#include <errno.h>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

PROCESS_INFORMATION pi[100]; //

/* WHAT IS PROCESS_INFORMATION
typedef struct _PROCESS_INFORMATION { // pi 
    HANDLE hProcess; 
    HANDLE hThread; 
    DWORD dwProcessId; 
    DWORD dwThreadId; 
} PROCESS_INFORMATION; 
 
Members
hProcess
Returns a handle to the newly created process. The handle is used to specify the process in all functions that perform operations on the process object.
hThread
Returns a handle to the primary thread of the newly created process. The handle is used to specify the thread in all functions that perform operations on the thread object.
dwProcessId
Returns a global process identifier that can be used to identify a process. The value is valid from the time the process is created until the time the process is terminated.
dwThreadId
Returns a global thread identifiers that can be used to identify a thread. The value is valid from the time the thread is created until the time the thread is terminated.
QuickInfo
*/

STARTUPINFO si[100];
/*
The STARTUPINFO structure is used with the CreateProcess function to specify main window properties if a new window is created for the new process.
typedef struct _STARTUPINFO { // si 
    DWORD   cb; // unsigned int cb 
    LPTSTR  lpReserved; 
    LPTSTR  lpDesktop; 
    LPTSTR  lpTitle; 
    DWORD   dwX; 
    DWORD   dwY; 
    DWORD   dwXSize; 
    DWORD   dwYSize; 
    DWORD   dwXCountChars; 
    DWORD   dwYCountChars; 
    DWORD   dwFillAttribute; 
    DWORD   dwFlags; 
    WORD    wShowWindow; 
    WORD    cbReserved2; 
    LPBYTE  lpReserved2; 
    HANDLE  hStdInput; 
    HANDLE  hStdOutput; 
    HANDLE  hStdError; 
} STARTUPINFO, *LPSTARTUPINFO; 
*/
LPSTR cString[100]; //far char * cString[100], trỏ để chỉ để đường dẫn path vào một thư mục 
HANDLE hHandless[100];
int status[100];
int n = 0;

void print(const string &s)
{
    cout << s;
}

void help(){
    // Display all commands

	printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
	cout << "For more information on a specific command, type help command-name\n";
    cout.width(20);
    cout << left << "1.  help"
         << "Provide Help information for Windows commands\n";
    cout.width(20);
    cout << left << "2.  cd .."
         << "Change to the parrent directory of the current directory\n";
    cout.width(20);
    cout << left << "3.  cd 'path'"
         << "Change current directory to this path\n";
    cout.width(20);
    cout << left << "4.  dir"
         << "Display list of files in parent directory\n";
    cout.width(20);
    cout << left << "5.  date"
         << "Display date\n";
    cout.width(20);
    cout << left << "6.  time"
         << "Display time\n";
    cout.width(20);
    cout << left << "7.  clock"
         << "Display clock\n";
    cout.width(20);
    cout << left << "8.  countdown"
         << "Display countdown clock, add fore or back mode, example: countdown fore, countdown back\n";
    cout.width(20);
    cout << left << "9.  notepad"
         << "Open system notepad, add fore or back mode, example: notepad fore, notepad back\n";
    cout.width(20);
    cout << left << "10. stop 'ID'"
         << "Stop a running process\n";
    cout.width(20);
    cout << left << "11. resume 'ID'"
         << "Resume a stopping process\n";
    cout.width(20);
    cout << left << "12. kill 'ID'"
         << "Kill a running process\n";
    cout.width(20);
    cout << left << "13. kill -1"
         << "Kill all running processes\n";
    cout.width(20);
    cout << left << "14. list"
         << "Display list of processes\n";
    cout.width(20);
    cout << left << "15. [*.bat]"
         << "Read *.bat file and run list of command lines\n";
	cout.width(20);
    cout << left << "16. path of *.exe"
         << "Run *.exe file, add fore or back mode\n";
    cout.width(20);
    cout << left << "17. env a"
    	 << "Display the value of the environment variable a. Ex: env path\n";
    cout.width(20);
    cout << left << "" << "If a = null, display all the environment variables and their values\n";
    cout.width(20);
    cout << left << "18. addenv (a) b"
    	 << "Add the environment variable a with its name b\n";
    cout.width(20);
    cout << left << "19. delenv a"
    	 << "Delete the environment variable a\n";
    cout.width(20);
    cout << left << "20. history"
    	 << "Print all used commands\n";
    cout.width(20);
    cout << left << "21. clean"
    	 << "Clean the history\n";
    cout.width(20);
    cout << left << "22. clear"
         << "Clear tiny shell\n";
    cout.width(20);
    cout << left << "23. exit"
         << "Exit process\n";
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void kill(string s){
    //Có id của tiến trình đấy -> kill bằng id
    int id = atoi(s.c_str()); 

    int a = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (pi[i].dwProcessId == id)
        {
            TerminateProcess(pi[i].hProcess, 0);
            CloseHandle(pi[i].hThread);
            CloseHandle(pi[i].hProcess);
            // cout << pi[i].hProcess << endl;
            printf("Process %s killed\n", cString[i]);
            for (int j = i; j < n; ++j)
            // Thay thế cái bị hủy bằng cái kế tiếp thứ tự dần dần
            {
                status[j] = status[j + 1];
                pi[j] = pi[j + 1];
                si[j] = si[j + 1];
                cString[j] = cString[j + 1];
            }
            n--;
            a = 0;
            break;
        }
    }
    if (a)
    {
        printf("Can't find process with this id = %d\n", id);
    }
}

void kill_All(){
    for (int i = 1; i <= n; ++i)
    {
        TerminateProcess(pi[i].hProcess, 0);
        CloseHandle(pi[i].hThread);
        CloseHandle(pi[i].hProcess);

        // cout << pi[i].hProcess << endl;
    }
    printf("All process killed ...\n");
    n = 0;
}

void stop(string s)
{
    int id = atoi(s.c_str());
    int a = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (pi[i].dwProcessId == id)
        {
            a = 0;
            if (status[i] == 1)
            {
                status[i] = 0;
                cout << "Stop " << cString[i] << " success\n";
                SuspendThread(pi[i].hThread);
                break;
            }
            else
            {
                cout << "Process " << cString[i] << " is still stopping" << endl;
                break;
            }
        }
    }
    if (a)
    {
        printf("Can't find process with this id = %d\n", id);
    }
}
void resume(string s)
{
    int id = atoi(s.c_str());
    int a = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (pi[i].dwProcessId == id)
        {
            a = 0;
            if (status[i] == 0)
            {
                status[i] = 1;
                cout << "Process " << cString[i] << " is running again\n";
                ResumeThread(pi[i].hThread);
                break;
            }
            else
            {
                cout << "Process " << cString[i] << " is still running" << endl;
                break;
            }
        }
    }
    if (a)
    {
        printf("Can't find process with this id = %d\n", id);
    }
}

void openInBackOrFore(const string &command, const string &s)
//Hàm này để xem là muốn chạy back hay chạy fore
{
    void openProcessInForeGround(const string &s);
    void openProcessInBackGround(const string &s);
    stringstream cc(command);
    //// Used for breaking words, tách cái xâu nhập vào thành các từ cách nhau bằng dấu cách
//    cout << s << endl;
//notepad fore => c1=notepad, c2=fore
    string c1, c2;
    cc >> c1;
    cc >> c2;
    if (c2.compare("back") == 0)
    {
        openProcessInBackGround(s);
    }
    else if (c2.compare("fore") == 0)
    {
        openProcessInForeGround(s);
    }
    else
    {
        printf("Illegal command! Add backgound or foreground mode!\n");
    }
}

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
    case CTRL_C_EVENT:
        kill_All();
        printf("dssdcsv");
        return TRUE;
    default:
        return FALSE;
    }
}

void openProcessInForeGround(const string &s)
{

    PROCESS_INFORMATION pi;                 // lpStartupInfo    // lpProcessInformation
    STARTUPINFO si = {sizeof(STARTUPINFO)}; // cpp string must be modified to use in c

    LPSTR cString = strdup(s.c_str()); //

    ZeroMemory(&si, sizeof(si)); // fill this block with zeros
    /*ZeroMemory() sets the memory with the value 0. 
    That is it will clear the memory. 
    Also setting an object(pointer to the object) to NULL means the base address of that object is initialized to 0
    */
    si.cb = sizeof(si);          // CreateProcess(cString, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi); 
    if (!CreateProcess(cString,  // No module name (use command line)
                       NULL,     // Command line
                       NULL,     // Process handle not inheritable
                       NULL,     // Thread handle not inheritable
                       FALSE,    // Set handle inheritance to FALSE
                       CREATE_NEW_CONSOLE,
                       NULL, // Use parent's environment block
                       NULL, // Use parent's starting directory
                       &si,  // Pointer to STARTUPINFO structure
                       &pi)  // Pointer to PROCESS_INFORMATION structure
    )
    {
        printf("Changing of directory or opening file not successful!\n");
        return;
    }
    if (SetConsoleCtrlHandler(CtrlHandler, TRUE))
    {
        WaitForSingleObject(pi.hProcess, INFINITE); // INFINITE // hProcess: The handle is used to specify the process in all functions that perform operations on the process object.
    //Đợi cho tiến trình chạy cho đến khi mình hủy
    //Thử chuyển infinite thành 1 => tiến trình tự tắt => list thì không thấy tiến trình nữa
        
    }
    
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
}

void openProcessInBackGround(const string &s)
{
    void kill(string s);
    ++n;
    status[n] = 1;
    si[n] = {sizeof(STARTUPINFO)};     // lpStartupInfo // lpProcessInformation
    pi[n];                             // cpp string must be modified to use in c
    ZeroMemory(&si[n], sizeof(si[n])); // fill this block with zeros
    si[n].cb = sizeof(si[n]);
    cString[n] = strdup(s.c_str()); // CreateProcess(cString, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
    //Nếu mà tạo tiến trình không thành công 
    if (!CreateProcess(cString[n],  // No module name (use command line)
                       NULL,        // Command line
                       NULL,        // Process handle not inheritable
                       NULL,        // Thread handle not inheritable
                       FALSE,       // Set handle inheritance to FALSE
                       CREATE_NEW_CONSOLE,
                       NULL,   // Use parent's environment block
                       NULL,   // Use parent's starting directory
                       &si[n], // Pointer to STARTUPINFO structure
                       &pi[n]) // Pointer to PROCESS_INFORMATION structure
    )
    {   
        //Tắt tiến trình
        TerminateProcess(pi[n].hProcess, 0);
        //Bỏ tác vụ 
        CloseHandle(pi[n].hThread);
        CloseHandle(pi[n].hProcess);
        n--;
        printf("Changing of directory or opening file not successful!\n");
        return;
    }
}

void listOfCurrent()
{
    char *buffer;

    // Get the current working directory:

    if ((buffer = _getcwd(NULL, 0)) == NULL) //Nếu không có địa chỉ
        perror("_getcwd error"); //In ra ten loi
    else
    {
//        printf("%s \n", buffer);
    }
    if (_chdir(buffer)) // Thay doi thu muc lam viec hien tai
    {
        switch (errno)
        {
        case ENOENT:
            printf("No such file or directory.\n");
            break;
        case EINVAL:
            printf("Invalid buffer.\n");
            break;
        default:
            printf("Unknown error.\n");
            break;
        }
    }
    else
        system("dir");

    free(buffer);
}

void list1()
{
    //Track running process
    // List những cái tiến trình đang hoạt động

    printf("\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| Numbers            IdProcess                hProcess               Status                      Name   \n");
    for (int i = 1; i <= n; ++i)
    {
    	DWORD dwExitCode;
        GetExitCodeProcess(pi[i].hProcess, &dwExitCode);
        if (dwExitCode != 259)
        {
            TerminateProcess(pi[i].hProcess, 0);
            CloseHandle(pi[i].hThread);
            CloseHandle(pi[i].hProcess);
            for (int j = i; j < n; ++j)
            {
                status[j] = status[j + 1];
                pi[j] = pi[j + 1];
                si[j] = si[j + 1];
                cString[j] = cString[j + 1];
            }
            n--;
            i--;
        }
        else
		{
        const char *a = (status[i] == 0) ? "stopping" : "Running ";
        printf("|   %-19d%-26d%-20p%s          %s\n", i, pi[i].dwProcessId, pi[i].hProcess, a, cString[i]);
        }
    }
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n");
}

void cd(string s)
{
	char dir[100];
    LPSTR cString = strdup(s.c_str()); // strup(): This function returns a pointer to a null-terminated byte string, which is a duplicate of the string pointed to by s. 
    //The memory obtained is done dynamically using malloc and hence it can be freed using free(). 
    //It returns a pointer to the duplicated string s.
    //c_str(): trả về con trỏ của chuỗi s
    // cString = s , 2 con trỏ khác nhau trỏ về 2 chỗ khác nhau có nội dung giống nhau
    int ch = chdir(cString);           // if the change of directory was successful it will print successful otherwise it will print not successful
    // int chdir(const char *path): hàm thay đổi địa chỉ path, bằng 0 thì thành công, =-1 thì không thành công

    if (ch < 0)
    {	
        openInBackOrFore("path back", cString);
    }
}

void runBat(string s)
{
    void run(string command);

    //Đọc file
    ifstream file(s);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            run(line);
        }
    }
    else
    {
        cout << "File " << s << " do not exist in this directory\n";
    }
}

void runExe(string command)
{
    void openProcessInForeGround(const string &s);
    void openProcessInBackGround(const string &s);
    stringstream cc(command);
    string c1, c2;
    cc >> c1;
    cc >> c2;
    if (c2.compare("back") == 0)
    {
        openProcessInBackGround(c1);
    }
    else if (c2.compare("fore") == 0)
    {
        openProcessInForeGround(c1);
    }
    else
    {
        printf("Illegal command! Add backgound or foreground mode!\n");
    }
}

// Biến môi trường 
void read_env(char *envname) {
	#define MAX_NAME 16383 // registry element limit for name
	#define MAX_VALUE 100000
	HKEY hkey; // 
    /*
    HKEY_LOCAL_MACHINE hoặc HKLM
HKEY_CURRENT_CONFIG hoặc HKCC 
HKEY_CLASSES_ROOT hoặc HKCR
HKEY_CURRENT_USER hoặc HKCU
HKEY_USERS hoặc HKU
HKEY_PERFORMANCE_DATA (chỉ trong Windows NT, nhưng không hiển thị trong Windows Registry Editor)
HKEY_DYN_DATA (chỉ trong Windows 9x và hiển thị trong Windows Registry Editor)
    */
	BYTE value[MAX_VALUE] ;
    DWORD valsize = sizeof(value) ; //unsigned int
    RegOpenKeyEx(HKEY_CURRENT_USER, "Environment", 0, KEY_ALL_ACCESS, &hkey);
    /*
    RegOpenKeyEx opens a key in the Windows registry. 
    The handle it gives must be used when you read to or write from any values under that key.
    int RegOpenKeyEx(
int hKey,
Pointer<Utf16> lpSubKey,
int ulOptions,
int samDesired,
Pointer<IntPtr> phkResult
)
    */

    if (envname == NULL) {
    	for (int i = 0; ; i ++) {
    		TCHAR name[MAX_NAME]; // char 
			DWORD namesz = MAX_NAME;
			value[0] = '\0';
  			DWORD valsize = MAX_VALUE;
    		if (RegEnumValue(hkey, i, name, &namesz, NULL, NULL, value, &valsize) == 0) {
				cout << (i < 9 ? "0":"") << i + 1 <<". " << name
					 << " = " << value << "\n";
			}
			else {
				break;
			}
		}
        
	}
	else if (RegQueryValueEx(hkey, envname, NULL, NULL, value, &valsize ) == 0) {
		cout << "The value of "<< envname<<" is: "<< value<<"\n";	
	}
	else {
		cout << "There no variables has the name "<< envname<< "\n";
	}
  	
	RegCloseKey(hkey);
}

void add_env(char* envname, char *envvalue) {
	cout << "The environment variable "<< envname<< " is added\n";
    HKEY hkey;
	static BYTE value[100000] ;
    DWORD valsize = sizeof(value) ;                                  
    RegOpenKeyEx(HKEY_CURRENT_USER,"Environment", 0, KEY_ALL_ACCESS, &hkey);
	if(RegQueryValueEx(hkey, envname, NULL, NULL, value, &valsize) == 0){
		char *name  = (char*) value;
		strcat(name, ";");
		strcat(name, envvalue);
    	RegSetValueEx(hkey,envname,0,REG_SZ,(BYTE*) name, strlen(name));
	}
	else {
		RegSetValueEx(hkey,envname,0,REG_SZ,(BYTE*) envvalue, strlen(envvalue));
	}
    RegCloseKey(hkey);
}

void del_env(char*envname){
	HKEY hkey;
	RegOpenKeyEx(HKEY_CURRENT_USER,"Environment", 0, KEY_ALL_ACCESS, &hkey);
	if (RegDeleteValue(hkey, envname) == 0) {
		cout << "The environment variable "<< envname<< " is deleted\n";
	}
	else {
		cout << "There no variables has the name "<< envname<< "\n";
	}
	RegCloseKey(hkey);
}

