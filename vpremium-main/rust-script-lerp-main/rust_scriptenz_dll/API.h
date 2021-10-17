#pragma once
#include <Windows.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include <Wininet.h>
#include <string>
#include <sstream>      // std::stringstream
#pragma comment(lib, "wininet.lib")
using namespace std;

#define LOCAL_HWID ScriptinMekani::GetMachineGUID();



template <int XORSTART, int BUFLEN, int XREFKILLER>

class XorStr {
private:
	XorStr();
public:
	char s[BUFLEN];
	XorStr(const char* xs);
	~XorStr() {
		for (int i = 0; i < BUFLEN; i++) s[i] = 0;
	}
};
template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStr<XORSTART, BUFLEN, XREFKILLER>::XorStr(const char* xs) {
	int xvalue = XORSTART; int i = 0;
	for (; i < (BUFLEN - 1); i++) {
		s[i] = xs[i - XREFKILLER] ^ xvalue;
		xvalue += 1;
		xvalue %= 256;
	}
	s[BUFLEN - 1] = 0;
}


static bool logcheck = false;

static bool authed = false;
static bool hwided = false;
static bool grouped = false;

namespace ScriptinMekani
{
	string replaceAll(string subject, const string& search,
		const string& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
		return subject;
	}

	string DownloadString(string URL) {
		HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
		HINTERNET urlFile;
		string rtn;
		if (interwebs) {
			urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
			if (urlFile) {
				char buffer[2000];
				DWORD bytesRead;
				do {
					InternetReadFile(urlFile, buffer, 2000, &bytesRead);
					rtn.append(buffer, bytesRead);
					memset(buffer, 0, 2000);
				} while (bytesRead);
				InternetCloseHandle(interwebs);
				InternetCloseHandle(urlFile);
				string p = replaceAll(rtn, "|n", "\r\n");
				return p;
			}
		}
		InternetCloseHandle(interwebs);
		string p = replaceAll(rtn, "|n", "\r\n");
		return p;
	}



	std::string GetMachineGUID()
	{
		std::string ret;
		char value[64];
		DWORD size = _countof(value);
		DWORD type = REG_SZ;
		HKEY key;
		LONG retKey = ::RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Cryptography", 0, KEY_READ | KEY_WOW64_64KEY, &key);
		LONG retVal = ::RegQueryValueExA(key, "MachineGuid", nullptr, &type, (LPBYTE)value, &size);
		if (retKey == ERROR_SUCCESS && retVal == ERROR_SUCCESS) {
			ret = value;
		}
		::RegCloseKey(key);
		return ret;
	}

