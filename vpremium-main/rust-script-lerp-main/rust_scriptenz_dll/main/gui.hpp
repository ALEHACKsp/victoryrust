#include "../pch/pch.h"
#include "../core/graphics_api.hpp"
#include "internal.hpp"
#include "../config settings/config.h"
#include "../core/config.hpp"

#include "../widgets/fonts.hpp"

#include "imgui_internal.h"
#include "imgui.h"
#include "internal.hpp"
#include "../font.h"
#include "../API.h"
#include "previews.h"
#include <Psapi.h>


static char str0[128] = "";
static char str1[128] = "";


static bool loggedin = true;
static bool isLogged = true;
static bool isGrouped = true;
static bool isHwidded = true;
static bool isDavinci = true;
static bool asagikaydir = false;
bool randomxy_active = false;

bool rememberme = false;

int menus = 0;


static int buttonflag = 0;


bool g_toggledInput = true;
bool g_toggledInput_mini = true;
bool g_toggledInput_start = true;
bool g_toggledInput_ok = true;
static int i = 300;


IDirect3DTexture9* kullanicifoto;
IDirect3DTexture9* ak47w;
IDirect3DTexture9* lr300w;
IDirect3DTexture9* mp5w;
IDirect3DTexture9* thompsonw;
IDirect3DTexture9* customsmgw;
IDirect3DTexture9* m249w;
IDirect3DTexture9* semiw;
IDirect3DTexture9* pythonw;
IDirect3DTexture9* m39w;
IDirect3DTexture9* m92w;
IDirect3DTexture9* revolverw;
IDirect3DTexture9* semipistolw;
IDirect3DTexture9* gradbar;


inline void click_keys()// W
{
    keybd_event(0x57, 0, 0, 0);
    keybd_event(0x57, 0, KEYEVENTF_KEYUP, 0);
}

inline void click_keyss()// S
{
    keybd_event(0x53, 0, 0, 0);
    keybd_event(0x53, 0, KEYEVENTF_KEYUP, 0);
}

inline void click_keysss()// A
{
    keybd_event(0x41, 0, 0, 0);
    keybd_event(0x41, 0, KEYEVENTF_KEYUP, 0);
}

inline void click_keyssss()// D
{
    keybd_event(0x44, 0, 0, 0);
    keybd_event(0x44, 0, KEYEVENTF_KEYUP, 0);
}


struct ImageTex {
    std::string m_name;
    PDIRECT3DTEXTURE9 m_texture;
    int m_width;
    int m_height;
};

std::vector<ImageTex> g_weapon_i;
std::vector<ImageTex> g_scopes_i;
std::vector<ImageTex> g_barrel_i;


ImageTex* g_weapon = nullptr;
ImageTex* g_scopes = nullptr;
ImageTex* g_barrel = nullptr;

bool recoil_toggle = false;


bool tab_1 = true;
bool tab_2 = false;
bool tab_3 = false;
bool tab_4 = false;

int R_1 = 63;
int G_1 = 63;
int B_1 = 63;

int R_2 = 41;
int G_2 = 41;
int B_2 = 41;

int R_3 = 41;
int G_3 = 41;
int B_3 = 41;

int R_4 = 41;
int G_4 = 41;
int B_4 = 41;



int R_1_first = 73;
int G_1_first = 73;
int B_1_first = 73;

int R_2_first = 28;
int G_2_first = 28;
int B_2_first = 28;

int R_3_first = 28;
int G_3_first = 28;
int B_3_first = 28;

int R_4_first = 28;
int G_4_first = 28;
int B_4_first = 28;



int code_key = 0;

int code_1 = 0;
int code_2 = 0;
int code_3 = 0;
int code_4 = 0;

int code_1_key = 0x30;
int code_2_key = 0x30;
int code_3_key = 0x30;
int code_4_key = 0x30;

int largeKey = 0;
int smallKey = 0;

int smallfurn = 0;
int largefurn = 0;

bool smallfurn_T = false;
bool largefurn_T = false;

const char* code_1_text = "0";
const char* code_2_text = "0";
const char* code_3_text = "0";
const char* code_4_text = "0";


//bool crosshair_draw = false;


void largeFurnace() {
    SetCursorPos(695, 500);
    Sleep(100);
    // first slot
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1390, 540);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(20);
    SetCursorPos(698, 500);
    Sleep(100);
    // first slot done
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1485, 540);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(20);
    SetCursorPos(701, 500);
    Sleep(100);
    //second slot done
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1575, 540);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(20);
    SetCursorPos(704, 500);
    Sleep(100);
    //third slot done
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1670, 540);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(20);
    SetCursorPos(708, 500);
    Sleep(100);
    //fourth slot done
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1765, 540);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(20);
    SetCursorPos(712, 500);
    Sleep(100);
    //Fifth slot done
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1300, 630);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(20);
    SetCursorPos(718, 500);
    Sleep(100);
    //Sixth slot
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1390, 630);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(20);
    SetCursorPos(725, 500);
    Sleep(100);
    //Seventh Slot
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1485, 630);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(20);
    SetCursorPos(734, 500);
    Sleep(100);
    //second slot done
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1575, 630);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(20);
    SetCursorPos(746, 500);
    Sleep(100);
    //third slot done
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1670, 630);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(20);
    SetCursorPos(762, 500);
    Sleep(100);
    //fourth slot done
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1765, 630);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(20);
    SetCursorPos(786, 500);
    Sleep(100);
    //Fifth slot done
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1300, 720);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(20);
    SetCursorPos(829, 500);
    Sleep(100);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1485, 720);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(20);
    SetCursorPos(912, 500);
    Sleep(100);
    //second slot done
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1575, 720);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(20);
    SetCursorPos(707, 616);
    Sleep(100);
    //third slot done
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1670, 720);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
void smallFurnace() {



    SetCursorPos(826, 500);
    Sleep(100);

    // first slot
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(20);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1380, 700);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    // first slot done

    Sleep(50);
    SetCursorPos(1200, 500);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1450, 700);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

    Sleep(200);
    SetCursorPos(1150, 500);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(200);
    SetCursorPos(1200, 500);
    Sleep(200);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(30);
    SetCursorPos(1615, 700);
    Sleep(50);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);



}

