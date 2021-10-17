#include "hwid.h"
using namespace std;
string HWID = _xor_("a");

string getProductId() {
    HKEY keyHandle;
    WCHAR rgValue[1024];
    WCHAR fnlRes[1024];
    DWORD size1;
    DWORD Type;

    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_QUERY_VALUE | KEY_WOW64_64KEY, &keyHandle) == ERROR_SUCCESS)
    {
        size1 = 1023;
        RegQueryValueExW(keyHandle, L"Productid", NULL, &Type, (LPBYTE)rgValue, &size1);
        RegCloseKey(keyHandle);
        wstring rgValueCh = rgValue;
        string convertRgVal(rgValueCh.begin(), rgValueCh.end());
        return convertRgVal;
    }
}
string getCurrentBuild() {
    HKEY keyHandle;
    WCHAR rgValue[1024];
    WCHAR fnlRes[1024];
    DWORD size1;
    DWORD Type;

    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_QUERY_VALUE | KEY_WOW64_64KEY, &keyHandle) == ERROR_SUCCESS)
    {
        size1 = 1023;
        RegQueryValueExW(keyHandle, L"CurrentBuild", NULL, &Type, (LPBYTE)rgValue, &size1);
        RegCloseKey(keyHandle);
        wstring rgValueCh = rgValue;
        string convertRgVal(rgValueCh.begin(), rgValueCh.end());
        return convertRgVal;
    }
}
string getMachineId()
{
    // LPCTSTR szHD = "C:\\";  // ERROR
    string ss;
    ss = "Err_StringIsNull";
    UCHAR szFileSys[255],
        szVolNameBuff[255];
    DWORD dwSerial;
    DWORD dwMFL;
    DWORD dwSysFlags;
    int error = 0;

    bool success = GetVolumeInformation(LPCTSTR("C:\\"), (LPTSTR)szVolNameBuff,
        255, &dwSerial,
        &dwMFL, &dwSysFlags,
        (LPTSTR)szFileSys,
        255);
    if (!success) {
        ss = "Err_Not_Elevated";
    }
    std::stringstream errorStream;
    errorStream << dwSerial;
    return string(errorStream.str().c_str());
}
#include <Iphlpapi.h>
#include <Assert.h>
#include <iomanip>
#include <conio.h>
#include <intrin.h>
#include <comdef.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "wbemuuid.lib")
#include <stdio.h>

#include <intrin.h>
#pragma warning(disable:4996)

#include <iostream>
#include <sstream>
#include <Windows.h>

#include <string.h>
#include <string>
#include <array>
string getHWinfo64() {

    std::array<int, 4> cpuInfo;
    __cpuid(cpuInfo.data(), 1);
    std::ostringstream buffer;
    buffer
        << std::uppercase << std::hex << std::setfill('0')
        << std::setw(8) << cpuInfo.at(3)
        << std::setw(8) << cpuInfo.at(0);
    return buffer.str();

}