#include "../pch/pch.h"
#include "../recoil data/rust_recoil.h"
#include "../core/graphics_api.hpp"
#include "internal.hpp"
#include "../utils/utils.h"
#include "../widgets/widgets.hpp"
#include "../config settings/config.h"
#include "gui.hpp"

#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h>
#include <urlmon.h>
#include "wtypes.h"
#include <DXGIType.h>
#pragma comment (lib, "windowscodecs.lib")

Settingsss* settingss = new Settingsss();


namespace Utils {
    void Error(const std::string& s) {
        printf("[ERROR] %s\n", s.c_str());
        throw std::runtime_error(s);
    }
    bool EndsWith(const std::string& haystack, const std::string& needle) {
        if (haystack.length() >= needle.length())
            return (!haystack.compare(haystack.length() - needle.length(), needle.length(), needle));
        return false;
    }
    std::vector<std::string> GetFilesInDirectory(const char* directory) {
        std::vector<std::string> files;
        std::filesystem::path path = directory;

        if (!std::filesystem::is_directory(path))
            return files;

        for (const auto& entry : std::filesystem::directory_iterator(directory))
            if (entry.is_regular_file())
                files.push_back(entry.path().string());
        return files;
    }
    std::vector<std::string> SplitString(std::string str, const char* delimiter) {
        std::vector<std::string> tokens;
        const auto delLen = strlen(delimiter);
        size_t pos = 0;
        while ((pos = str.find(delimiter)) != std::string::npos) {
            tokens.push_back(str.substr(0, pos));
            str.erase(0, pos + delLen);
        }
        tokens.push_back(str);
        return tokens;
    }
    std::string GetFormattedTime() {
        time_t rawtime;
        tm timeinfo = {};
        char buffer[80];
        time(&rawtime);
        localtime_s(&timeinfo, &rawtime);
        auto suffix = timeinfo.tm_hour >= 12 ? " PM" : " AM";
        if (timeinfo.tm_hour > 12)
            timeinfo.tm_hour -= 12;
        strftime(buffer, sizeof(buffer), "%H:%M", &timeinfo);
        return std::string(buffer) + suffix;
    }
}
config::config(settings_t* settings) {
    m_settings = settings;
    m_path_to_game_cfg = std::string();
    m_cfg_cvars.clear();
    m_game_keybinds.clear();
    m_game_cfg.clear();
    m_cfg_cvars.push_back(convar_t(("next_gun="), KEYBIND_CVAR, &settings->cycle_gun_fw));
    m_cfg_cvars.push_back(convar_t(("prev_gun="), KEYBIND_CVAR, &settings->cycle_gun_bk));
    m_cfg_cvars.push_back(convar_t(("next_scope="), KEYBIND_CVAR, &settings->cycle_scope_fw));
    m_cfg_cvars.push_back(convar_t(("prev_scope="), KEYBIND_CVAR, &settings->cycle_scope_bk));
    m_cfg_cvars.push_back(convar_t(("next_muzzle="), KEYBIND_CVAR, &settings->cycle_muzzle_fw));
    m_cfg_cvars.push_back(convar_t(("prev_muzzle="), KEYBIND_CVAR, &settings->cycle_muzzle_bk));
    m_game_keybinds.push_back(convar_t(("\"inventory.toggle\""), KEYBIND_CVAR, &settings->inventory_key));
    m_game_keybinds.push_back(convar_t(("\"inventory.togglecrafting\""), KEYBIND_CVAR, &settings->crafting_key));
    m_game_keybinds.push_back(convar_t(("consoletoggle"), KEYBIND_CVAR, &settings->console_key));
    m_game_keybinds.push_back(convar_t(("\"+attack\""), KEYBIND_CVAR, &settings->fire_key));
    m_game_keybinds.push_back(convar_t(("\"+attack2\""), KEYBIND_CVAR, &settings->aim_key));
    m_game_keybinds.push_back(convar_t(("\"+duck\""), KEYBIND_CVAR, &settings->duck_key));
    m_game_keybinds.push_back(convar_t(("\"+forward\""), KEYBIND_CVAR, &settings->forward));
    m_game_keybinds.push_back(convar_t(("\"+backward\""), KEYBIND_CVAR, &settings->back));
    m_game_keybinds.push_back(convar_t(("\"+left\""), KEYBIND_CVAR, &settings->left));
    m_game_keybinds.push_back(convar_t(("\"+right\""), KEYBIND_CVAR, &settings->right));
    m_game_cfg.push_back(convar_t(("graphics.fov \""), FLOAT_CVAR, &Internal::fov));
    m_game_cfg.push_back(convar_t(("input.sensitivity \""), FLOAT_CVAR, &Internal::sensitivity));
}