BOOL CALLBACK evaluate_window(HWND hwnd, LPARAM param)
{
    DWORD pid = 0;
    DWORD tid = GetWindowThreadProcessId(hwnd, &pid);

    HANDLE phandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (phandle == NULL)
        return TRUE;

    char basenameRaw[256] = { 0 };
    GetModuleBaseNameA(phandle, NULL, basenameRaw, 256);

    CloseHandle(phandle);

    std::string basename = basenameRaw;
    if (basename != "Spotify.exe")
        return TRUE;

    char textRaw[256] = { 0 };
    GetWindowTextA(hwnd, textRaw, 256);

    std::string text = textRaw;
    if (text == "" || text == "GDI+ Window" || text == "MSCTFIME UI")
        return TRUE;

    std::vector<std::string>* titles = (std::vector<std::string> *)(param);
    titles->push_back(text);

    return TRUE;
}

std::string spotify_title()
{
    std::vector<std::string> titles;
    EnumWindows(evaluate_window, (LPARAM)(&titles));

    // Song title likely to be longest.
    std::sort(titles.begin(), titles.end(), [](std::string a, std::string b) {
        return a.size() < b.size();
        });
    std::reverse(titles.begin(), titles.end());

    if (titles.size() > 0)
        return titles[0];
    else return "";
}



namespace cypher
{
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

