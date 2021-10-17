#pragma once

#ifndef UTILS_HPP
#define UTILS_HPP

#include <Windows.h>

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <algorithm>

#pragma comment(lib, "urlmon.lib")
#include <urlmon.h>


#include <random>
#include <Lmcons.h>


#include "Shlobj.h"
#include "Shlobj_core.h"

#define DIRECTINPUT_VERSION 0x0800
#include <d3d9.h>
#include <dinput.h>

#include "../DirectX9/Include/d3dx9tex.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx9.h"
#include "../ImGui/imgui_impl_win32.h"

extern LPDIRECT3D9 g_pD3D;
extern LPDIRECT3DTEXTURE9 g_pLogoTexture;
extern LPDIRECT3DDEVICE9 g_pd3dDevice;
extern D3DPRESENT_PARAMETERS g_d3dpp;
extern HWND g_hwnd;

extern ImFont* g_fontXsm;
extern ImFont* g_fontSm;
extern ImFont* g_fontMd;
extern ImFont* g_fontLg;

typedef bool (*t_Login)();
typedef bool (*t_Logout)();
typedef char* (*t_Status)();
typedef char* (*t_Username)();
typedef char* (*t_Modules)();
typedef bool (*t_Inject)(char* moduleName, bool __ignore);

extern t_Login Login;
extern t_Logout Logout;
extern t_Status GetStatus;
extern t_Username GetUsername;
extern t_Modules GetModules;
extern t_Inject Inject;

extern bool g_loggedIn;

namespace Utils {
	void Shout(std::string_view message, std::string_view title, bool exit = false);

	ImVec2 GetWindowSize();

	std::vector<std::string> SplitString(std::string str, std::string_view delimiter);
}

#endif // !UTILS_HPP