void config::read_cfgs() {
    if (!read_local_cfg()) {
        return;
    }
    if (m_path_to_game_cfg.length() > 0)
        read_game_cfgs();
}
void config::read_game_cfgs() {
    if (!read_game_cfg()) {
        return;
    }
    if (!read_game_keys()) {
        return;
    }
}
bool config::read_local_cfg() {
    bool ok = true;
    try {
        std::string line;
        std::string tok;
        std::ifstream file(m_path_to_local_cfg);

        while (std::getline(file, line)) {
            for (auto& it : m_cfg_cvars) {
                if (line.find(it.m_name) != std::string::npos) {
                    std::string sub = line.substr(it.m_name.length());

                    if (it.m_type == KEYBIND_CVAR) {
                        if (unity_key_to_vk.find(sub) == unity_key_to_vk.end()) {
                            ok = false;
                            continue;
                        }
                        *it.m_val.n = unity_key_to_vk[sub];
                        continue;
                    }
                    if (it.m_type == FLOAT_CVAR) {
                        *it.m_val.f = std::stof(sub);
                        continue;
                    }
                    if (it.m_type == INT_CVAR) {
                        *it.m_val.n = std::stoi(sub);
                        continue;
                    }
                }
            }
        }
    }
    catch (...) {
        return false;
    }
    return ok;
}
bool config::read_game_cfg() {
    try {
        std::string line;
        std::ifstream file(m_path_to_game_cfg + ("client.cfg"));

        while (std::getline(file, line)) {

            for (auto& it : m_game_cfg) {
                if (line.find(it.m_name) != std::string::npos) {
                    size_t name_len = it.m_name.length();
                    auto val_end = line.find("\"", name_len);
                    std::string val = line.substr(name_len, val_end - name_len);
                    if (it.m_type == FLOAT_CVAR) {
                        *it.m_val.f = std::stof(val);
                        DEVMSG("[%s] = %s\n", it.m_name.c_str(), val.c_str());
                        continue;
                    }
                }
            }
        }
    }
    catch (...) {
        return false;
    }
    return true;
}
bool config::read_game_keys() {
    try {
        std::string line;
        std::ifstream file(m_path_to_game_cfg + ("keys.cfg"));

        while (std::getline(file, line)) {
            for (auto& it : m_game_keybinds) {
                if (line.find(it.m_name) != std::string::npos) {
                    auto key_end = line.find(" ", 5);
                    auto sub = line.substr(5, key_end - 5);

                    if (unity_key_to_vk.find(sub) == unity_key_to_vk.end())
                        return false;

                    *it.m_val.n = unity_key_to_vk[sub];
                    DEVMSG("[%s] = %s\n", it.m_name.c_str(), sub.c_str());
                    continue;
                }
            }

        }
    }
    catch (...) {
        return false;
    }

    return true;
}
#define _DLL
#ifdef _DLL
#define STR(str) ""
#else
#define STR(str) str
#endif
rust_recoil* g_recoil = nullptr;
HANDLE thrd = 0;
rust_recoil::~rust_recoil() {
    if (m_cfg)
        delete m_cfg;
    if (m_input)
        delete m_input;
    if (m_settings)
        delete m_settings;
    if (m_mouse)
        delete m_mouse;
}


