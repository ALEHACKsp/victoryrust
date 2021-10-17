#pragma once

#ifndef GRAPHICS_API
#define GRAPHICS_API

#include "../pch/pch.h"
#include <dwmapi.h>
#include <magnification.h>
#include "../main/internal.hpp"
#include <imgui_internal.h>
#include <D2D1Helper.h>
#include <d2d1helper.h>

#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "magnification.lib")

using WndProcCallback = std::function<bool(HWND, UINT, WPARAM, LPARAM)>;

LPDIRECT3D9 g_pD3D;
LPDIRECT3DDEVICE9 g_pd3dDevice;
D3DPRESENT_PARAMETERS g_d3dpp;
HWND g_hwnd;
WndProcCallback g_wndProcCallback;
bool* g_pMenuOpen;
int* g_pMenuKeyBind;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#include "../files.h"
#include <stdio.h>
#include <string>
#include <windows.h>

int hippp = 0;

bool crosscheckbox = false;
bool weaps = true;
bool preview = false;
bool weapinfo = false;
bool spotifyyy = false;
int antiafkkeybind = 0;
int antiafkkeybind1 = 0;
bool randomi = false;
bool smothi = false;
float col1[4]{ 0.0f, 1.0f, 0.0,1.f };
bool antiafk = false;
int rapids = 0;
bool bRapidf = false;
void Settingsss::Setup() {
	if (section == 1)
	{
		LoadConfig();
	}
	else if (section == 2)
	{
		SaveConfig();
	}
}

void Settingsss::SetupS() {

	SaveConfig();

}

void Settingsss::SaveConfig()
{
	files->OnSetup();
	files->WriteInt("Recoil", "ak47", Internal::bAKKey);
	files->WriteInt("Recoil", "lr", Internal::bLRKey);
	files->WriteInt("Recoil", "mp5", Internal::bMP5Key);
	files->WriteInt("Recoil", "thomp", Internal::bTOMMYKey);
	files->WriteInt("Recoil", "smg", Internal::bCUSTOMKey);
	files->WriteInt("Recoil", "semi", Internal::bSARKey);
	files->WriteInt("Recoil", "faytoncuk", Internal::bPYTHONKey);
	files->WriteInt("Recoil", "m249", Internal::bM249Key);
	files->WriteInt("Recoil", "m39", Internal::bM39Key);
	files->WriteInt("Recoil", "m92", Internal::bM92Key);
	files->WriteInt("Recoil", "sap", Internal::bSAPKey);
	files->WriteInt("Attachments", "hippp", hippp);
	//Attachments
	files->WriteInt("Attachments", "holo", Internal::bHOLOKey);
	files->WriteInt("Attachments", "simple", Internal::bSIMPLEKey);
	files->WriteInt("Attachments", "sekiz", Internal::b8XKey);
	files->WriteInt("Attachments", "on16", Internal::b16XKey);
	files->WriteInt("Attachments", "saylins", Internal::bSILENCERKey);
	files->WriteInt("Attachments", "MuzzleBoost", Internal::bBOOSTKey);
	files->WriteFloat("Randomization", "XSCALE", Internal::inaccuracy_x);
	files->WriteFloat("Randomization", "YSCALE", Internal::inaccuracy_y);
	//Floats
	files->WriteFloat("Sensivity", "UserSens", Internal::sensitivity);
	//Bools

	
	files->WriteBool("Misc", "enabled", spotifyyy);
	files->WriteBool("Misc", "preview", preview);
	files->WriteBool("Misc", "soundcheck", Internal::Sounds_toggle);
	files->WriteBool("Misc", "bRapidf", bRapidf);
	files->WriteBool("Misc", "randomi", randomi);
	files->WriteBool("Misc", "crosscheckbox", crosscheckbox);
	files->WriteBool("Misc", "weaps", weaps);
	//Helpers
	files->WriteInt("Helpers", "rapids", rapids);
	files->WriteInt("Helpers", "antiafkkeybind", antiafkkeybind);
	files->WriteInt("Helpers", "antiafkkeybind1", antiafkkeybind1);
	






	Beep(195, 200);
}

