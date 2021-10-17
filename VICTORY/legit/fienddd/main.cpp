#include <Windows.h>
#include <Windows.h>

#include "Overlay.h"
#include "driver.h"
#include "Memory.h"



using namespace std;

UINT64 Gbase;
UINT64 Ubase;

HANDLE memory_read = NULL, memory_write = NULL, memory_esp_write = NULL;




void InitializeDriver() {
	if (driver::open_memory_handles())
		std::cout << "[-] Shared memory handles opened successfully" << std::endl;
	else
	{
		std::cout << "[!] Shared memory handles failed to open" << std::endl;
		std::cin.get();
		return;
	}

	if (driver::get_process_id("RustClient.exe"))
		std::cout << "[-] PID aquired successfully" << std::endl;

	else
	{
		std::cout << "[!] could not get pid" << std::endl;
		std::cin.get();
		return;
	}

	Gbase = (UINT64)driver::get_module_base_address("GameAssembly.dll");
	Ubase = (UINT64)driver::get_module_base_address("UnityPlayer.dll");
	if (!Gbase || !Ubase)
	{
		//std::cout << "	[+] game assembly: " << std::hex << game_assembly << std::endl;
		//std::cout << "	[+] unity player: " << std::hex << unity_player << std::endl;

		std::cout << "[!] failed to aquire base address..." << std::endl;
		std::cout << "[!] GBASE : " << Gbase << endl;
		std::cout << "[!] UBASE : " << Ubase << endl;
		std::cin.get();
		return;
	}

	std::cout << "[+] aquired base address and PID" << std::endl;
	std::cout << "[!] GBASE : " << std::hex << Gbase << endl;
	std::cout << "[!] UBASE : " << Ubase << endl;

	std::cout << "[!+!] Driver successfully initialized!" << std::endl;


}
#include "DriverLoad.h"


void SetConsole(bool showFlag) {
	SetConsoleTitle("EyeRust Legit Version");

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
	SetConsole(true);
	
	int choice;
	std::cout << "\n\n -> MAKE SURE RUST IS CLOSED IF YOU ARE GOING TO LOAD THE DRIVER!" << std::endl;
	std::cout << green <<" [+]"<< white <<" TYPE 1 TO LOAD DRIVER AND 2 TO SKIP (ONLY LOAD ONCE PER PC RESTART)" << std::endl;
	std::cin >> choice;
	if (choice == 1) {
		DriverLoad();
		//DriverLoadIntel();
	}
	std::cout << " NOW MAKE SURE RUST IS OPEN AND THEN TYPE \"YES\"" << std::endl;
	std::string Answer;
	while (Answer != "YES")
	{

		Answer = "";
		std::cin >> Answer;
		std::cout << std::endl;
		if (Answer == "YES") {

			std::cout << green <<"CONFIRMED " << white << std::endl;
			break;
		}
		else
		{
			std::cout << white <<"DIDNT TYPE YES, TRY AGAIN " << std::endl;
		}
	}


	printf("\n\nSTARTING EyeRust...");
	InitializeDriver();
	InitOverlay();
}



