#pragma once
#include "../pch/pch.h"
#include "unity_keynames.h"
#include "settings.h"

enum convar_types {
	KEYBIND_CVAR,
	INT_CVAR,
	FLOAT_CVAR
};

struct convar_t {
	convar_t( std::string name, int type, int* key ) {
		m_name = name;
		m_val.n = key;
		m_type = type;
	}

	convar_t( std::string name, int type, float* f ) {
		m_name = name;
		m_val.f = f;
		m_type = type;
	}

	std::string m_name;
	union {
		int* n;
		float* f;
	} m_val;

	int m_type;

};

class config {
public:
	config( settings_t* settings );
	config( ) {};

	void read_cfgs( );
	void read_game_cfgs( );

	std::string m_path_to_game_cfg;
	std::string m_path_to_local_cfg;
private:
	bool read_local_cfg( );
	bool read_game_cfg( );
	bool read_game_keys( );

	settings_t* m_settings;

	std::vector<convar_t> m_cfg_cvars;
	std::vector<convar_t> m_game_keybinds;
	std::vector<convar_t> m_game_cfg;
};