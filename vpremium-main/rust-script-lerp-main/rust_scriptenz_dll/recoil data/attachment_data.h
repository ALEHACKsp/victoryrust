#pragma once
#include "../pch/pch.h"

enum attachment_types {
    SCOPE_ATTACHMENT,
    MUZZLE_ATTACHMENT,
};

enum scope_types : int {
    INVALID_SCOPE = -1,

    SIMPLE_SCOPE,
    HOLO_SCOPE,
    X8_SCOPE,
    X16_SCOPE,

    // keep NO_SCOPE here :)
    NO_SCOPE,
    SCOPE_COUNT
};

enum muzzle_types : int {
    INVALID_MUZZLE = -1,
    MUZZLE_BREAK,
    MUZZLE_SILENCER,
    MUZZLE_BOOST,

    MUZZLE_COUNT
};

class base_attachment {
public:
    base_attachment( ) { }

    virtual std::string attachment_group_name( ) = 0;
    virtual attachment_types attachment_group( ) = 0;
    virtual int get_type( ) = 0;

    std::string get_name( ) {
        return m_name;
    }

    bool modifies_recoil( ) {
        return m_modifies_recoil;
    }

    float get_recoil_factor( ) {
        return m_recoil_factor;
    }

    uint8_t* m_sound;
protected:


    int m_type;
    bool m_modifies_recoil;
    float m_recoil_factor;
    std::string m_name;
};



class scope_attachment: public base_attachment {
public:
    scope_attachment( ) { };

    scope_attachment( std::string name, uint8_t* sound, float recoil_factor, int type, float zoom_factor) {
        m_name = name;
        m_modifies_recoil = false;
        m_type = type;
        m_sound = sound;

        m_zoom_factor = zoom_factor;
        m_recoil_factor = recoil_factor;

        if ( recoil_factor != 1.f )
            m_modifies_recoil = true;
    }

    std::string attachment_group_name( ) override {
        return std::string( "SCOPE" );
    }

    attachment_types attachment_group( ) override {
        return SCOPE_ATTACHMENT;
    }

    int get_type( ) override {
        return m_type;
    }

    float get_zoom_factor( ) {
        return m_zoom_factor;
    }

private:

    float m_zoom_factor;
};

class muzzle_attachment: public base_attachment {
public:
    muzzle_attachment( ) { }

    muzzle_attachment( std::string name, uint8_t* sound, float recoil_factor, int type, float firerate_factor = 1.f ) {
        m_name = name;
        m_modifies_recoil = false;
        m_modifies_firerate = false;
        m_type = type;
        m_sound = sound;

        m_recoil_factor = recoil_factor;
        m_firerate_factor = firerate_factor;

        if ( recoil_factor != 1.f )
            m_modifies_recoil = true;

        if ( firerate_factor != 1.f )
            m_modifies_firerate = true;
    }

    std::string attachment_group_name( ) override {
        return std::string("MUZZLE");
    }

    attachment_types attachment_group( ) override {
        return MUZZLE_ATTACHMENT;
    }

    int get_type( ) override {
        return m_type;
    }

    bool modifies_firerate( ) {
        return m_modifies_firerate;
    }

    float get_firerate_factor( ) {
        return m_firerate_factor;
    }

private:

    bool m_modifies_firerate;
    float m_firerate_factor;
};