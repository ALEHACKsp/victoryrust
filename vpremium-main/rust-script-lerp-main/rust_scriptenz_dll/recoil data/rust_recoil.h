#pragma once
#include "../pch/pch.h"
#include "../Mouse control/mouse_controller.h"
#include "../input/inputsystem.h"
#include "../recoil data/weapon_data.h"
#include "../recoil data/attachment_data.h"

#include "../utils/utils.h"
#include "../utils/utils.hpp"

#include "../config settings/settings.h"
#include "../config settings/unity_keynames.h"
#include "../config settings/config.h"

#include "../proc handle/process_handler.h"

enum menu_states {
    IN_CONSOLE = ( 1 << 0 ),
    IN_INVENTORY = ( 1 << 1 ),
    IN_ESCAPE = ( 1 << 2 ),
    IN_CRAFTING = ( 1 << 3 )
};

// the axis returned from "Unity.Input.GetAxis" per pixel of mouse move
#define AXIS_PER_PIXEL 0.05f
extern HANDLE thrd;

void input_loop( );
// main class of the "script"
class rust_recoil {
public:
    ~rust_recoil();
    rust_recoil( std::string path );
   


    void recoil_loop( );

    void init_inputsystem( );

    void cycle_gun( bool fw );
    void cycle_scope( bool fw );
    void cycle_muzzle ( bool fw );

    process_handler m_proc_handler;

    // inputsystem callbacks needs these
    bool m_shutdown;
    bool m_refresh_cfg;
    config* m_cfg;
    settings_t* m_settings;
private:
    bool is_firing( scope_attachment*& scope );
    bool is_geforce_now_active( );

    void add_inaccuracy( vec2& recoil );
    float calc_recoil_time( vec2 recoil );

    weapon_data_container* get_weapon( );
    scope_attachment* get_scope( );
    muzzle_attachment* get_muzzle( );

    void apply_attachments(weapon_data_container* weapon, scope_attachment* scope, muzzle_attachment* muzzle);

    vec2 angles_to_pixels( vec2 angles );

    int32_t m_shots_fired;
    std::chrono::time_point<std::chrono::steady_clock> m_last_fired;

    float m_recoil_modifier;
    float m_fov;

    mouse_controller* m_mouse;
    inputsystem* m_input;

    std::array<weapon_data_container, WEAPON_COUNT> m_weapons;
    std::array<scope_attachment, SCOPE_COUNT> m_scopes;
    std::array<muzzle_attachment, MUZZLE_COUNT> m_muzzles;
};

extern rust_recoil* g_recoil;