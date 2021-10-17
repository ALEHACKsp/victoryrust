#pragma once
#include "../pch/pch.h"

int low_level_mouse_hook( int code, WPARAM wparam, LPARAM lparam );
void set_hook_and_block( );

class process_handler {
public:
	process_handler( ) {};
 	process_handler( std::string window_name );

	void update( );
	bool window_active( );

	HHOOK m_ll_mouse_hk;
	std::string m_exectuable_dir;

private:
	void place_windows_hook( );

	std::string m_window_name;

	HANDLE m_windows_hook_thread;

	uint32_t m_pid;

	bool m_was_active;
	bool m_window_active;

};