	std::string GetProductID()
	{
		std::string ret;
		char value[64];
		DWORD size = _countof(value);
		DWORD type = REG_SZ;
		HKEY key;
		LONG retKey = ::RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ | KEY_WOW64_64KEY, &key);
		LONG retVal = ::RegQueryValueExA(key, "ProductID", nullptr, &type, (LPBYTE)value, &size);
		if (retKey == ERROR_SUCCESS && retVal == ERROR_SUCCESS) {
			ret = value;
		}
		::RegCloseKey(key);
		return ret;
	}



	std::string GetProducer()
	{
		std::string ret;
		char value[64];
		DWORD size = _countof(value);
		DWORD type = REG_SZ;
		HKEY key;
		LONG retKey = ::RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ | KEY_WOW64_64KEY, &key);
		LONG retVal = ::RegQueryValueExA(key, "ProcessorNameString", nullptr, &type, (LPBYTE)value, &size);
		if (retKey == ERROR_SUCCESS && retVal == ERROR_SUCCESS) {
			ret = value;
		}
		::RegCloseKey(key);
		return ret;
	}





	std::string DownloadBytes(const char* const szUrl)
	{
		HINTERNET hOpen = NULL;
		HINTERNET hFile = NULL;
		char* lpBuffer = NULL;
		DWORD dwBytesRead = 0;
		char* data = 0;
		DWORD dataSize = 0;

		hOpen = InternetOpenA("victory", NULL, NULL, NULL, NULL);
		if (!hOpen) return "";

		hFile = InternetOpenUrlA(hOpen, szUrl, NULL, NULL, INTERNET_FLAG_RELOAD, NULL);

		if (!hFile) {
			InternetCloseHandle(hOpen);
			return "";
		}

		std::string output;
		do {
			char buffer[2000];
			InternetReadFile(hFile, (LPVOID)buffer, _countof(buffer), &dwBytesRead);
			output.append(buffer, dwBytesRead);
		} while (dwBytesRead);

		InternetCloseHandle(hFile);
		InternetCloseHandle(hOpen);

		return output;
	}

	BYTE toByte(std::string const& str)
	{
		std::stringstream ss;
		ss << hex << str;
		BYTE b;
		ss >> b;
		return b;
	}


	bool Login(char username[128], char password[128])
	{

		std::string dsadsa = XorStr<0x2E, 40, 0x43FEFDB2>("\x46\x5B\x44\x41\x41\x09\x1B\x1A\x40\x5E\x5B\x4D\x55\x49\x45\x4F\x4B\x4C\x34\x6F\x21\x25\x6B\x26\x2E\x22\x2B\x22\x64\x3B\x24\x3D\x71\x23\x3F\x36\x3B\x3D\x69" + 0x43FEFDB2).s;
		std::string dsda = XorStr<0x8F, 11, 0x1C3728B4>("\xA9\xE0\xF0\xE1\xE0\xE3\xFA\xE4\xF3\xA5" + 0x1C3728B4).s;
		std::string adas = dsadsa + username + dsda + password;
		std::string qew = ScriptinMekani::DownloadString(adas);
		if (qew.find("p1<br>") != std::string::npos)
		{
			logcheck = true;

			authed = true;
			if (authed && !hwided && !grouped)
			{
				std::string qeqweqweqkewqe = XorStr<0xBB, 40, 0xB091F549>("\xD3\xC8\xC9\xCE\xCC\xFA\xEE\xED\xB5\xAD\xA6\xB2\xA8\xBA\xB0\xB8\xBE\xBF\xB9\xE0\xAC\xB6\xFE\xB5\xA1\xBB\xA0\xA6\xF9\xA8\xB1\xAA\xE4\xB0\xB2\xB9\xB6\x8E\xDC" + 0xB091F549).s;
				std::string qeqwke = qeqweqweqkewqe + username;
				std::string qeqwe = ScriptinMekani::DownloadString(qeqwke);
				//   MessageBox(0, qeqwe.c_str(), XorStr<0xC3, 15, 0x35A03E04>("\x8E\xAD\xA6\xB4\xA8\xBB\xA6\xAC\xBF\xEC\x88\xAA\xA8\xB5" + 0x35A03E04).s, MB_OK);


				if (qeqwe.find(XorStr<0xDD, 8, 0x08E8ABA6>("\xB3\xB1\xFF\x84\x80\x96\x86" + 0x08E8ABA6).s) != std::string::npos)
				{
					MessageBoxA(0, XorStr<0x7B, 31, 0x800BF157>("\x35\x13\x5D\x0A\x16\xED\xE4\xA2\xEF\xE1\xE3\xF2\xA7\xEA\xFC\xF3\xAB\xED\xAD\xE0\xEA\xE7\xB1\xDE\xFA\xF7\xF0\xF8\xE4\xFD" + 0x800BF157).s, XorStr<0xC3, 15, 0x35A03E04>("\x8E\xAD\xA6\xB4\xA8\xBB\xA6\xAC\xBF\xEC\x88\xAA\xA8\xB5" + 0x35A03E04).s, MB_OK);

				}
				else
				{
					hwided = true;
					if (authed && hwided && !grouped)
					{
						std::string qewqekqweqkekqw = XorStr<0x85, 39, 0x52873AFA>("\xED\xF2\xF3\xF8\xFA\xB0\xA4\xA3\xFB\xE7\xEC\xE4\xFE\xE0\xEA\xE6\xE0\xE5\xE3\xB6\xFA\xFC\xB4\xF4\xEA\xF7\xFB\x8E\xD1\xCA\xD3\x9B\xC9\xC9\xC0\xC1\xC7\x97" + 0x52873AFA).s;
						std::string qekq = XorStr<0x52, 7, 0x9C570C38>("\x74\x3B\x23\x3C\x32\x6A" + 0x9C570C38).s;
						std::string low = ScriptinMekani::GetMachineGUID();
						std::string eqwkeq = qewqekqweqkekqw + username + qekq + low;
						std::string ddsada = ScriptinMekani::DownloadString(eqwkeq);
						//MessageBox(0, eqwkeq.c_str(), XorStr<0xC3, 15, 0x35A03E04>("\x8E\xAD\xA6\xB4\xA8\xBB\xA6\xAC\xBF\xEC\x88\xAA\xA8\xB5" + 0x35A03E04).s, MB_OK);


						if (ddsada.find("1") != std::string::npos)
						{
							MessageBoxA(0, XorStr<0xE5, 23, 0xBC47E6B2>("\xB2\x83\x8B\x8B\x86\x87\x8E\xCC\x99\x81\xCF\xA6\x98\x91\x87\x9B\x87\x8F\xA5\x8D\x8A\x8E" + 0xBC47E6B2).s, XorStr<0xC3, 15, 0x35A03E04>("\x8E\xAD\xA6\xB4\xA8\xBB\xA6\xAC\xBF\xEC\x88\xAA\xA8\xB5" + 0x35A03E04).s, MB_OK);


							//MessageBox(0, kqkqkqkqkqkqk.c_str(), XorStr<0xC3, 15, 0x35A03E04>("\x8E\xAD\xA6\xB4\xA8\xBB\xA6\xAC\xBF\xEC\x88\xAA\xA8\xB5" + 0x35A03E04).s, MB_OK);


							grouped = true;
							return true;






						}
						else if (ddsada.find("0") != std::string::npos)
						{
							MessageBoxA(0, XorStr<0x69, 11, 0xDF267644>("\x21\x1D\x02\x08\x4D\x39\x1D\x1F\x1F\x15" + 0xDF267644).s, XorStr<0xC3, 15, 0x35A03E04>("\x8E\xAD\xA6\xB4\xA8\xBB\xA6\xAC\xBF\xEC\x88\xAA\xA8\xB5" + 0x35A03E04).s, MB_OK);

						}

						else if (ddsada.find("3") != std::string::npos)
						{
							MessageBoxA(0, XorStr<0xAE, 36, 0x444185F5>("\xF7\xC0\xC5\xC3\x92\xFB\xC3\xDC\xD2\x97\xD0\xD8\xC9\x9B\xDE\xD8\xDB\xD1\xE0\xB2\xA7\xB7\xB0\xA0\xA2\xE7\xBC\xA6\xEA\xB8\xB5\xBE\xBA\xAA\xBD" + 0x444185F5).s, XorStr<0xC3, 15, 0x35A03E04>("\x8E\xAD\xA6\xB4\xA8\xBB\xA6\xAC\xBF\xEC\x88\xAA\xA8\xB5" + 0x35A03E04).s, MB_OK);
							return true;


						}

					}
				}
			}

		}
		else
		{
			return false;

		}


	}

}