    bool SubTab(const char* label, const ImVec2& size_arg, const bool selected)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;
        static float sizeplus = 0.f;
        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);
        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ImGui::ItemSize(size, style.FramePadding.y);
        if (!ImGui::ItemAdd(bb, id))
            return false;
        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, 0);
        window->DrawList->AddRectFilledMultiColor(bb.Min, bb.Max, ImColor(35, 35, 35, 255), ImColor(35, 35, 35, 255), ImColor(30, 30, 30, 255), ImColor(30, 30, 30, 255));
        if (!selected) {
            if (hovered) {
                window->DrawList->AddRectFilledMultiColor(bb.Min, bb.Max, ImColor(40, 40, 40, 255), ImColor(40, 40, 40, 255), ImColor(40, 40, 40, 255), ImColor(40, 40, 40, 255));
            }
        }
       
        window->DrawList->AddText({ bb.Min.x + size_arg.x / 2 - ImGui::CalcTextSize(label).x / 2,bb.Min.y + size_arg.y / 2 - ImGui::CalcTextSize(label).y / 2 }, ImColor(225 / 255.f, 225 / 255.f, 225 / 255.f, 255.f / 255.f), label);
        ImDrawList* draw = ImGui::GetWindowDrawList();
        return pressed;
    }

    ImFont* boldPoppin;
    ImFont* XXMediumPoppin;
    ImFont* mediumPoppin;
    ImFont* lightPoppin;

    void InitUI() {
        ImGuiStyle& s = ImGui::GetStyle();
        ImGuiIO& io = ImGui::GetIO();
        if (ak47w == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, ak47b, sizeof(ak47b), 212, 212, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &ak47w);

        if (lr300w == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, lr300b, sizeof(lr300b), 212, 212, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &lr300w);

        if (mp5w == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, mp5b, sizeof(mp5b), 212, 212, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &mp5w);


        if (thompsonw == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, thompsonb, sizeof(thompsonb), 212, 212, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &thompsonw);

        if (semipistolw == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, semipistolb, sizeof(semipistolb), 212, 212, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &semipistolw);

        if (revolverw == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, revolverb, sizeof(revolverb), 212, 212, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &revolverw);

        if (m92w == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, m92b, sizeof(m92b), 212, 212, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &m92w);
        if (customsmgw == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, customsmgb, sizeof(customsmgb), 212, 212, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &customsmgw);

        if (m249w == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, m249b, sizeof(m249b), 212, 212, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &m249w);

        if (semiw == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, seminew, sizeof(seminew), 212, 212, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &semiw);

        if (pythonw == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, pythonb, sizeof(pythonb), 212, 212, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &pythonw);

        if (m39w == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, m39b, sizeof(m39b), 212, 212, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &m39w);

        if (gradbar == nullptr)
            D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, gradientbars, sizeof(gradientbars), 500, 4, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &gradbar);
         boldPoppin = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(MySemi_compressed_data, MySemi_compressed_size, 70.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic()); //yazik kafama ayni anda farkettik DWQKQWKDQW 
        XXMediumPoppin = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(MyMedi_compressed_data, MyMedi_compressed_size, 25.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
         mediumPoppin = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(MyMedi_compressed_data, MyMedi_compressed_size, 18.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
         lightPoppin = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(MyMedi_compressed_data, MyMedi_compressed_size, 14.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    }


    bool WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        return 1;
    }
    
    void RenderUI()
    {
        Internal::activation();
        Internal::Style();
        POINT mPos;
        GetCursorPos(&mPos);
        ImGuiWindowFlags flags = 0;
        auto pos = ImGui::GetWindowPos();
        auto size = ImGui::GetWindowSize();
        bool isHovering = mPos.x >= pos.x && mPos.y >= pos.y && mPos.x <= (pos.x + size.x) && mPos.y <= (pos.y + size.y);

        if (GetAsyncKeyState(smallKey) != 0)
        {
            smallFurnace();
        }
        if (GetAsyncKeyState(largeKey) != 0)
        {
            largeFurnace();
        }


        if (GetAsyncKeyState(code_key))
        {

            INPUT ip;
            ip.type = INPUT_KEYBOARD;
            ip.ki.wScan = 0; // hardware scan code for key
            ip.ki.time = 0;
            ip.ki.dwExtraInfo = 0;

            ip.ki.wVk = code_1_key;
            ip.ki.dwFlags = 0;
            SendInput(1, &ip, sizeof(INPUT));
            ip.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &ip, sizeof(INPUT));


            ip.ki.wVk = code_2_key;
            ip.ki.dwFlags = 0;
            SendInput(1, &ip, sizeof(INPUT));
            ip.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &ip, sizeof(INPUT));


            ip.ki.wVk = code_3_key;
            ip.ki.dwFlags = 0;
            SendInput(1, &ip, sizeof(INPUT));
            ip.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &ip, sizeof(INPUT));


            ip.ki.wVk = code_4_key;
            ip.ki.dwFlags = 0;
            SendInput(1, &ip, sizeof(INPUT));
            ip.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &ip, sizeof(INPUT));

            Sleep(500);
        }

        if (Internal::crosshair_toggle) {
            ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(GAPI::GetWindowSize().x / 2 + Internal::gap + 1, GAPI::GetWindowSize().y / 2 - 1), ImVec2(GAPI::GetWindowSize().x / 2 + Internal::length + Internal::gap + 1, GAPI::GetWindowSize().y / 2 + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(col1[0], col1[1], col1[2], col1[3])));
            ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(GAPI::GetWindowSize().x / 2 - Internal::gap - 1, GAPI::GetWindowSize().y / 2 + 1), ImVec2(GAPI::GetWindowSize().x / 2 - Internal::length - Internal::gap - 1, GAPI::GetWindowSize().y / 2 - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(col1[0], col1[1], col1[2], col1[3])));
            ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(GAPI::GetWindowSize().x / 2 - 1, GAPI::GetWindowSize().y / 2 + Internal::gap + 1), ImVec2(GAPI::GetWindowSize().x / 2 + 1, GAPI::GetWindowSize().y / 2 + Internal::length + Internal::gap + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(col1[0], col1[1], col1[2], col1[3])));
            ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(GAPI::GetWindowSize().x / 2 + 1, GAPI::GetWindowSize().y / 2 - Internal::gap - 1), ImVec2(GAPI::GetWindowSize().x / 2 - 1, GAPI::GetWindowSize().y / 2 - Internal::length - Internal::gap - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(col1[0], col1[1], col1[2], col1[3])));
        }
       
        if (weaps)
        {
            HWND hwnd = FindWindowA(0, "riplegend");
            ::SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
            ::ShowWindow(hwnd, SW_NORMAL);
            ImGui::SetNextWindowPos(ImVec2(Internal::screen_rect.left + 8, Internal::screen_rect.top + 8)); //kalima gelmedi öyle koydum degisirz
            ImGui::SetNextWindowSize(ImVec2{ 305, 30 });
            if (ImGui::Begin("riplegend", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse))
            {
                ImGui::PushFont(mediumPoppin);
                ImGui::Image(gradbar, ImVec2(330, 4));
                ImGui::SetCursorPosX(15);
                ImGui::SetCursorPosY(8);
                ImGui::Text(Internal::Weapon.c_str());
                ImGui::SameLine(); //Y
                ImGui::SetCursorPosX(125);
                ImGui::Text(Internal::Scope.c_str());
                ImGui::SameLine(); //Y
                ImGui::SetCursorPosX(225);
                ImGui::Text(Internal::Barrel.c_str());
                ImGui::SameLine(); //Y
                ImGui::PopFont();




            }
            ImGui::End();



        }

        if (GetAsyncKeyState(antiafkkeybind1) & 1)
        {
            antiafk = true;
        }

        if (antiafk)
        {
            if (GetAsyncKeyState(antiafkkeybind) & 1)
            {
                antiafk = false;
            }
            Sleep(33);
            click_keys(); // W
            Sleep(33); //aslinda gerek yokdu ama sonradan cözdüm
            click_keyss(); // S
            Sleep(33);
            click_keysss(); // A	
            Sleep(33);
            click_keyssss(); // D	
            Sleep(33);
            click_keys(); // W
            Sleep(33); //aslinda gerek yokdu ama sonradan cözdüm
            click_keyss(); // S
            Sleep(33);
            click_keysss(); // A	
            Sleep(33);
            click_keyssss(); // D	
            Sleep(33);
            click_keys(); // W
            Sleep(33); //aslinda gerek yokdu ama sonradan cözdüm
            click_keyss(); // S
            Sleep(33);
            click_keysss(); // A	
            Sleep(33);
            click_keyssss(); // D	
            Sleep(33);
            click_keys(); // W
            Sleep(33); //aslinda gerek yokdu ama sonradan cözdüm
            click_keyss(); // S
            Sleep(33);
            click_keysss(); // A	
            Sleep(33);
            click_keyssss(); // D	
            Sleep(33);
            click_keys(); // W
            Sleep(33); //aslinda gerek yokdu ama sonradan cözdüm
            click_keyss(); // S
            Sleep(33);
            click_keysss(); // A	
            Sleep(33);
            click_keyssss(); // D	
            Sleep(33);
            click_keys(); // W
            Sleep(33); //aslinda gerek yokdu ama sonradan cözdüm
            click_keyss(); // S
            Sleep(33);
            click_keysss(); // A	
            Sleep(33);
            click_keyssss(); // D	
            Sleep(33);
            click_keys(); // W
            Sleep(33); //aslinda gerek yokdu ama sonradan cözdüm
            click_keyss(); // S
            Sleep(33);
            click_keysss(); // A	
            Sleep(33);
            click_keyssss(); // D	
            Sleep(33);
            click_keys(); // W
            Sleep(33); //aslinda gerek yokdu ama sonradan cözdüm
            click_keyss(); // S
            Sleep(33);
            click_keysss(); // A	
            Sleep(33);
            click_keyssss(); // D	
            Sleep(33);
            click_keys(); // W
            Sleep(33); //aslinda gerek yokdu ama sonradan cözdüm
            click_keyss(); // S
            Sleep(33);
            click_keysss(); // A	
            Sleep(33);
            click_keyssss(); // D	
            Sleep(33);
            click_keys(); // W
            Sleep(33); //aslinda gerek yokdu ama sonradan cözdüm
            click_keyss(); // S
            Sleep(33);
            click_keysss(); // A	
            Sleep(33);
            click_keyssss(); // D	
            Sleep(33);
            click_keys(); // W
            Sleep(33); //aslinda gerek yokdu ama sonradan cözdüm
            click_keyss(); // S
            Sleep(33);
            click_keysss(); // A	
            Sleep(33);
            click_keyssss(); // D	
        }


        if (spotifyyy)
        {   
            HWND hwnds = FindWindowA(0, "spotifyy");
            ::SetWindowPos(hwnds, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
            ::ShowWindow(hwnds, SW_NORMAL);
            ImGui::SetNextWindowPos(ImVec2(Internal::screen_rect.right - 408, Internal::screen_rect.top + 8)); //kalima gelmedi öyle koydum degisirz
            ImGui::SetNextWindowSize(ImVec2{ 410, 30 });
            if (ImGui::Begin("spotifyy", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse))
            {
                
                ImGui::PushFont(mediumPoppin);
                ImGui::Image(gradbar, ImVec2(410, 4));

                if (ImGui::CustomButton("Prev", "##BUTTON56", ImVec2(30, 20), false, mediumPoppin, ""))
                {
                    INPUT ip;


                    ip.type = INPUT_KEYBOARD;
                    ip.ki.wScan = 0;
                    ip.ki.time = 0;
                    ip.ki.dwExtraInfo = 0;

                    ip.ki.wVk = 0xB1; //VK_MEDIA_PREV_TRACK previous

                    ip.ki.dwFlags = 0;
                    SendInput(1, &ip, sizeof(INPUT));

                    ip.ki.dwFlags = KEYEVENTF_KEYUP;
                    SendInput(1, &ip, sizeof(INPUT));

                }
                ImGui::SameLine();
                ImGui::SetCursorPosX(35);
                ImGui::Text("Current Playing: ");
                ImGui::SameLine();
                auto title = spotify_title();
                puts(title.c_str());
                ImGui::Text(spotify_title().c_str());
                ImGui::SameLine();
                if (ImGui::Button("Next", ImVec2(30, 20)))
                {
                    INPUT ipss;


                    //Advertisement
                    //Default IME

                    ipss.type = INPUT_KEYBOARD;
                    ipss.ki.wScan = 0;
                    ipss.ki.time = 0;
                    ipss.ki.dwExtraInfo = 0;

                    ipss.ki.wVk = 0xB0; //VK_MEDIA_NEXT_TRACK

                    ipss.ki.dwFlags = 0;
                    SendInput(1, &ipss, sizeof(INPUT));

                    ipss.ki.dwFlags = KEYEVENTF_KEYUP;
                    SendInput(1, &ipss, sizeof(INPUT));
                }
                

                ImGui::PopFont();


            }
            ImGui::End();
            //sülalece alicaklar aynen spotify oldu demi yapiyoruz beraber
        }

        if (GetAsyncKeyState(rapids) & 0x8000)
        {

            if (bRapidf == true) {

                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                Sleep(75);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                Sleep(75);

            }
            else {

            }

        }

        if (Internal::g_open )
        {

            ImGuiWindowFlags GUI_flags = 0;
            GUI_flags |= ImGuiWindowFlags_NoSavedSettings;
            GUI_flags |= ImGuiWindowFlags_NoCollapse;
            GUI_flags |= ImGuiWindowFlags_NoNav;
            GUI_flags |= ImGuiWindowFlags_NoResize;
            GUI_flags |= ImGuiWindowFlags_NoTitleBar;
            GUI_flags |= ImGuiWindowFlags_NoScrollbar;
            GUI_flags |= ImGuiWindowFlags_NoScrollWithMouse;

            ImGui::SetNextWindowSize(ImVec2(370, i));
            ImGui::Begin("$$$", (bool*)1, GUI_flags);
            {

                const auto wnd = ImGui::GetCurrentWindowRead();
                auto ws = wnd->Size;
                auto wp = wnd->Pos;
                auto poss = ImGui::GetWindowPos();
                auto size = ImGui::GetWindowSize();
                bool isHovering = mPos.x >= poss.x && mPos.y >= poss.y && mPos.x <= (poss.x + size.x) && mPos.y <= (poss.y + size.y);
                if (!g_toggledInput_mini && isHovering) {
                    GAPI::EnableInput();
                    g_toggledInput_mini = true;
                    printf("input enabled\n");
                }
                else if (g_toggledInput_mini && !isHovering) {
                    GAPI::DisableInput();
                    g_toggledInput_mini = false;
                    printf("input disabled\n");
                }
                
                ImGuiStyle* styles = &ImGui::GetStyle();
                ImVec4* colors = styles->Colors;

                ImGui::BeginChild("##topGradient", ImVec2(370, 121));
                {
                    ImGui::GetCurrentWindow()->DrawList->AddRectFilled(ImVec2(0, ImGui::GetWindowPos().y), ImVec2(ImGui::GetWindowPos().x + 370, ImGui::GetWindowPos().y + 121), ImGui::GetColorU32(ImVec4{ 46.f / 255.f,43.f / 255.f,51.f / 255.f,1.f }));
                    ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y + 121), ImVec2(ImGui::GetWindowPos().x + 370, ImGui::GetWindowPos().y + 124), ImGui::GetColorU32(ImVec4{ 126.f / 255.f, 131.f / 255.f, 219.f / 255.f, 1.f }));
                    ImGui::PushFont(boldPoppin);
                    ImGui::RenderText(ImVec2(ImGui::GetWindowPos().x + 82, ImGui::GetWindowPos().y + 27), "VICTORY");
                    ImGui::PopFont();
                    colors[ImGuiCol_Text] = ImColor(111, 105, 112, 255);
                    ImGui::PushFont(lightPoppin);
                    ImGui::RenderText(ImVec2(ImGui::GetWindowPos().x + 130, ImGui::GetWindowPos().y + 80), "vPremium Next GEN v1.0");
                    ImGui::PopFont();
                    colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);

                    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 121, ImGui::GetCursorPosY() + 96));
                    ImGui::PushFont(XXMediumPoppin);
                    if (loggedin)
                    {
                        ImGui::SetCursorPosX(55); //senimi kircam
                        if (ImGui::TopButton("Main", buttonflag == 0 ? true : false))buttonflag = 0; ImGui::SameLine();
                        if (ImGui::TopButton("Settings", buttonflag == 1 ? true : false))buttonflag = 1; ImGui::SameLine();
                        if (ImGui::TopButton("Config", buttonflag == 2 ? true : false))buttonflag = 2;  ImGui::SameLine();
                        if (ImGui::TopButton("Helpers", buttonflag == 3 ? true : false))buttonflag = 3;


                    }
                    else
                    {
                        ImGui::SetCursorPosX(160);

                        if (ImGui::TopButton("Login", buttonflag == 4 ? true : false))buttonflag = 4; ImGui::SameLine();

                    }


                    ImGui::PopFont();

                }
                ImGui::EndChild();
               
				ImGui::PushFont(mediumPoppin);


                ImGuiStyle& style = ImGui::GetStyle();

                if (loggedin && isHwidded && isGrouped && isLogged && isDavinci)
                {
                    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 10, ImGui::GetCursorPosY() + ImGui::GetFontSize()));
                    ImGui::BeginGroup();


                    switch (buttonflag)
                    {
                    case 0:
                    {










                        colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
                        ImGui::Checkbox("Weapon Preview", &preview); ImGui::SameLine();
                        ImGui::SetCursorPosX(300);
                        ImGui::Text(Internal::Weapon.c_str());
                        ImGui::Checkbox("Sounds", &Internal::Sounds_toggle); ImGui::SameLine();
                        ImGui::SetCursorPosX(300);
                        ImGui::Text(Internal::Scope.c_str());
                        


                            //yapariz onlari kanka



                            //bugfix


                        ImGui::Checkbox("Rapid Fire", &bRapidf); ImGui::SameLine();
                        style.FrameRounding = 4;
                        ImGui::KeyBind("##rapid", rapids, ImVec2(80, 20)); ImGui::SameLine();

                        ImGui::SetCursorPosX(300);
                        ImGui::Text(Internal::Barrel.c_str());
                        ImGui::SetCursorPosX(15);
                        ImGui::Text("Menu Key = INSERT"); ImGui::SameLine();
                        ImGui::SameLine();
                        ImGui::SetCursorPosX(210);
                        ImGui::Text("HipFire = "); ImGui::SameLine();
                        ImGui::KeyBind("##hipp", hippp, ImVec2(80, 20)); //dogru burasi


                        if (hippp)
                        {
                            Internal::hipfire_toggle = !Internal::hipfire_toggle;
                        }

                        




                        if (preview)
                        {
                            ImGui::SetNextWindowSize(ImVec2{ 220, 220 });
                            ImGui::SetNextWindowBgAlpha(0.f);



                            HWND hwwnd = FindWindowA(0, "nbaa");

                           

                            if (ImGui::Begin("nbaa##window", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse))
                            {
                                if (Internal::Weapon == "NONE")
                                {

                                }
                                if (Internal::Weapon == "AK-47")
                                {
                                    ImGui::Image(ak47w, ImVec2(212, 212));
                                }
                                if (Internal::Weapon == "LR-300")
                                {
                                    ImGui::Image(lr300w, ImVec2(212, 212));
                                }
                                if (Internal::Weapon == "MP5")
                                {
                                    ImGui::Image(mp5w, ImVec2(212, 212));
                                }
                                if (Internal::Weapon == "C-SMG")
                                {
                                    ImGui::Image(customsmgw, ImVec2(212, 212));
                                }
                                if (Internal::Weapon == "Thompson")
                                {
                                    ImGui::Image(thompsonw, ImVec2(212, 212));
                                }
                                if (Internal::Weapon == "Python")
                                {
                                    ImGui::Image(pythonw, ImVec2(212, 212));
                                }
                                if (Internal::Weapon == "SEMI")
                                {
                                    ImGui::Image(semiw, ImVec2(212, 212));
                                }
                                if (Internal::Weapon == "M249")
                                {
                                    ImGui::Image(m249w, ImVec2(212, 212));
                                }
                                if (Internal::Weapon == "M39")
                                {
                                    ImGui::Image(m39w, ImVec2(212, 212));
                                }
                                //revolver
                               
                                //semi pistol
                                if (Internal::Weapon == "SAP")
                                {
                                    ImGui::Image(semipistolw, ImVec2(212, 212));
                                }
                                //m92
                                if (Internal::Weapon == "M92")
                                {
                                    ImGui::Image(m92w, ImVec2(212, 212));
                                }

                            }
                            ImGui::End();
                        }

                     



                        ImGui::PushItemWidth(200);
                        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
                        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2);
                        //	ImGui::SetCursorPosX(ImGui::GetCursorPosX());

                        int dsa = ImGui::GetStateStorage()->GetInt(ImGui::GetID("Attachments"));

                        int asd = ImGui::GetStateStorage()->GetInt(ImGui::GetID("Weapons"));

                        if (asd == 0)
                        {
                            //ImGui::Text("Header kapali");
                            i = 300;
                            asagikaydir = false;

                        }
                        else if (asd == 1)
                        {
                            asagikaydir = true;
                            //ImGui::Text("Header Acik");
                            if (dsa == 1)
                            {
                                static int sd = 140;
                                i = 400 + sd;

                            }
                            else
                            {
                                i = 450;
                            }

                        }

                        //Attachments

                        if (dsa == 1)
                        {
                            if (asd == 0)
                            {
                                //weapons kapaliysa
                                i = 360;
                            }
                        }
                        //ImGui::Text(std::to_string(i).c_str());


                                //ikiside kapali


                        
                        if (ImGui::CollapsingHeader("Weapons", ImGuiTreeNodeFlags_FramePadding))
                        {

                            style.FrameRounding = 4;

                            //izninle biraz düzenli yapicam hrkanka
#pragma  region AK47
                            ImGui::SetCursorPosX(35);
                            ImGui::Text("AK-47");
                            ImGui::SameLine();
                            ImGui::KeyBind("##AK", Internal::bAKKey, ImVec2(90, 20));
                            ImGui::SameLine();
#pragma endregion

#pragma region LR
                            ImGui::SetCursorPosX(190);
                            ImGui::Text("LR-300");
                            ImGui::SameLine();
                            ImGui::KeyBind("##AKf", Internal::bLRKey, ImVec2(90, 20));
#pragma endregion


#pragma region MP5
                            ImGui::SetCursorPosY(375);
                            ImGui::SetCursorPosX(105);

                            ImGui::Text("MP5");
                            ImGui::SetCursorPosY(375);

                            ImGui::SetCursorPosX(145);
                            ImGui::KeyBind("##MP5", Internal::bMP5Key, ImVec2(90, 20));
                            ImGui::SameLine();
#pragma endregion

#pragma region Thomp
                            ImGui::SetCursorPosY(351);

                            ImGui::SetCursorPosX(190);
                            ImGui::Text("Thomp"); //vardi bende
                            ImGui::SameLine();
                            ImGui::KeyBind("##thomp", Internal::bTOMMYKey, ImVec2(90, 20));
#pragma endregion

#pragma region SMG
                            ImGui::SetCursorPosY(279);
                            ImGui::SetCursorPosX(38);

                            ImGui::Text("SMG");
                            ImGui::SetCursorPosY(279);

                            ImGui::SetCursorPosX(84);
                            ImGui::KeyBind("##SMG", Internal::bCUSTOMKey, ImVec2(90, 20));
#pragma endregion

#pragma region Semi

                            ImGui::SetCursorPosY(279);

                            ImGui::SetCursorPosX(200);

                            ImGui::Text("Sar");
                            ImGui::SetCursorPosY(279);

                            ImGui::SetCursorPosX(244);

                            ImGui::KeyBind("##Sar", Internal::bSARKey, ImVec2(90, 20));
#pragma endregion

#pragma region fayton
                            ImGui::SetCursorPosY(303);

                            ImGui::SetCursorPosX(33);
                            ImGui::Text("Python"); //vardi bende
                            ImGui::SetCursorPosY(303);

                            ImGui::SetCursorPosX(84);
                            ImGui::KeyBind("##python", Internal::bPYTHONKey, ImVec2(90, 20));


#pragma endregion


#pragma region M429

                            ImGui::SetCursorPosY(303);

                            ImGui::SetCursorPosX(194);

                            ImGui::Text("M249");
                            ImGui::SetCursorPosY(303);

                            ImGui::SetCursorPosX(244);

                            ImGui::KeyBind("##M249", Internal::bM249Key, ImVec2(90, 20));

#pragma endregion


#pragma region m39
                            ImGui::SetCursorPosY(327);
                            ImGui::SetCursorPosX(38);

                            ImGui::Text("M39");
                            ImGui::SetCursorPosY(327);

                            ImGui::SetCursorPosX(84);
                            ImGui::KeyBind("##M39", Internal::bM39Key, ImVec2(90, 20));


#pragma endregion

#pragma region m92
                            ImGui::SetCursorPosY(327);

                            ImGui::SetCursorPosX(198);

                            ImGui::Text("M92");
                            ImGui::SetCursorPosY(327);

                            ImGui::SetCursorPosX(244);

                            ImGui::KeyBind("##M92", Internal::bM92Key, ImVec2(90, 20));



#pragma  endregion

#pragma region sap
                            ImGui::SetCursorPosY(351);
                            ImGui::SetCursorPosX(38);

                            ImGui::Text("Sap");
                            ImGui::SetCursorPosY(351);

                            ImGui::SetCursorPosX(84);
                            ImGui::KeyBind("##sap", Internal::bSAPKey, ImVec2(90, 20));

#pragma endregion



#pragma region  revolver





#pragma endregion

#pragma region activeweapon

#pragma endregion






                        }


                        asagikaydir ? ImGui::SetCursorPosY(420) : ImGui::SetCursorPosY(260);


                        if (ImGui::CollapsingHeader("Attachments", ImGuiTreeNodeFlags_FramePadding))
                        {
#pragma region Holo

                            if (asd == 1)
                            {
                                ImGui::SetCursorPosY(445);

                            }
                            else
                            {
                                ImGui::SetCursorPosY(280);

                            }
                            ImGui::SetCursorPosX(35);
                            ImGui::Text("Holo");

                            if (asd == 1)
                            {
                                ImGui::SetCursorPosY(445);

                            }
                            else
                            {
                                ImGui::SetCursorPosY(280);

                            }

                            ImGui::SetCursorPosX(83);

                            ImGui::KeyBind("##holo", Internal::bHOLOKey, ImVec2(90, 20));
                            ImGui::SameLine();
#pragma endregion

#pragma region Simple
                            ImGui::SetCursorPosX(190);
                            ImGui::Text("Simple");
                            ImGui::SameLine();
                            ImGui::KeyBind("##simple", Internal::bSIMPLEKey, ImVec2(90, 20));


#pragma endregion


#pragma region 8x
                            if (asd == 1)
                            {
                                ImGui::SetCursorPosY(468);
                                ImGui::SetCursorPosX(41);

                                ImGui::Text("8X");
                                ImGui::SetCursorPosY(468);

                                ImGui::SetCursorPosX(83);
                                ImGui::KeyBind("##8x", Internal::b8XKey, ImVec2(90, 20));
                                ImGui::SameLine();
                            }
                            else
                            {
                                ImGui::SetCursorPosY(306);
                                ImGui::SetCursorPosX(41);

                                ImGui::Text("8X");
                                ImGui::SetCursorPosY(306);

                                ImGui::SetCursorPosX(83);
                                ImGui::KeyBind("##8x", Internal::b8XKey, ImVec2(90, 20));
                                ImGui::SameLine();
                            }


#pragma endregion

#pragma region 16x

                            if (asd == 1)
                            {
                                ImGui::SetCursorPosY(468);
                                ImGui::SetCursorPosX(190);

                                ImGui::Text("16X");
                                ImGui::SetCursorPosY(468);

                                ImGui::SetCursorPosX(243);
                                ImGui::KeyBind("##16x", Internal::b16XKey, ImVec2(90, 20));
                                ImGui::SameLine();
                            }
                            else
                            {
                                ImGui::SetCursorPosY(306);
                                ImGui::SetCursorPosX(200);

                                ImGui::Text("16X");
                                ImGui::SetCursorPosY(306);

                                ImGui::SetCursorPosX(243);
                                ImGui::KeyBind("##16x", Internal::b16XKey, ImVec2(90, 20));
                                ImGui::SameLine();
                            }


#pragma endregion

#pragma region silence
                            if (asd == 1)
                            {
                                ImGui::SetCursorPosY(491);
                                ImGui::SetCursorPosX(30);

                                ImGui::Text("Silence");
                                ImGui::SetCursorPosY(491);

                                ImGui::SetCursorPosX(83);
                                ImGui::KeyBind("##silence", Internal::bSILENCERKey, ImVec2(90, 20));
                                ImGui::SameLine();
                            }
                            else
                            {
                                ImGui::SetCursorPosY(331);
                                ImGui::SetCursorPosX(30);

                                ImGui::Text("Silence");
                                ImGui::SetCursorPosY(331);

                                ImGui::SetCursorPosX(83);
                                ImGui::KeyBind("##silence", Internal::bSILENCERKey, ImVec2(90, 20));
                                ImGui::SameLine();
                            }


#pragma endregion

#pragma region MuzzleBoost

                            if (asd == 1)
                            {
                                ImGui::SetCursorPosY(491);
                                ImGui::SetCursorPosX(190);

                                ImGui::Text("Boost");
                                ImGui::SetCursorPosY(491);

                                ImGui::SetCursorPosX(243);
                                ImGui::KeyBind("##muzzle", Internal::bBOOSTKey, ImVec2(90, 20));
                                ImGui::SameLine();
                            }
                            else
                            {
                                ImGui::SetCursorPosY(331);
                                ImGui::SetCursorPosX(190);

                                ImGui::Text("Boost");
                                ImGui::SetCursorPosY(331);

                                ImGui::SetCursorPosX(243);
                                ImGui::KeyBind("##muzzle", Internal::bBOOSTKey, ImVec2(90, 20));
                                ImGui::SameLine();
                            }



#pragma endregion
                            /*
                            if (asd == 1)
                            {

                                ImGui::SetCursorPosY(515);


                                ImGui::SetCursorPosX(125);

                                ImGui::Text(Scope.c_str());

                                ImGui::SetCursorPosY(515);


                                ImGui::SetCursorPosX(185);

                                ImGui::Text(Barrel.c_str());

                            }
                            else
                            {
                                ImGui::SetCursorPosY(355);


                                ImGui::SetCursorPosX(125);

                                ImGui::Text(Scope.c_str());

                                ImGui::SetCursorPosY(355);


                                ImGui::SetCursorPosX(185);

                                ImGui::Text(Barrel.c_str());
                            }

                            */




                        }

                        ImGui::PopStyleVar(2);
                        ImGui::PopItemWidth();

                        break;
                    }
                    case 1:
                    {
                        i = 360;
                        settingss->Setup();

                        ImGui::PushItemWidth(310);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
                        ImGui::RenderText(ImVec2(ImGui::GetWindowPos().x + (ImGui::GetContentRegionAvailWidth() / 2 - (ImGui::CalcTextSize("Sensitivity", NULL, true).x / 2)), ImGui::GetWindowPos().y + 140), "Sensitivity");
                        ImGui::Spacing();
                        ImGui::Spacing();
                        ImGui::Spacing();

                        ImGui::GetCurrentWindow()->DrawList->AddLine(ImVec2(ImGui::GetWindowPos().x + 10, ImGui::GetWindowPos().y + 160), ImVec2(ImGui::GetWindowPos().x + 360, ImGui::GetWindowPos().y + 160), ImGui::GetColorU32(ImVec4{ 1.f,1.f ,1.f ,1.f }));
                        ImGui::SetCursorPosX(10);
                        ImGui::SetCursorPosY(145);

                        ImGui::SliderFloat("", &Internal::sensitivity, 0.f, 1.f, "%.3f");

                        /*
                        ImGui::RenderText(ImVec2(ImGui::GetWindowPos().x + (ImGui::GetContentRegionAvailWidth() / 2 - (ImGui::CalcTextSize("Randomization", NULL, true).x / 2)), ImGui::GetWindowPos().y + 190), "Randomization");
                        ImGui::GetCurrentWindow()->DrawList->AddLine(ImVec2(ImGui::GetWindowPos().x + 10, ImGui::GetWindowPos().y + 215), ImVec2(ImGui::GetWindowPos().x + 360, ImGui::GetWindowPos().y + 215), ImGui::GetColorU32(ImVec4{ 1.f,1.f ,1.f ,1.f }));
                        ImGui::NewLine();
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
                        ImGui::Checkbox("Enable/Disable", &ak47);
                        if (ak47)
                        {

                            ImGui::PushItemWidth(240);
                            ImGui::SliderFloat("Randomization X", &xRand, 0.f, 25.f, "%.3f");
                            ImGui::SliderFloat("Randomization Y", &yRand, 0.f, 25.f, "%.3f");
                            ImGui::PopItemWidth();

                        }

                    */


                        std::string HardwareIDFirst = "HWID: ";
                        const char* HardwareIDEnd = ScriptinMekani::GetMachineGUID().c_str();


                        std::string finalHardwareID = HardwareIDFirst.append(HardwareIDEnd);

                        std::string userNameFirst = "Username: ";
                        const char* userNameEnd = str0;
                        std::string finalUserName = userNameFirst.append(userNameEnd);

                        std::string Kalansure = "Product ID: ";
                        const 	char* time = ScriptinMekani::GetProductID().c_str();
                        std::string finalText = Kalansure.append(time);
                        colors[ImGuiCol_Text] = ImColor(0, 255, 0, 255);


                        ImGui::RenderText(ImVec2(ImGui::GetWindowPos().x + (ImGui::GetContentRegionAvailWidth() / 2 - (ImGui::CalcTextSize(finalUserName.c_str(), NULL, true).x / 2)), ImGui::GetWindowPos().y + (randomi ? 190 : 190)), finalUserName.c_str());
                        ImGui::RenderText(ImVec2(ImGui::GetWindowPos().x + (ImGui::GetContentRegionAvailWidth() / 2 - (ImGui::CalcTextSize(finalHardwareID.c_str(), NULL, true).x / 2)), ImGui::GetWindowPos().y + (randomi ? 210 : 210)), finalHardwareID.c_str());
                        ImGui::RenderText(ImVec2(ImGui::GetWindowPos().x + (ImGui::GetContentRegionAvailWidth() / 2 - (ImGui::CalcTextSize(finalText.c_str(), NULL, true).x / 2)), ImGui::GetWindowPos().y + (randomi ? 230 : 230)), finalText.c_str());

                        colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);

                        ImGui::RenderText(ImVec2(ImGui::GetWindowPos().x + (ImGui::GetContentRegionAvailWidth() / 2 - (ImGui::CalcTextSize("Randomization", NULL, true).x / 2)), ImGui::GetWindowPos().y + 255), "Randomization");
                        ImGui::GetCurrentWindow()->DrawList->AddLine(ImVec2(ImGui::GetWindowPos().x + 10, ImGui::GetWindowPos().y + 275), ImVec2(ImGui::GetWindowPos().x + 360, ImGui::GetWindowPos().y + 275), ImGui::GetColorU32(ImVec4{ 1.f,1.f ,1.f ,1.f }));
                        ImGui::SetCursorPosY(280);
                        ImGui::Checkbox("Enable/Disable", &randomi);
                        if (randomi)
                        {
                            randomxy_active = true;
                            if (!smothi)
                            {
                                i = 430;
                            }
                            else
                            {
                                i = 470;
                            }
                            ImGui::PushItemWidth(310);
                            ImGui::SliderFloat("Randomization X", &Internal::inaccuracy_x, 1, 25, "%.2f");
                            ImGui::SliderFloat("Randomization Y", &Internal::inaccuracy_y, 1, 25, "%.2f");
                            ImGui::PopItemWidth();
                        }
                        else
                        {
                            randomxy_active = false;
                            i = 360;
                        }

                        ImGui::RenderText(ImVec2(ImGui::GetWindowPos().x + (ImGui::GetContentRegionAvailWidth() / 2 - (ImGui::CalcTextSize("Smoothing", NULL, true).x / 2)), ImGui::GetWindowPos().y + 300), "Smoothing");
                        ImGui::GetCurrentWindow()->DrawList->AddLine(ImVec2(ImGui::GetWindowPos().x + 10, ImGui::GetWindowPos().y + 320), ImVec2(ImGui::GetWindowPos().x + 360, ImGui::GetWindowPos().y + 320), ImGui::GetColorU32(ImVec4{ 1.f,1.f ,1.f ,1.f }));
                        if (randomi)
                        {
                            ImGui::SetCursorPosY(395);
                        }
                        else
                        { 
                            ImGui::SetCursorPosY(330);
                        }
                        ImGui::Checkbox("Enable/Disable ", &smothi);

                        
                        if (smothi)
                        {
                            if (randomi)
                            {
                                i = 510;
                            }
                            else
                            {
                                i = 450;
                            }
                            ImGui::PushItemWidth(310);
                            ImGui::SliderFloat("Smoothing X", &Internal::control_amount_x, 0, 100, "%.0f");
                            ImGui::SliderFloat("Smoothing Y", &Internal::control_amount_y, 0, 100, "%.0f");
                            ImGui::PopItemWidth();
                        }
                        


                        ImGui::PopItemWidth();



                    }
                    break;
                    case 2:

                        i = 280;
                        settingss->Setup();

                        ImGui::PushItemWidth(310);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
                        ImGui::RenderText(ImVec2(ImGui::GetWindowPos().x + (ImGui::GetContentRegionAvailWidth() / 2 - (ImGui::CalcTextSize("Config", NULL, true).x / 2)), ImGui::GetWindowPos().y + 140), "Config");
                        ImGui::Spacing();
                        ImGui::Spacing();
                        ImGui::Spacing();

                        ImGui::GetCurrentWindow()->DrawList->AddLine(ImVec2(ImGui::GetWindowPos().x + 10, ImGui::GetWindowPos().y + 160), ImVec2(ImGui::GetWindowPos().x + 360, ImGui::GetWindowPos().y + 160), ImGui::GetColorU32(ImVec4{ 1.f,1.f ,1.f ,1.f }));


                        ImGui::RenderText(ImVec2(ImGui::GetWindowPos().x + (ImGui::GetContentRegionAvailWidth() / 2 - (ImGui::CalcTextSize("Field Of View", NULL, true).x / 2)), ImGui::GetWindowPos().y + 220), "Field Of View");
                        ImGui::GetCurrentWindow()->DrawList->AddLine(ImVec2(ImGui::GetWindowPos().x + 10, ImGui::GetWindowPos().y + 240), ImVec2(ImGui::GetWindowPos().x + 360, ImGui::GetWindowPos().y + 240), ImGui::GetColorU32(ImVec4{ 1.f,1.f ,1.f ,1.f }));
                        ImGui::SetCursorPosY(230);
                        ImGui::PushItemWidth(310);
                        ImGui::SliderFloat("##s", &Internal::fov, 70, 90, "%.1f");
                        ImGui::PopItemWidth();

                        ImGui::SetCursorPosY(170);

                        ImGui::SetCursorPosX(135); //senimi kircam
                        if (ImGui::CustomButton("Save", "##BUTTON5", ImVec2(90, 20), false, mediumPoppin, ""))
                        {
                            //	settings->saveconfigg = true;
                            section = 2;
                            settingss->SaveConfig();
                            Sleep(2000);
                            section = 0;

                            //settings->saveconfigg = false;

                        }
                        ImGui::SetCursorPosX(135); //senimi kircam
                        if (ImGui::CustomButton("Load", "##BUTTON8", ImVec2(90, 20), false, mediumPoppin, ""))
                        {
                            section = 1;
                            settingss->LoadConfig();
                            Sleep(2000);
                            section = 0;
                        }

                        ImGui::Spacing();
                        ImGui::Spacing();


                        break;
                    case 3:
                        i = 300;
                        ImGui::Checkbox("Crosshair", &crosscheckbox);
                        if (crosscheckbox)
                        {
                            Internal::crosshair_toggle = true;
                            i = 445;
                            ImGui::PushItemWidth(135); //aynen
                            ImGui::ColorPicker3("Color", col1);
                            ImGui::PopItemWidth();
                        }
                        else
                        {
                            Internal::crosshair_toggle = false;
                        }

                        //kanka hipfire felan diyordun onlari zoom sorun ya sorun ne bilyiormusun bak anlatiyim #include <mangetifier> diye birsey var bu normalde calisiyor ama d3d9 ekleyince tak hata verior debug olmiyor program cok araastirdim bir konu buldum adam akilli o da nuget yap diyor nugetde calisiyor ama dll sorun






                        ImGui::Checkbox("Weapons Panel", &weaps);
                        ImGui::Checkbox("Spotify Panel", &spotifyyy);
                        ImGui::KeyBind(" Anti AFK Panic Key (Click it and wait 3 sec.)", antiafkkeybind, ImVec2(90, 20));
                        ImGui::KeyBind(" Anti AFK Key", antiafkkeybind1, ImVec2(90, 20));


                        break;
                    default:
                        break;
                    }      // Edit bools storing our window open/close state
                    ImGui::NewLine();
                    ImGui::EndGroup();

                }
            }
            ImGui::End();

        }    

    }





}