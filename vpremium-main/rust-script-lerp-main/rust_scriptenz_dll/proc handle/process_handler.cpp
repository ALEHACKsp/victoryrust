#include "../pch/pch.h"
#include "process_handler.h"
#include "../recoil data/rust_recoil.h"

int low_level_mouse_hook( int code, WPARAM wparam, LPARAM lparam ) {
	auto handler = &g_recoil->m_proc_handler;
	if ( handler->window_active( ) )
		return 0;

	return CallNextHookEx( handler->m_ll_mouse_hk, code, wparam, lparam );
}

void set_hook_and_block( ) {
	auto handler = &g_recoil->m_proc_handler;

	if ( handler->m_ll_mouse_hk )
		UnhookWindowsHookEx( handler->m_ll_mouse_hk );

	handler->m_ll_mouse_hk = SetWindowsHookEx( WH_MOUSE_LL, (HOOKPROC)low_level_mouse_hook, GetModuleHandleA( nullptr ), 0 );

	tagMSG msg;
	BOOL res;

	// GetMessageA here will block and make sure out process gets all messages
	do {
		res = GetMessageA( &msg, 0, 0, 0 );
	} while ( res && !g_recoil->m_shutdown );
}

process_handler::process_handler( std::string window_name ) {
	m_window_name = window_name;
	m_exectuable_dir = std::string();

	m_ll_mouse_hk = 0;
	m_windows_hook_thread = 0;
	m_pid = 0;

	m_was_active = false;
	m_window_active = false;
}

void process_handler::update( ) {
	DWORD max_path = MAX_PATH;

	char title[ 128 ];
	char exe_path[ MAX_PATH ];
	auto wnd = GetForegroundWindow( );
	GetWindowTextA( wnd, title, 128 );

	if ( !m_window_name.compare( title ) ) {
		m_window_active = true;

		if ( !m_was_active ) {
			uint32_t pid;
			GetWindowThreadProcessId( wnd, (LPDWORD)&pid );
			
			// check if the process changed and get the name filepath and replace our WindowsHook in the chain
			if ( pid != m_pid ) {
				m_pid = pid;

				HANDLE h = OpenProcess( PROCESS_QUERY_LIMITED_INFORMATION, FALSE, m_pid );

				QueryFullProcessImageNameA( h, 0, exe_path, &max_path );

				std::filesystem::path path;
				try {
					path = std::filesystem::path( exe_path );
					path.remove_filename( );
				}
				catch ( ... ) {
					//DEVMSG( "Filesystem path threw execpt\n" );
				}


				DEVMSG( "Found executable filepath %s\n", path.string().c_str() );

				m_exectuable_dir = path.string( );

				CloseHandle( h );

				// set the path to the games cfg folder
				g_recoil->m_cfg->m_path_to_game_cfg = m_exectuable_dir + ("/cfg/");
				g_recoil->m_cfg->read_game_cfgs( );

				// now (re)place the WindowsHook in the hook chain 
				//place_windows_hook( );
			}
		}
		
		m_was_active = true;
	}
	else {
		m_window_active = false;
		m_was_active = false;
	}
}

bool process_handler::window_active( ) {
	return m_window_active;
}

void process_handler::place_windows_hook( ) {
	// GetMessageA will be blocking target thread and we can't signal it, just forcefully kill it.
	if ( m_windows_hook_thread )
		TerminateThread( m_windows_hook_thread, 0 ); 

	m_windows_hook_thread = CreateThread( nullptr, 0, ( LPTHREAD_START_ROUTINE )set_hook_and_block, nullptr, 0, nullptr );
}