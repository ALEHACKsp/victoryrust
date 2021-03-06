#pragma once
#include "../pch/pch.h"

/*
    General input-system using the system KeyStates instead of something like WndProc since
    this way does not require a WndProc which can be easily detected - and additionally this works regardless if the application's window has focus or not.
    Because of that fact this is definitely want you want for a user-mode keylogger. For game-cheating purposes the GetKeyState-variant calls can be replaced
    with reads to the games own inputsystem, and with that evade any attempts to detect the malicious code by logging/intercepting the syscall ( Get(Async)KeyState calls into kernel with the ntdll functions NtUserGetAsyncKeyState or NtUserGetKeyState )
    a problem to keep in mind is if the game in question has its input-system layed out in a different way than the WIN-API way, in that cause you'd have to make a translation table yourself (which is quite annoying, but no way around it)
*/

#define NUM_KEYS 0xFF

// my own keystate flags used for checking which status a key has
enum keystate_t {
    HELD = 1 << 0,
    PRESSED = 1 << 1,
    RELEASED = 1 << 2,
    TOGGLED = 1 << 3,
};

struct key_callback_t {
    key_callback_t( const int32_t key_code, const keystate_t state, std::function<void()> callback ) {
        m_key_code = key_code;
        m_on_state = state;
        m_callback = callback;
    }

    int32_t m_key_code;
    keystate_t m_on_state;
    std::function<void( )> m_callback;
};

class inputsystem {
public:
    inputsystem( );

    void reset( );

    // add/remove checked keys
    void add_key( const int32_t key_code );
    void remove_key( const int32_t key_code );

    void process_callbacks( );
    void add_callback( const int32_t key_code, const keystate_t state, std::function<void( )> callback );
    void remove_callbacks( const int32_t key_code );

    // loops through all the keys and sets the button states - needs to be called at start of frame or loop to get the states for current iteration
    void update_keystates( );

    // returns the status of the keystate of the supplied VK-code
    bool get_state( const int32_t key_code, const keystate_t state );

    // translates keypress to the actual character (taking into account special characters)
    std::wstring get_character( const int32_t key_code );

private:
    // sets the state of a key based on the supplied key state
    void handle_key_state( const int32_t key_code, const bool down, const bool key_repeat = false );

    // keyboard states
    BYTE m_button_states[ 0xFF ];

    // key press callbacks
    std::vector<key_callback_t> m_key_callbacks;

    // buttons to check for the the KeyState loop.
    std::vector<int32_t> m_checked_buttons;
};