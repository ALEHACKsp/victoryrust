#pragma once

#include "../pch/pch.h"
#include "../core/graphics_api.hpp"
#include "../config settings/config.h"
#include "../core/config.hpp"

#include "../widgets/fonts.hpp"

#include "imgui_internal.h"
#include "imgui.h"



namespace Internal
{
    ImFont* main_font;
    ImFont* group_font;
    ImFont* second_font;
    ImFont* third_font;
    ImFont* minus_;

    bool g_open = true;
    bool g_start_window = true;

    bool& Sounds_toggle = Config::Add("Sounds", "nulled", Config::Type::BOOL, true);
    bool& hipfire_toggle = Config::Add("hipfire", "nulled", Config::Type::BOOL, false);
    bool& crosshair_toggle = Config::Add("crosshair", "nulled", Config::Type::BOOL, false);
    bool& blatent_mode = Config::Add("blatent", "nulled", Config::Type::BOOL, true);
   // bool& code_enable = Config::Add("code enable", "nulled", Config::Type::BOOL, false);
    bool& g_mini = Config::Add("mini menu", "nulled", Config::Type::BOOL, true);

    std::string Weapon = "Weapon", Scope = "Scope", Barrel = "Barrel", Sounds = "ON", HipFire = "OFF";


    int& bAKKey = Config::Add("AK_Keybind", "nulled", Config::Type::INT, 0);
    int& bLRKey = Config::Add("LR_Keybind", "nulled", Config::Type::INT, 0);
    int& bMP5Key = Config::Add("MP5_Keybind", "nulled", Config::Type::INT, 0);
    int& bTOMMYKey = Config::Add("TOMMY_Keybind", "nulled", Config::Type::INT, 0);
    int& bCUSTOMKey = Config::Add("CUSTOM_Keybind", "nulled", Config::Type::INT, 0);
    int& bM249Key = Config::Add("M249_Keybind", "nulled", Config::Type::INT, 0);
    int& bSARKey = Config::Add("SAR_Keybind", "nulled", Config::Type::INT, 0);
    int& bSAPKey = Config::Add("SAP_Keybind", "nulled", Config::Type::INT, 0);
    int& bM39Key = Config::Add("M39_Keybind", "nulled", Config::Type::INT, 0);
    int& bM92Key = Config::Add("M92_Keybind", "nulled", Config::Type::INT, 0);
    int& bPYTHONKey = Config::Add("PYTHON_Keybind", "nulled", Config::Type::INT, 0);
    int& bHOLOKey = Config::Add("HOLO_Keybind", "nulled", Config::Type::INT, 0);
    int& b8XKey = Config::Add("8X_Keybind", "nulled", Config::Type::INT, 0);
    int& b16XKey = Config::Add("16X_Keybind", "nulled", Config::Type::INT, 0);
    int& bSIMPLEKey = Config::Add("SIMPLE_Keybind", "nulled", Config::Type::INT, 0);
    int& bSILENCERKey = Config::Add("SILENCER_Keybind", "nulled", Config::Type::INT, 0);
    int& bBOOSTKey = Config::Add("BOOST_Keybind", "nulled", Config::Type::INT, 0);
    int& bBREAKKey = Config::Add("BREAK_Keybind", "nulled", Config::Type::INT, 0);


    float& length = Config::Add("crosshair length", "nulled", Config::Type::FLOAT, 4.0f);
    float& gap = Config::Add("crosshair gap", "nulled", Config::Type::FLOAT, 1.0f);
    float& length_t = Config::Add("crosshair length_t", "nulled", Config::Type::FLOAT, 4.0f);
    float& gap_t = Config::Add("crosshair gap_t", "nulled", Config::Type::FLOAT, 1.0f);
    float& circle_size = Config::Add("crosshair circle size", "nulled", Config::Type::FLOAT, 1.5f);
    float& inaccuracy_x = Config::Add("inaccuracy_x", "nulled", Config::Type::FLOAT, 0.0f);
    float& inaccuracy_y = Config::Add("inaccuracy_x", "nulled", Config::Type::FLOAT, 0.0f);
    float& control_amount_x = Config::Add("control_amount_x", "nulled", Config::Type::FLOAT, 100.0f);
    float& control_amount_y = Config::Add("control_amount_y", "nulled", Config::Type::FLOAT, 100.0f);
    float& border_thickness = Config::Add("border thickness", "nulled", Config::Type::FLOAT, 1.0f);
    float& fov = Config::Add("fov", "nulled", Config::Type::FLOAT, 90.f);
    float& sensitivity = Config::Add("sensitivity", "nulled", Config::Type::FLOAT, 0.4f);
    int& g_menuKeyBind = Config::Add("menu key", "nulled", Config::Type::INT, VK_INSERT);
    int& bcode_key = Config::Add("Code_keybind", "nulled", Config::Type::INT, 0);



