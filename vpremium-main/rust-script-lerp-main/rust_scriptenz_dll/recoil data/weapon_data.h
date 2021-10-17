#pragma once
#include "../pch/pch.h"
#include "recoil_values.h"
#include "attachment_data.h"

enum rust_weapon_id: int {
    INVALID_WEAPON = -1,
    // curves :)
    AK47,
    LR300,
    MP5,
    THOMPSON,
    CUSTOM_SMG,
    M249,
    M39,
    SAR,
    M92_PISTOL,
    SEMI_PISTOL,
    PYTHON,

    WEAPON_COUNT
};

class weapon_data_container {
public:
    weapon_data_container( ) { }
    weapon_data_container( std::string name, uint8_t* sound, float firerate, int32_t capacity, float ironsights, vec2* recoil, bool semi = false, bool linear = false, float ads_scale = 1.f, float move_pen = 0.f) : m_name( name ), m_sound(sound), m_firerate( firerate ), m_capacity( capacity ), m_ironsight_factor( ironsights ), m_recoil_values( recoil ), m_linear_recoil( linear ), m_ads_scale( ads_scale ), m_move_penalty( move_pen ), m_semiauto( semi ) { }

    std::string get_name() {
        return m_name;
    }

    float get_firerate( muzzle_attachment* muzzle ) {
        if ( muzzle && muzzle->modifies_firerate( ) )
            return m_firerate * muzzle->get_firerate_factor( );

        return m_firerate;
    }

    vec2 get_recoil_value( int32_t i ) {
        if ( i >= m_capacity ) {
            DEVMSG( "Requested recoil value %i but capacity is %i\n", i, m_capacity );
            return vec2( );
        }

        if ( m_linear_recoil )
            return -m_recoil_values[ 0 ];
        else
            return -m_recoil_values[ i ];
    }

    int32_t get_capacity( ) {
        return m_capacity;
    }

    float get_ironsights_factor( ) {
        return m_ironsight_factor;
    }

    bool linear_recoil( ) {
        return m_linear_recoil;
    }

    float ads_scale( ) {
        return m_ads_scale;
    }

    float move_penalty( ) {
        return m_move_penalty;
    }

    bool is_semi( ) {
        return m_semiauto;
    }

    uint8_t* m_sound;
private:

    bool m_semiauto;
    bool m_linear_recoil;
    float m_ads_scale;
    float m_move_penalty;

    std::string m_name;
    float m_ironsight_factor;
    float m_firerate;
    int32_t m_capacity;

    vec2* m_recoil_values;
};