void Settingsss::LoadConfig()
{

	files->OnSetup();
	Internal::bAKKey = files->ReadInt("Recoil", "ak47");
	Internal::bLRKey = files->ReadInt("Recoil", "lr");
	Internal::bMP5Key = files->ReadInt("Recoil", "mp5");
	Internal::bTOMMYKey = files->ReadInt("Recoil", "thomp");
	Internal::bCUSTOMKey = files->ReadInt("Recoil", "smg");
	Internal::bSARKey = files->ReadInt("Recoil", "semi");
	Internal::bPYTHONKey = files->ReadInt("Recoil", "faytoncuk");
	Internal::bM249Key = files->ReadInt("Recoil", "m249");
	Internal::bM39Key = files->ReadInt("Recoil", "m39");
	Internal::bM92Key = files->ReadInt("Recoil", "m92");
	Internal::bSAPKey = files->ReadInt("Recoil", "sap");
	hippp = files->ReadInt("Attachments", "hippp");

	//Attachments
	Internal::bHOLOKey = files->ReadInt("Attachments", "holo");
	Internal::bSIMPLEKey = files->ReadInt("Attachments", "simple");
	Internal::b8XKey = files->ReadInt("Attachments", "sekiz");
	Internal::b16XKey = files->ReadInt("Attachments", "on16");
	Internal::bSILENCERKey = files->ReadInt("Attachments", "saylins");
	Internal::bBOOSTKey = files->ReadInt("Attachments", "MuzzleBoost");
	Internal::inaccuracy_x = files->ReadInt("Randomization", "XSCALE");
	Internal::inaccuracy_y = files->ReadInt("Randomization", "YSCALE");
	//FLOATS
	Internal::sensitivity = files->ReadFloat("Sensivity", "UserSens");

	//Bools
	spotifyyy = files->ReadBool("Misc", "enabled");
	preview = files->ReadBool("Misc", "preview");
	Internal::Sounds_toggle = files->ReadBool("Misc", "soundcheck");
	bRapidf = files->ReadBool("Misc", "bRapidf");
	randomi = files->ReadBool("Misc", "randomi");
	crosscheckbox = files->ReadBool("Misc", "crosscheckbox");
	weaps = files->ReadBool("Misc", "weaps");
	//Helpers
	rapids = files->ReadInt("Helpers", "rapids");
	antiafkkeybind = files->ReadInt("Helpers", "antiafkkeybind");
	antiafkkeybind1 = files->ReadInt("Helpers", "antiafkkeybind1");

	//Beep(300, 200);

}

bool Settingsss::CofigExists()
{
	struct stat buffer;
	return (stat("Settingsss.cfg", &buffer) == 0);
}