    int R = 175;
    int G = 4;
    int B = 4;

    float sway = 0;
    float rainbow;
    float speed = 5;
    float smoothing = 0;
    RECT screen_rect;
    int bar_transparency = 255;
    int tab = 1;
    bool rust_active = false;


    bool recoil = true;
    bool count_ammo = false;


    int current_status = 0;
    int current_weapon = 0;
    int current_scopes = 0;
    int current_barrel = 0;

    int binds_tab = 1;
    int binds2_tab = 0;
    int binds3_tab = 0;

    int code_1 = 0;
    int code_2 = 0;
    int code_3 = 0;
    int code_4 = 0;

    bool enabled = true;



    const char* code_1_text = "0";
    const char* code_2_text = "0";
    const char* code_3_text = "0";
    const char* code_4_text = "0";

    const char* weapon_text_button = "none";
    const char* scopes_text_button = "none";
    const char* barrel_text_button = "none";

    const char* binds_tab_text = "weapon binds";
    const char* core_tab_text = "core binds";
    const char* colors_tab_text = "menu color";
    const char* crosshair_text = "cross";


    const char* status_text = "on";
    const char* weapon_text = "none";
    const char* scopes_text = "none";
    const char* barrel_text = "none";


    float status_distance = 100;
    float weapon_distance = 90;
    float scopes_distance = 90;
    float barrel_distance = 90;

    bool disable_wep = false;
    bool disable_scope = false;
    bool disable_barrel = false;


    bool bAKActivate = true;
    bool bLRActivate = false;
    bool bMP5Activate = false;
    bool bTOMMYActivate = false;
    bool bCUSTOMActivate = false;
    bool bSARActivate = false;
    bool bM249Activate = false;
    bool bM39 = false;
    bool bM39Activate = false;
    bool bM92Activate = false;
    bool bSemiPistolActivate = false;
    bool bPythonActivate = false;


    bool bHoloActivate = false;
    bool b8XActivate = false;
    bool b16xActivate = false;
    bool bSimpleActivate = false;


    bool bSilencerActivate = false;
    bool bBoostActivate = false;
    bool bBreakActivate = false;

    int current_cycle = 0;


    int transparency = 255;
    bool g_ok_prompt = false;


    int R_1 = 57;
    int G_1 = 57;
    int B_1 = 57;

    int R_2 = 23;
    int G_2 = 23;
    int B_2 = 23;

    int R_3 = 23;
    int G_3 = 23;
    int B_3 = 23;

    int R_4 = 23;
    int G_4 = 23;
    int B_4 = 23;

    int color_1 = 0;
    int color_2 = 1;
    int color_3 = 0;

    int toggle = 0;

    float stop_recoil = 0.01;
    void wep_reset()
    {
        bAKActivate = false;
        bLRActivate = false;
        bMP5Activate = false;
        bTOMMYActivate = false;
        bCUSTOMActivate = false;
        bSARActivate = false;
        bM249Activate = false;
        bM39 = false;
        bM39Activate = false;
        bM92Activate = false;
        bSemiPistolActivate = false;
        bPythonActivate = false;
    }
    void scope_reset()
    {
        bHoloActivate = false;
        b8XActivate = false;
        b16xActivate = false;
        bSimpleActivate = false;
    }
    void barrel_reset()
    {
        bSilencerActivate = false;
        bBoostActivate = false;
        bBreakActivate = false;
    }

