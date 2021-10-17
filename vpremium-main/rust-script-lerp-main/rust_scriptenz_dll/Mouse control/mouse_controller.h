#pragma once
#include "../pch/pch.h"
#include "../utils/utils.h"

class mouse_controller {
public:
    mouse_controller( );

    // does relative mouse move
    void mouse_move( vec2 relative );

    // does relative mouse move in linear fashion with given time
    void lerp_move( vec2 relative, int32_t time, int32_t moves = 100 );
    void reset( );

private:

    vec2 m_remainder;
};