LRESULT CALLBACK GlobalKeyboardHook(int msg, WPARAM wParam, LPARAM lParam) {
	if (msg == HC_ACTION) {
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
		switch (wParam) {
		case WM_KEYUP:


			if (p->vkCode == *g_pMenuKeyBind)
			{
				*g_pMenuOpen = !(*g_pMenuOpen);
				if (*g_pMenuOpen)
				{
					printf("dd");
					SetWindowLong(g_hwnd, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
				}
				else if (*g_pMenuOpen)
				{
					SetWindowLong(g_hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
					Internal::g_open = false;
				}
			}
			if (p->vkCode == Internal::bAKKey) {
				if (Internal::bAKActivate == false)
				{
					Internal::Weapon = "AK-47";
					Internal::current_weapon = 1;
					Internal::sounds();
				}
				else if (Internal::bAKActivate == true)
				{
					Internal::Weapon = "NONE";
					Internal::current_weapon = 0;
					Internal::sounds();
				}
			}
			if (p->vkCode == Internal::bLRKey) {
				if (Internal::bLRActivate == false)
				{
					Internal::Weapon = "LR-300";

					Internal::current_weapon = 2;
					Internal::sounds();
				}
				else if (Internal::bLRActivate == true)
				{
					Internal::Weapon = "NONE";

					Internal::current_weapon = 0;
					Internal::sounds();
				}
			}
			if (p->vkCode == Internal::bMP5Key) {
				if (Internal::bMP5Activate == false)
				{
					Internal::Weapon = "MP5";

					Internal::current_weapon = 3;
					Internal::sounds();
				}
				else if (Internal::bMP5Activate == true)
				{
					Internal::Weapon = "NONE";
					Internal::current_weapon = 0;
					Internal::sounds();
				}
			}
			if (p->vkCode == Internal::bTOMMYKey) {
				if (Internal::bTOMMYActivate == false)
				{
					Internal::Weapon = "Thompson";

					Internal::current_weapon = 4;
					Internal::sounds();
				}
				else if (Internal::bTOMMYActivate == true)
				{
					Internal::Weapon = "NONE";
					Internal::current_weapon = 0;
					Internal::sounds();
				}
			}
			if (p->vkCode == Internal::bCUSTOMKey) {
				if (Internal::bCUSTOMActivate == false)
				{
					Internal::Weapon = "C-SMG";
					Internal::current_weapon = 5;
					Internal::sounds();
				}
				else if (Internal::bCUSTOMActivate == true)
				{
					Internal::Weapon = "NONE";
					Internal::current_weapon = 0;
					Internal::sounds();
				}
			}
			if (p->vkCode == Internal::bM249Key) {
				if (Internal::bM249Activate == false)
				{
					Internal::Weapon = "M249";
					Internal::current_weapon = 6;
					Internal::sounds();
				}
				else if (Internal::bM249Activate == true)
				{
					Internal::Weapon = "NONE";
					Internal::current_weapon = 0;
					Internal::sounds();
				}
			}
			

			if (p->vkCode == Internal::bSARKey) {
				if (Internal::bSARActivate == false)
				{
					Internal::Weapon = "SEMI";
					Internal::current_weapon = 7;
					Internal::sounds();
				}
				else if (Internal::bSARActivate == true)
				{
					Internal::Weapon = "NONE";
					Internal::current_weapon = 0;
					Internal::sounds();
				}
			}

			if (p->vkCode == Internal::bSAPKey) {
				if (Internal::bSemiPistolActivate == false)
				{
					Internal::Weapon = "SAP";
					Internal::current_weapon = 8;
					Internal::sounds();
				}
				else if (Internal::bSemiPistolActivate == true)
				{
					Internal::Weapon = "NONE";
					Internal::current_weapon = 0;
					Internal::sounds();
				}
			}
			if (p->vkCode == Internal::bM39Key) {
				if (Internal::bM39Activate == false)
				{
					Internal::Weapon = "M39";
					Internal::current_weapon = 9;
					Internal::sounds();
				}
				else if (Internal::bM39Activate == true)
				{
					Internal::Weapon = "NONE";
					Internal::current_weapon = 0;
					Internal::sounds();
				}
			}
			if (p->vkCode == Internal::bM92Key) {
				if (Internal::bM92Activate == false)
				{
					Internal::Weapon = "M92";
					Internal::current_weapon = 10;
					Internal::sounds();
				}
				else if (Internal::bM92Activate == true)
				{
					Internal::Weapon = "NONE";
					Internal::current_weapon = 0;
					Internal::sounds();
				}
			}
			if (p->vkCode == Internal::bPYTHONKey) {
				if (Internal::bPythonActivate == false)
				{
					Internal::Weapon = "Python";
					Internal::current_weapon = 11;
					Internal::sounds();
				}
				else if (Internal::bPythonActivate == true)
				{
					Internal::Weapon = "NONE";
					Internal::current_weapon = 0;
					Internal::sounds();
				}
			}



			if (p->vkCode == Internal::bHOLOKey) {
				if (Internal::bHoloActivate == false)
				{
					Internal::Scope = "HOLO";
					Internal::current_scopes = 1;
					Internal::sounds();
				}
				else if (Internal::bHoloActivate == true)
				{
					Internal::Scope = "NONE";
					Internal::current_scopes = 0;
					Internal::sounds();
				}
			}
			if (p->vkCode == Internal::b8XKey) {
				if (Internal::b8XActivate == false)
				{
					Internal::Scope = "8X";
					Internal::current_scopes = 2;
					Internal::sounds();
				}
				else if (Internal::b8XActivate == true)
				{
					Internal::Scope = "NONE";
					Internal::current_scopes = 0;
					Internal::sounds();
				}
			}
			if (p->vkCode == Internal::b16XKey) {
				if (Internal::b16XKey == false)
				{
					Internal::Scope = "16X";
					Internal::current_scopes = 3;
					Internal::sounds();
				}
				else if (Internal::b16XKey == true)
				{
					Internal::Scope = "NONE";
					Internal::current_scopes = 0;
					Internal::sounds();
				}
			}

			if (p->vkCode == Internal::bSIMPLEKey) {
				if (Internal::bSimpleActivate == false)
				{
					Internal::Scope = "SIMPLE";
					Internal::current_scopes = 4;
					Internal::sounds();
				}
				else if (Internal::bSimpleActivate == true)
				{
					Internal::Scope = "NONE";
					Internal::current_scopes = 0;
					Internal::sounds();
				}
			}
			if (p->vkCode == Internal::bSILENCERKey) {
				if (Internal::bSilencerActivate == false)
				{
					Internal::Barrel = "SILENCE";
					Internal::current_barrel = 1;
					Internal::sounds();
				}
				else if (Internal::bSilencerActivate == true)
				{
					Internal::Barrel = "NONE";
					Internal::current_barrel = 0;
					Internal::sounds();
				}
			}
			if (p->vkCode == Internal::bBOOSTKey) {
				if (Internal::bBoostActivate == false)
				{
					Internal::Barrel = "Boost";
					Internal::current_barrel = 2;
					Internal::sounds();
				}
				else if (Internal::bBoostActivate == true)
				{
					Internal::Barrel = "NONE";
					Internal::current_barrel = 0;
					Internal::sounds();
				}
			}





			

			if (p->vkCode == VK_UP) {
				Internal::current_cycle = Internal::current_cycle - 1;
				std::cout << "-1" << std::endl;

				if (Internal::current_cycle == -1)
				{
					Internal::current_cycle = 3;
					std::cout << "CYCLE RESET" << std::endl;
				}
			}
			if (p->vkCode == VK_DOWN) {
				Internal::current_cycle = Internal::current_cycle + 1;
				std::cout << "+1" << std::endl;

				if (Internal::current_cycle > 3)
				{
					Internal::current_cycle = 0;
					std::cout << "CYCLE RESET" << std::endl;
				}
			}
			if (p->vkCode == VK_RIGHT) {
				if (Internal::current_cycle == 0)
				{
					Internal::current_status = Internal::current_status + 1;
					printf("0");
				}
				if (Internal::current_cycle == 1)
				{
					Internal::current_weapon = Internal::current_weapon + 1;
					printf("1");
				}
				if (Internal::current_cycle == 2)
				{
					Internal::current_scopes = Internal::current_scopes + 1;
					printf("2");
				}
				if (Internal::current_cycle == 3)
				{
					Internal::current_barrel = Internal::current_barrel + 1;
					printf("3");
				}
			}
			if (p->vkCode == VK_LEFT) {


				if (Internal::current_cycle == 0)
				{
					Internal::current_status = Internal::current_status - 1;
					printf("0");
				}
				if (Internal::current_cycle == 1)
				{
					Internal::current_weapon = Internal::current_weapon - 1;
					printf("1");
				}
				if (Internal::current_cycle == 2)
				{
					Internal::current_scopes = Internal::current_scopes - 1;
					printf("2");

				}
				if (Internal::current_cycle == 3)
				{
					Internal::current_barrel = Internal::current_barrel - 1;
					printf("3");
				}
			}


			if (Internal::current_cycle == 0)
			{
				Internal::R_1 = 47;
				Internal::G_1 = 47;
				Internal::B_1 = 47;

				Internal::R_2 = 23;
				Internal::G_2 = 23;
				Internal::B_2 = 23;

				Internal::R_3 = 23;
				Internal::G_3 = 23;
				Internal::B_3 = 23;

				Internal::R_4 = 23;
				Internal::G_4 = 23;
				Internal::B_4 = 23;
			}
			if (Internal::current_cycle == 1)
			{
				Internal::R_1 = 23;
				Internal::G_1 = 23;
				Internal::B_1 = 23;

				Internal::R_2 = 47;
				Internal::G_2 = 47;
				Internal::B_2 = 47;

				Internal::R_3 = 23;
				Internal::G_3 = 23;
				Internal::B_3 = 23;

				Internal::R_4 = 23;
				Internal::G_4 = 23;
				Internal::B_4 = 23;
			}
			if (Internal::current_cycle == 2)
			{
				Internal::R_1 = 23;
				Internal::G_1 = 23;
				Internal::B_1 = 23;

				Internal::R_2 = 23;
				Internal::G_2 = 23;
				Internal::B_2 = 23;

				Internal::R_3 = 47;
				Internal::G_3 = 47;
				Internal::B_3 = 47;

				Internal::R_4 = 23;
				Internal::G_4 = 23;
				Internal::B_4 = 23;
			}

			if (Internal::current_cycle == 3)
			{
				Internal::R_1 = 23;
				Internal::G_1 = 23;
				Internal::B_1 = 23;

				Internal::R_2 = 23;
				Internal::G_2 = 23;
				Internal::B_2 = 23;

				Internal::R_3 = 23;
				Internal::G_3 = 23;
				Internal::B_3 = 23;

				Internal::R_4 = 47;
				Internal::G_4 = 47;
				Internal::B_4 = 47;
			}


			MARGINS margin = { -1 };
			DwmExtendFrameIntoClientArea(g_hwnd, &margin);

			break;
		}
	}
	return CallNextHookEx(NULL, msg, wParam, lParam);
}

namespace GAPI {
	bool CreateDeviceD3D();
	void CleanupDeviceD3D();
	void ResetDevice();
	LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void MakeWindow(const wchar_t* szWindowTitle,
		const wchar_t* szWindowClass,
		WndProcCallback callback,
		Callback init,
		Callback render,
		bool* pMenuOpen,
		int* pMenuKeyBind
	) {
		g_wndProcCallback = callback;
		g_pMenuOpen = pMenuOpen;
		g_pMenuKeyBind = pMenuKeyBind;

		WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(0), 0, 0, 0, 0, szWindowClass, 0 };
		::RegisterClassEx(&wc);

		auto screenWidth = GetSystemMetrics(SM_CXSCREEN);
		auto screenHeight = GetSystemMetrics(SM_CYSCREEN);

		g_hwnd = ::CreateWindow(wc.lpszClassName, szWindowTitle, WS_POPUP | WS_VISIBLE | WS_EX_TOOLWINDOW, 0, 0, screenWidth, screenHeight, 0, 0, wc.hInstance, 0);

		MARGINS margin = { -1 };
		DwmExtendFrameIntoClientArea(g_hwnd, &margin);

		if (!CreateDeviceD3D()) {
			CleanupDeviceD3D();
			::UnregisterClass(wc.lpszClassName, wc.hInstance);
			Utils::Error("Failed to create D3D device");
			return;
		}

		::ShowWindow(g_hwnd, SW_SHOWDEFAULT);
		::UpdateWindow(g_hwnd);

		std::thread([]() {
			MSG msg;
			while (!GetMessage(&msg, NULL, NULL, NULL)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			}).detach();



			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGui::StyleColorsDark();
			ImGui_ImplWin32_Init(g_hwnd);
			ImGui_ImplDX9_Init(g_pd3dDevice);

			init();

			MSG msg;
			ZeroMemory(&msg, sizeof(msg));
			while (msg.message != WM_QUIT) {
				::SetWindowPos(g_hwnd, HWND_TOPMOST, 0, 0, screenWidth, screenHeight, 0);

				if (::PeekMessage(&msg, 0, 0U, 0U, PM_REMOVE)) {
					::TranslateMessage(&msg);
					::DispatchMessage(&msg);
					continue;
				}

				ImGui_ImplDX9_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();

				render();

				ImGui::EndFrame();
				g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
				g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
				g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

				D3DCOLOR bgScene = D3DCOLOR_RGBA(0, 0, 0, 0);
				g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, bgScene, 1.0f, 0);

				if (g_pd3dDevice->BeginScene() >= 0) {
					ImGui::Render();
					ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
					g_pd3dDevice->EndScene();
				}

				HRESULT result = g_pd3dDevice->Present(0, 0, 0, 0);
				if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
					ResetDevice();
			}

			ImGui_ImplDX9_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();

			CleanupDeviceD3D();
			::DestroyWindow(g_hwnd);
			::UnregisterClass(wc.lpszClassName, wc.hInstance);
	}

	bool CreateDeviceD3D() {
		if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
			return false;

		ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
		g_d3dpp.Windowed = TRUE;
		g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		//g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		g_d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		g_d3dpp.EnableAutoDepthStencil = TRUE;
		g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

		if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
			return false;

		return true;
	}

	void CleanupDeviceD3D() {
		if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = 0; }
		if (g_pD3D) { g_pD3D->Release(); g_pD3D = 0; }
	}

	void ResetDevice() {
		ImGui_ImplDX9_InvalidateDeviceObjects();
		HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
		if (hr == D3DERR_INVALIDCALL)
			IM_ASSERT(0);
		ImGui_ImplDX9_CreateDeviceObjects();
	}

	bool WhilePressed(int virtual_key)
	{
		if (GetAsyncKeyState(virtual_key) & 0x8000) return true;
		return false;
	}
	bool IsPressed(int virtual_key)
	{
		if (GetKeyState(virtual_key) & 0x8000) return true;
		return false;
	}

	LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;

		switch (msg) {
		case WM_SIZE:
			if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED | WS_EX_TOOLWINDOW) {
				g_d3dpp.BackBufferWidth = LOWORD(lParam);
				g_d3dpp.BackBufferHeight = HIWORD(lParam);
				ResetDevice();
			}
			return 0;

		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // disable alt key
				return 0;
			break;

		case WM_DESTROY:
			::PostQuitMessage(0);
			return 0;
		}

		if (g_wndProcCallback(hWnd, msg, wParam, lParam))
			return ::DefWindowProc(hWnd, msg, wParam, lParam);
		return {};
	}

	ImVec2 GetWindowSize() {
		return { (float)g_d3dpp.BackBufferWidth, (float)g_d3dpp.BackBufferHeight };
	}

	void SetWindowSize(const ImVec2& size) {
		g_d3dpp.BackBufferWidth = size.x;
		g_d3dpp.BackBufferHeight = size.y;
	}

	void SetWindowPos(const ImVec2& pos) {
		auto size = GetWindowSize();
		MoveWindow(g_hwnd, pos.x, pos.y, size.x, size.y, FALSE);
	}

	void DragWindow(const ImVec2& dragOffset) {
		RECT rect;
		if (!GetWindowRect(g_hwnd, &rect))
			return;

		ImVec2 newPos = { rect.left + dragOffset.x, rect.top + dragOffset.y };
		SetWindowPos(newPos);
	}

	void EnableInput() {
		SetWindowLong(g_hwnd, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	}

	void DisableInput() {
		SetWindowLong(g_hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	}

	void ZoomRegion(const ImVec2& pos, const ImVec2& size, float zoomFactor) {

	}




	bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height) {
		PDIRECT3DTEXTURE9 texture;
		HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice, filename, &texture);
		if (hr != S_OK)
			return false;

		D3DSURFACE_DESC my_image_desc;
		texture->GetLevelDesc(0, &my_image_desc);
		*out_texture = texture;
		*out_width = (int)my_image_desc.Width;
		*out_height = (int)my_image_desc.Height;
		return true;
	}

	bool LoadTextureFromMemory(void* in_texture, size_t size, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height) {
		PDIRECT3DTEXTURE9 texture;
		HRESULT hr = D3DXCreateTextureFromFileInMemory(g_pd3dDevice, in_texture, size, &texture);
		if (hr != S_OK)
			return false;

		D3DSURFACE_DESC my_image_desc;
		texture->GetLevelDesc(0, &my_image_desc);
		*out_texture = texture;
		*out_width = (int)my_image_desc.Width;
		*out_height = (int)my_image_desc.Height;
		return true;
	}
}

#endif // !GRAPHICS_API