    void sounds()
    {
        if (Sounds_toggle)
        {
            Beep(300, 300);
        }
    }
    void activation()
    {





        if (current_weapon == 0)
        {
            wep_reset();
            disable_wep = true;
            weapon_text_button = "none";
            weapon_text = "none";
            weapon_distance = 90;

        }
        if (current_weapon == 1)
        {
            wep_reset();
            bAKActivate = true;
            disable_wep = false;
            weapon_text_button = "assault rifle";
            weapon_text = "ak47";
            weapon_distance = 90;
        }
        if (current_weapon == 2)
        {
            wep_reset();
            bLRActivate = true;
            disable_wep = false;
            weapon_text_button = "lr-300";
            weapon_text = "lr300";
            weapon_distance = 90;
        }
        if (current_weapon == 3)
        {
            wep_reset();
            bMP5Activate = true;
            disable_wep = false;
            weapon_text_button = "mp5a4";
            weapon_text = "mp5a4";
            weapon_distance = 80;
        }
        if (current_weapon == 4)
        {
            wep_reset();
            bTOMMYActivate = true;
            disable_wep = false;
            weapon_text_button = "thompson";
            weapon_text = "tommy";
            weapon_distance = 80;
        }
        if (current_weapon == 5)
        {
            wep_reset();
            bCUSTOMActivate = true;
            disable_wep = false;
            weapon_text_button = "custom smg";
            weapon_text = "custom";
            weapon_distance = 79;

        }
        if (current_weapon == 6)
        {
            wep_reset();
            bM249Activate = true;
            disable_wep = false;
            weapon_text_button = "m249";
            weapon_text = "m249";
            weapon_distance = 87;
        }
        if (current_weapon == 7)
        {
            wep_reset();
            bSARActivate = true;
            disable_wep = false;
            weapon_text_button = "semi rifle";
            weapon_text = "sar";
            weapon_distance = 97;
        }
        if (current_weapon == 8)
        {
            wep_reset();
            bSemiPistolActivate = true;
            disable_wep = false;
            weapon_text_button = "semi pistol";
            weapon_text = "sap";
            weapon_distance = 97;
        }
        if (current_weapon == 9)
        {
            wep_reset();
            bM39Activate = true;
            disable_wep = false;
            weapon_text_button = "m39";
            weapon_text = "m39";
            weapon_distance = 93;
        }
        if (current_weapon == 10)
        {
            wep_reset();
            bM92Activate = true;
            disable_wep = false;
            weapon_text_button = "m92";
            weapon_text = "m92";
            weapon_distance = 93;
        }
        if (current_weapon == 11)
        {
            wep_reset();
            bPythonActivate = true;
            disable_wep = false;
            weapon_text_button = "python";
            weapon_text = "python";
            weapon_distance = 80;
        }



        if (current_scopes == 0)
        {
            scope_reset();
            disable_scope = true;
            scopes_text_button = "none";
            scopes_text = "none";
            scopes_distance = 90;
        }
        if (current_scopes == 1)
        {
            scope_reset();
            bHoloActivate = true;
            disable_scope = false;
            scopes_text_button = "holo";
            scopes_text = "holo";
            scopes_distance = 93;
        }
        if (current_scopes == 2)
        {
            scope_reset();
            b8XActivate = true;
            disable_scope = false;
            scopes_text_button = "8x";
            scopes_text = "8x";
            scopes_distance = 103;

        }
        if (current_scopes == 3)
        {
            scope_reset();
            b16xActivate = true;
            disable_scope = false;
            scopes_text_button = "16x";
            scopes_text = "16x";
            scopes_distance = 96;

        }
        if (current_scopes == 4)
        {
            scope_reset();
            bSimpleActivate = true;
            disable_scope = false;
            scopes_text_button = "simple";
            scopes_text = "simple";
            scopes_distance = 82;
        }




        if (current_barrel == 0)
        {
            barrel_reset();
            disable_barrel = true;
            barrel_text_button = "none";
            barrel_text = "none";
            barrel_distance = 90;
        }
        if (current_barrel == 1)
        {
            barrel_reset();
            bSilencerActivate = true;
            disable_barrel = false;
            barrel_text_button = "silencer";
            barrel_text = "silencer";
            barrel_distance = 77;
        }
        if (current_barrel == 2)
        {
            barrel_reset();
            bBoostActivate = true;
            disable_barrel = false;
            barrel_text_button = "boost";
            barrel_text = "boost";
            barrel_distance = 87;
        }
        if (current_barrel == 3)
        {
            barrel_reset();
            bBreakActivate = true;
            disable_barrel = false;
            barrel_text_button = "break";
            barrel_text = "break";
            barrel_distance = 87;
        }





    }

    void Style()
    {
        ImGuiStyle* styles = &ImGui::GetStyle();

        ImVec4* colors = styles->Colors;
        styles->Alpha = 1.0f;
        styles->FramePadding = ImVec2(0, 0);
        styles->WindowPadding = ImVec2(0, 0);
        styles->WindowRounding = 0;

        styles->AntiAliasedLines = true;
        colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(41.f / 255.f, 41.f / 255.f, 41.f / 255.f, 1.f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(126.f / 255.f, 131.f / 255.f, 219.f / 255.f, 1.f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(98.f / 255.f, 103.f / 255.f, 210.f / 255.f, 1.f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(126.f / 255.f, 131.f / 255.f, 219.f / 255.f, 1.f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
        //ne hatasi kanka
        colors[ImGuiCol_Header] = ImVec4(126.f / 255.f, 131.f / 255.f, 219.f / 255.f, 1.f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(98.f / 255.f, 103.f / 255.f, 210.f / 255.f, 1.f);
        colors[ImGuiCol_HeaderActive] = ImVec4(126.f / 255.f, 131.f / 255.f, 219.f / 255.f, 1.f);

        colors[ImGuiCol_Separator] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        // colors[ImGuiCol_Tab] = ImLerpS(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.80f);
        colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
        colors[ImGuiCol_TabActive] = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
        colors[ImGuiCol_TabUnfocused] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
        colors[ImGuiCol_TabUnfocusedActive] = ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);

        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    }

}


//new config system
class Settingsss
{
public:


    void Setup();
    void SaveConfig();
    void LoadConfig();
    void SetupS();

private:
    bool CofigExists();
};
extern Settingsss* settingss;
int section = 0;
