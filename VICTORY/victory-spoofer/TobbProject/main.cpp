#include "Utils/Utils.hpp"
#include "Pages/LoginWindow.hpp"
#include "Pages/MainWindow.hpp"
#include "Pages/KeyWindow.hpp"
#include "Fonts/RudaBold.hpp"
#include "Pages/LoadingWindow.hpp"
#include "Bytes/LogoByte.hpp"

LPDIRECT3D9 g_pD3D = 0;
LPDIRECT3DTEXTURE9 g_pLogoTexture = { };
LPDIRECT3DDEVICE9 g_pd3dDevice = 0;
D3DPRESENT_PARAMETERS g_d3dpp = { };
HWND g_hwnd = nullptr;

bool CreateDeviceD3D();
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool g_loggedIn = false;

std::string g_title = "";

ImFont* g_fontXsm = nullptr;
ImFont* g_fontSm = nullptr;
ImFont* g_fontMd = nullptr;
ImFont* g_fontLg = nullptr;

int main() {
	HWND consoleWindow = GetConsoleWindow();

	SetWindowPos(consoleWindow, 0, 5000, 5000, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(0), 0, 0, 0, 0, "c_imgui_menu", 0 };
	::RegisterClassEx(&wc);

	float windowWidth = 400;
	float windowHeight = 300;
	float centerX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
	float centerY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;

	g_hwnd = ::CreateWindowA(wc.lpszClassName, g_title.c_str(), WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, centerX, centerY, windowWidth, windowHeight, 0, 0, wc.hInstance, 0);

	if (!CreateDeviceD3D()) {
		Utils::Shout("CreateDeviceD3D Failed", g_title);
		CleanupDeviceD3D();
		::UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
	}

	::SetWindowLong(g_hwnd, GWL_STYLE, 0);
	::ShowWindow(g_hwnd, SW_SHOWDEFAULT);
	::UpdateWindow(g_hwnd);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(g_hwnd);
	ImGui_ImplDX9_Init(g_pd3dDevice);

	auto fontAtlas = ImGui::GetIO().Fonts;
	g_fontXsm = fontAtlas->AddFontFromMemoryCompressedTTF(rudaBold, rudaBoldSize, 12);
	g_fontSm = fontAtlas->AddFontFromMemoryCompressedTTF(rudaBold, rudaBoldSize, 16);
	g_fontMd = fontAtlas->AddFontFromMemoryCompressedTTF(rudaBold, rudaBoldSize, 24);
	g_fontLg = fontAtlas->AddFontFromMemoryCompressedTTF(rudaBold, rudaBoldSize, 32);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT) {
		if (::PeekMessage(&msg, 0, 0U, 0U, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			continue;
		}

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		KeyWindow::Render();

		ImGui::EndFrame();
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

		D3DCOLOR bgScene = D3DCOLOR_RGBA(255, 255, 255, 255);
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

	return 0;
}

bool CreateDeviceD3D() {
	if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return false;

	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
		return false;

	D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &logo_png, sizeof(logo_png), 500, 250, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &g_pLogoTexture);

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

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg) {
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED) {
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			ResetDevice();
		}
		return 0;

	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;

	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}

	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}