rust_recoil::rust_recoil(std::string local_cfg) {
    srand(time(nullptr));
    m_weapons[AK47] = weapon_data_container(("AK47"), NULL, 133.3f, 30, 1.666667f, g_ak47_recoil);
    m_weapons[CUSTOM_SMG] = weapon_data_container(("CUSTOM_SMG"), NULL, 100.f, 24, 1.363636f, g_custom_smg_recoil);
    m_weapons[LR300] = weapon_data_container(("LR300"), NULL, 120.f, 30, 1.666667f, g_lr300_recoil);
    m_weapons[THOMPSON] = weapon_data_container(("THOMPSON"), NULL, 130.f, 20, 1.363636f, g_thompson_recoil);
    m_weapons[MP5] = weapon_data_container(("MP5"), NULL, 100.f, 30, 1.666667f, g_mp5_recoil);
    m_weapons[M249] = weapon_data_container(("M249"), NULL, 120.f, 100, 1.666667f, g_m249_recoil, false, true, 0.5f, 1.25f);
    m_weapons[M39] = weapon_data_container(("M39"), NULL, 200.f, 20, 1.25f, g_m39_recoil, true, true, 0.6f, 0.5f);
    m_weapons[SAR] = weapon_data_container(("SAR"), NULL, 175.f, 16, 1.666667f, g_sar_recoil, true, true, 0.6f, 0.5f);
    m_weapons[M92_PISTOL] = weapon_data_container(("M92_PISTOL"), NULL, 100.f, 15, 1.153846f, g_m92_pistol_recoil, true, true, 0.5f, 0.0f);
    m_weapons[SEMI_PISTOL] = weapon_data_container(("SEMI_PISTOL"), NULL, 150.f, 10, 1.153846f, g_semi_pistol_recoil, true, true, 0.6f, 0.5f);
    m_weapons[PYTHON] = weapon_data_container(("PYTHON"), NULL, 150.f, 6, 1.25f, g_python_recoil, true, true, 0.5f, 0.0f);
    m_scopes[NO_SCOPE] = scope_attachment(("NO SCOPE"), NULL, 1.f, NO_SCOPE, 1.f);
    m_scopes[SIMPLE_SCOPE] = scope_attachment(("SIMPLE SCOPE"), NULL, 1.f, SIMPLE_SCOPE, 1.f);
    m_scopes[HOLO_SCOPE] = scope_attachment(("HOLOGRAPHIC SIGHT"), NULL, 1.f, HOLO_SCOPE, 2.f);
    m_scopes[X8_SCOPE] = scope_attachment(("8X SCOPE"), NULL, 0.8f, X8_SCOPE, 8.f);
    m_scopes[X16_SCOPE] = scope_attachment(("16X SCOPE"), NULL, 0.8f, X16_SCOPE, 16.f);
    m_muzzles[MUZZLE_BREAK] = muzzle_attachment(("MUZZLE BREAK"), NULL, 0.5f, MUZZLE_BREAK);
    m_muzzles[MUZZLE_SILENCER] = muzzle_attachment(("SILENCER"), NULL, 0.8f, MUZZLE_SILENCER);
    m_muzzles[MUZZLE_BOOST] = muzzle_attachment(("MUZZLE BOOST"), NULL, 1.f, MUZZLE_BOOST, 0.9f);
    m_settings = new settings_t();
    m_proc_handler = process_handler(("Rust"));
    // read the configs for settings :)
    m_cfg = new config(m_settings);
    m_cfg->m_path_to_local_cfg = local_cfg;
    m_cfg->read_cfgs();
    m_input = new inputsystem();
    init_inputsystem();
    m_mouse = new mouse_controller();
    m_last_fired = utils::get_time();
    m_shots_fired = 0;
    m_shutdown = false;
}
void rust_recoil::init_inputsystem() {
    m_refresh_cfg = false;
    m_input->reset();
    m_input->add_key(m_settings->fire_key);
    m_input->add_key(m_settings->aim_key);
    m_input->add_key(m_settings->duck_key);
    m_input->add_key(m_settings->forward);
    m_input->add_key(m_settings->back);
    m_input->add_key(m_settings->left);
    m_input->add_key(m_settings->right);
}
void rust_recoil::recoil_loop() {
    bool semi_can_fire = true;
    while (!m_shutdown) {
        Sleep(1);
        m_proc_handler.update();
        m_input->update_keystates();
        m_input->process_callbacks();
        if (m_refresh_cfg)
            init_inputsystem();
        if (!m_proc_handler.window_active() || !Internal::enabled)
            continue;
        auto weapon = get_weapon();
        auto scope = get_scope();
        auto muzzle = get_muzzle();
        if (!weapon)
            continue;
        auto time_since_fired = std::chrono::duration_cast<std::chrono::milliseconds>(utils::get_time() - m_last_fired).count();
        if (time_since_fired > int64_t(weapon->get_firerate(nullptr) * 2.f) && !m_input->get_state(m_settings->fire_key, HELD)) {
            m_shots_fired = 0;
        }
        int32_t cur_salvo = 0;
        auto start = utils::get_time();
        while (is_firing(scope) && m_shots_fired < weapon->get_capacity()) {
            m_last_fired = utils::get_time();
            semi_can_fire = false;
            apply_attachments(weapon, scope, muzzle);
            vec2 recoil = weapon->get_recoil_value(m_shots_fired);
            recoil *= m_recoil_modifier;
            recoil.x *= Internal::control_amount_x * Internal::stop_recoil;
            recoil.y *= Internal::control_amount_y * Internal::stop_recoil;
            add_inaccuracy(recoil);
            m_mouse->lerp_move(angles_to_pixels(recoil), ((weapon->linear_recoil() || Internal::sway) ? int32_t(weapon->get_firerate(muzzle)) : int32_t(calc_recoil_time(recoil))));
            m_shots_fired++;
            cur_salvo++;
            scope = get_scope();
            int64_t wanted_time = int64_t(weapon->get_firerate(muzzle) * 1000.f);
            wanted_time *= cur_salvo;
            utils::accurate_sleep(wanted_time, start);
            m_input->update_keystates();
            m_input->process_callbacks();
        }
        if (!m_input->get_state(m_settings->fire_key, HELD))
            semi_can_fire = true;
    }
}



