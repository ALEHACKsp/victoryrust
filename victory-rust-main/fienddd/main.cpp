#include <Windows.h>
#include <Windows.h>

#include "Overlay.h"
#include "driver.h"
#include "Memory.h"

#include "kdmapper\kdmapper.hpp"
#include "kdmapper\driverbyte.h"


using namespace std;



HANDLE memory_read = NULL, memory_write = NULL, memory_esp_write = NULL;




void InitializeDriver() {
	mem->Attach("RustClient.exe"); //RPM MEMORY, NOT DRIVER CLASS
	mem->process_id = mem->GetPID(("RustClient.exe"));
	Gbase = (UINT64)mem->GetModuleBase(("GameAssembly.dll"));
	Ubase = (UINT64)mem->GetModuleBase(("UnityPlayer.dll"));

	std::cout << "[+] aquired base address and PID" << std::endl;
	std::cout << "[!] GBASE : " << std::hex << Gbase << endl;
	std::cout << "[!] UBASE : " << Ubase << endl;

	std::cout << "[!+!] Driver successfully initialized!" << std::endl;

}



void SetConsole(bool showFlag) {
	SetConsoleTitle("EyeRust Premium");

	int horizontal = 0, vertical = 0;
	int x = 450, y = 600; //Change the window size

	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 15;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	HWND hwnd = GetConsoleWindow();
	
	
	LONG lStyle = GetWindowLong(hwnd, GWL_STYLE);
	lStyle &= ~(WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
	SetWindowLong(hwnd, GWL_STYLE, lStyle);
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(console, &csbi);
	COORD scrollbar = {
		csbi.srWindow.Right - csbi.srWindow.Left + 1,
		csbi.srWindow.Bottom - csbi.srWindow.Top + 1
	};
	if (console == 0)
		throw 0;
	else
		SetConsoleScreenBufferSize(console, scrollbar);
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, 0, (255 * 96) / 100, LWA_ALPHA); //Setting the background transparency
}; 
#include <iostream> #include <vector> #include <iostream> #include <windows.h>

inline std::ostream& green(std::ostream& s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	return s;
}
inline std::ostream& white(std::ostream& s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return s;
}
int main() {

bakugan:
encocuk:
	SetConsole(true);

	int choice;
	std::cout << "\n\n -> MAKE SURE RUST IS CLOSED IF YOU ARE GOING TO LOAD THE DRIVER!" << std::endl;
	std::cout << green << " [+]" << white << " TYPE 1 TO LOAD DRIVER AND 2 TO SKIP (ONLY LOAD ONCE PER PC RESTART)" << std::endl;
	std::cin >> choice;
	if (choice == 1) {

		HANDLE iqvw64e_device_handle = intel_driver::Load();

		if (!iqvw64e_device_handle || iqvw64e_device_handle == INVALID_HANDLE_VALUE)
		{
			std::cout << "[-] Failed to load driver iqvw64e.sys" << std::endl;
			return -1;
		}

		if (!kdmapper::MapDriver(iqvw64e_device_handle, RawData))
		{
			std::cout << "[-] Failed to map driver" << std::endl;
			intel_driver::Unload(iqvw64e_device_handle);
			return -1;
		}

		intel_driver::Unload(iqvw64e_device_handle);
		MessageBoxA(0, "success", "nice", 0);


	}
	std::cout << " NOW MAKE SURE RUST IS OPEN AND THEN TYPE \"YES\"" << std::endl;
	std::string Answer;
	while (Answer != "YES")
	{

		Answer = "";
		std::cin >> Answer;
		std::cout << std::endl;
		if (Answer == "YES") {

			std::cout << green << "CONFIRMED " << white << std::endl;
			break;
		}
		else
		{
			std::cout << white << "DIDNT TYPE YES, TRY AGAIN " << std::endl;
		}
	}


	printf("\n\nSTARTING EyeRust...");
	InitializeDriver();
	InitOverlay();

	


}



