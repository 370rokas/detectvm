#include <iostream>
#include <windows.h>
#include <tchar.h>

BOOL SelfDelete(){
TCHAR szFile[MAX_PATH], szCmd[MAX_PATH];
if((GetModuleFileName(0,szFile,MAX_PATH)!=0) &&(GetShortPathName(szFile,szFile,MAX_PATH)!=0)){
lstrcpy(szCmd,_T("/c del "));lstrcat(szCmd,szFile);lstrcat(szCmd,_T(" >> NUL"));
 if((GetEnvironmentVariable(_T("ComSpec"),szFile,MAX_PATH)!=0) &&((INT)ShellExecute(0,0,szFile,szCmd,0,SW_HIDE)>32))
    return TRUE;}return FALSE;
}

bool IsVboxVM(){
    HANDLE handle = CreateFile(_T("\\\\.\\VBoxMiniRdrDN"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (handle != INVALID_HANDLE_VALUE){CloseHandle(handle);return true;}
    return false;}

bool IsVMwareVM(){
    HKEY hKey = 0;DWORD dwType = REG_SZ;char buf[255] = {0};DWORD dwBufSize = sizeof(buf);
    if( RegOpenKeyEx( HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\VMware, Inc.\\VMware Tools"), 0, KEY_QUERY_VALUE, &hKey ) == ERROR_SUCCESS ) {
    return true;}
    return false;
}

int main(){
    if (IsVboxVM() == true){std::cout << "Running in vbox!";}
    else if(IsVMwareVM()==true){std::cout << "Running in vmware!";}
    else{std::cout << "Not in vbox or vmware!";}
    if (IsVboxVM() == true || IsVMwareVM() == true){SelfDelete(); exit(-1);}
}