void rust_recoil::apply_attachments(weapon_data_container* weapon, scope_attachment* scope, muzzle_attachment* muzzle) {
    if (!weapon)
        return;


    m_recoil_modifier = 1.f;
    m_fov = Internal::fov;
    if (scope) {
        if (scope->get_type() == SIMPLE_SCOPE)
            m_fov /= ((weapon->get_ironsights_factor() + 1.f) * 0.5f);
        else
            m_fov /= scope->get_zoom_factor();
        if (scope->modifies_recoil())
            m_recoil_modifier = scope->get_recoil_factor();
    }
    else {
        m_fov /= weapon->get_ironsights_factor();
    }
    if (muzzle && muzzle->modifies_recoil()) {
        if (scope && scope->modifies_recoil()) {
            m_recoil_modifier = (m_recoil_modifier + muzzle->get_recoil_factor()) / 2.f;
        }
        else {
            m_recoil_modifier = muzzle->get_recoil_factor();
        }
    }
    if (weapon->linear_recoil()) {
        bool ducking = m_input->get_state(m_settings->duck_key, HELD);
        if (ducking)
            m_recoil_modifier *= 0.5f;
        if (m_input->get_state(m_settings->aim_key, HELD))
            m_recoil_modifier *= weapon->ads_scale();
        if (m_input->get_state(m_settings->forward, HELD) || m_input->get_state(m_settings->back, HELD) || m_input->get_state(m_settings->left, HELD) || m_input->get_state(m_settings->right, HELD)) {
            float speedscale = ducking ? 0.6 : 1.f;
            m_recoil_modifier *= (1.f + speedscale * weapon->move_penalty());
        }
    }
}
void rust_recoil::add_inaccuracy(vec2& recoil) {
    if (Internal::inaccuracy_x > 0)
    {
        float inacc_scale_y = Internal::inaccuracy_x * 0.001f / 100;
        float x = utils::random_float(-Internal::inaccuracy_x / 100, Internal::inaccuracy_x / 100) / 2;
        recoil.x += recoil.x * x;
    }

    if (Internal::inaccuracy_y > 0)
    {
        float inacc_scale_x = Internal::inaccuracy_y * 0.001f;
        float y = utils::random_float(-Internal::inaccuracy_y / 100, Internal::inaccuracy_y / 100) / 2;
        recoil.y += recoil.y * y;
    }

    if (Internal::inaccuracy_y == 0 && Internal::inaccuracy_x == 0)
    {
        return;
    }
}
float rust_recoil::calc_recoil_time(vec2 recoil) {
    return (recoil.length() / 20.f) * 1000.f;
}
vec2 rust_recoil::angles_to_pixels(vec2 angles) {
    return angles / (AXIS_PER_PIXEL * (Internal::sensitivity * 3.f * (m_fov / 100.f)));
}
bool rust_recoil::is_firing(scope_attachment*& scope) {
    if (m_input->get_state(m_settings->fire_key, HELD)) {
        CURSORINFO info;
        info.cbSize = sizeof(CURSORINFO);
        GetCursorInfo(&info);
        if (info.flags)
            return false;
        if (m_input->get_state(m_settings->aim_key, HELD))
        {
            return true;
        }
        if (m_settings->hipfire) {
            scope = &m_scopes[NO_SCOPE];
            return true;
        }
    }
    return false;
}
weapon_data_container* rust_recoil::get_weapon() {
    if (Internal::bAKActivate == true)
    {
        m_settings->active_weapon = AK47;
    }
    if (Internal::bLRActivate == true)
    {
        m_settings->active_weapon = LR300;
    }
    if (Internal::bMP5Activate == true)
    {
        m_settings->active_weapon = MP5;
    }
    if (Internal::bTOMMYActivate == true)
    {
        m_settings->active_weapon = THOMPSON;
    }
    if (Internal::bCUSTOMActivate == true)
    {
        m_settings->active_weapon = CUSTOM_SMG;
    }
    if (Internal::bSARActivate == true)
    {
        m_settings->active_weapon = SAR;
    }
    if (Internal::bM249Activate == true)
    {
        m_settings->active_weapon = M249;
    }
    if (Internal::bM39Activate == true)
    {
        m_settings->active_weapon = M39;
    }
    if (Internal::bM92Activate == true)
    {
        m_settings->active_weapon = M92_PISTOL;
    }
    if (Internal::bSemiPistolActivate == true)
    {
        m_settings->active_weapon = SEMI_PISTOL;
    }
    if (Internal::bPythonActivate == true)
    {
        m_settings->active_weapon = PYTHON;
    }
    if (Internal::disable_wep == true)
    {
        m_settings->active_weapon = -1;
    }
    if (Internal::hipfire_toggle == true)
    {
        m_settings->hipfire = true;
    }
    if (Internal::hipfire_toggle == false)
    {
        m_settings->hipfire = false;
    }
    if (m_settings->active_weapon == INVALID_WEAPON)
        return nullptr;
    return &m_weapons[m_settings->active_weapon];
}
scope_attachment* rust_recoil::get_scope() {


    if (Internal::bHoloActivate == true)
    {
        Internal::disable_scope == false;
        m_settings->active_scope = HOLO_SCOPE;
    }
    if (Internal::b8XActivate == true)
    {
        Internal::disable_scope == false;
        m_settings->active_scope = X8_SCOPE;
    }
    if (Internal::b16xActivate == true)
    {
        Internal::disable_scope == false;
        m_settings->active_scope = X16_SCOPE;
    }
    if (Internal::bSimpleActivate == true)
    {
        Internal::disable_scope == false;
        m_settings->active_scope = SIMPLE_SCOPE;
    }
    if (Internal::disable_scope == true)
    {
        m_settings->active_scope = -1;
    }
    if (m_settings->active_scope == INVALID_SCOPE)
        return nullptr;

    return &m_scopes[m_settings->active_scope];
}

