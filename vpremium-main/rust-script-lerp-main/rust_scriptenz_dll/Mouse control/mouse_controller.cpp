#include "../pch/pch.h"
#include "mouse_controller.h"

mouse_controller::mouse_controller( ) {
    reset( );
}

void mouse_controller::reset( ) {
    m_remainder.zero( );
}

void mouse_controller::mouse_move( vec2 relative ) {
    // add the previous remainder to current move
    relative += m_remainder;
    m_remainder.zero( );

    // Integer type vector used for the mouse move
    POINT pt;
    pt.x = relative.x;
    pt.y = relative.y;

    // Calculate the new remainder to use for next move :)
    m_remainder = vec2( relative.x - float( pt.x ), relative.y - float( pt.y ) );

    // only call mouse_event if it will move the mouse
    if ( pt.x || pt.y ) {
        INPUT input;
        input.type = INPUT_MOUSE;
        input.mi.mouseData = 0;
        input.mi.time = 0;
        input.mi.dx = pt.x;
        input.mi.dy = pt.y;
        input.mi.dwFlags = MOUSEEVENTF_MOVE;
        SendInput(1, &input, sizeof(input));
    }
}

// accuracy of about 2ms
void mouse_controller::lerp_move( vec2 relative, int32_t time, int32_t moves ) {
    auto start = std::chrono::high_resolution_clock::now( );

    // only deal with positive numbers, save the sign and then convert to positive
    float signx = relative.x < 0 ? -1.f : 1.f;
    float signy = relative.y < 0 ? -1.f : 1.f;
    relative = vec2( std::fabs( relative.x ), std::fabs( relative.y ) );

    float deltatime = float( time ) / float( moves );
    vec2 delta_move = relative / float( moves );

    vec2 actual_moved = vec2( );

    int32_t cur_move = 0;
    while ( std::chrono::duration_cast< std::chrono::milliseconds >( utils::get_time( ) - start ).count( ) < time - int( std::ceilf( deltatime ) ) && cur_move < moves ) {
        // sanity check to make sure we don't overshoot
        vec2 next_move = actual_moved + delta_move;
        if ( next_move.x > relative.x || next_move.y > relative.y )
            break;

        actual_moved += delta_move;

        mouse_move( vec2( delta_move.x * signx, delta_move.y * signy ) );

        // actively try to fix our "time" by calculating how long to sleep until we reach it.
        int wanted_time = int( deltatime * float( cur_move ) );
        int actual_time = std::chrono::duration_cast< std::chrono::milliseconds >( utils::get_time( ) - start ).count( );
        int sleep_time = wanted_time - actual_time;

        // obviously only sleep if we can reasonably do it
        if ( sleep_time > 0 )
            Sleep( sleep_time );

        cur_move++;
    }

    // do final move to fix disrepencies as good as possible
    mouse_move( vec2( ( relative.x - actual_moved.x ) * signx, ( relative.y - actual_moved.y ) * signy ) );
}