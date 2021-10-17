#pragma once
#include "../pch/pch.h"
#include "../recoil data/weapon_data.h"
#include "../recoil data/attachment_data.h"


struct settings_t {
    settings_t() {
        active_weapon = INVALID_WEAPON;
        active_scope = INVALID_SCOPE;
        active_muzzle = INVALID_MUZZLE;
        enabled = true;
        hipfire;
    }

    // internal settings
    int active_weapon = INVALID_WEAPON;
    int active_scope = INVALID_SCOPE;
    int active_muzzle = INVALID_MUZZLE;

    bool enabled = true;
    bool hipfire;

    //  'script' settings
    int cycle_gun_fw = VK_F22;
    int cycle_gun_bk = VK_F22;

    int cycle_scope_fw = VK_F22;
    int cycle_scope_bk = VK_F22;




    int cycle_muzzle_fw = VK_F22;
    int cycle_muzzle_bk = VK_F22;



    // game settings


    int fire_key = VK_LBUTTON;
    int aim_key = VK_RBUTTON;

    int duck_key = VK_LCONTROL;
    int forward = 'W';
    int back = 'S';
    int left = 'A';
    int right = 'D';

    int inventory_key = VK_TAB;
    int crafting_key = 'Q';
    int console_key = VK_F1;
};