muzzle_attachment* rust_recoil::get_muzzle() {
    if (Internal::bSilencerActivate == true)
    {
        Internal::disable_barrel == false;
        m_settings->active_muzzle = MUZZLE_SILENCER;
    }
    if (Internal::bBoostActivate == true)
    {
        Internal::disable_barrel == false;
        m_settings->active_muzzle = MUZZLE_BOOST;
    }
    if (Internal::bBreakActivate == true)
    {
        Internal::disable_barrel == false;
        m_settings->active_muzzle = MUZZLE_BREAK;
    }
    if (Internal::disable_barrel == true)
    {
        m_settings->active_muzzle = -1;
    }
    if (m_settings->active_muzzle == INVALID_MUZZLE)
        return nullptr;

    return &m_muzzles[m_settings->active_muzzle];
}
void rust_recoil::cycle_gun(bool fw) {
    fw ? m_settings->active_weapon++ : m_settings->active_weapon--;

    if (m_settings->active_weapon >= WEAPON_COUNT)
        m_settings->active_weapon = INVALID_WEAPON;
    else if (m_settings->active_weapon < INVALID_WEAPON)
        m_settings->active_weapon = WEAPON_COUNT - 1;
    auto weapon = get_weapon();
}
void rust_recoil::cycle_scope(bool fw) {
    fw ? m_settings->active_scope++ : m_settings->active_scope--;
    if (m_settings->active_scope >= NO_SCOPE)
        m_settings->active_scope = INVALID_SCOPE;
    else if (m_settings->active_scope < INVALID_SCOPE)
        m_settings->active_scope = NO_SCOPE - 1;
    auto scope = get_scope();
}
void rust_recoil::cycle_muzzle(bool fw) {
    fw ? m_settings->active_muzzle++ : m_settings->active_muzzle--;
    if (m_settings->active_muzzle >= MUZZLE_COUNT)
        m_settings->active_muzzle = INVALID_MUZZLE;
    else if (m_settings->active_muzzle < INVALID_MUZZLE)
        m_settings->active_muzzle = MUZZLE_COUNT - 1;
    auto muzzle = get_muzzle();
}
void GameThread() {
    char documents[MAX_PATH];
    g_recoil = new rust_recoil(std::string(documents));
    g_recoil->recoil_loop();
}

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


int main(void* mod, uint32_t reason, void* reserved) {
   
    // AllocConsole();
    FreeConsole();
    FILE* _dummy;
  //  freopen_s(&_dummy, "CONOUT$", "w", stdout);

    GetWindowRect(GetDesktopWindow(), &Internal::screen_rect);

    Config::Load();
    HHOOK keyBoard = SetWindowsHookEx(WH_KEYBOARD_LL, GlobalKeyboardHook, NULL, NULL);

    std::thread([]() { GameThread(); }).detach();

    std::string reqqq1 = ScriptinMekani::DownloadString("https://victoryrust.com/api/rand.php");

    wstring wideusername;
    for (int i = 0; i < reqqq1.length(); ++i)
        wideusername += wchar_t(reqqq1[i]);

    const wchar_t* your_result = wideusername.c_str();


    std::string reqqq2 = ScriptinMekani::DownloadString("https://victoryrust.com/api/rand.php");
    
    wstring wideusernames;

    for (int is = 0; is < reqqq2.length(); ++is)
        wideusernames += wchar_t(reqqq2[is]);

    const wchar_t* your_resulta = wideusernames.c_str();


    GAPI::MakeWindow(
        your_result,
        your_resulta,
        cypher::WndProc,
        cypher::InitUI,
        cypher::RenderUI,
        &Internal::g_open,
        &Internal::g_menuKeyBind
    );
       
  
}
