#pragma once
#include "../pch/pch.h"

/*
    Random helper/util functions :)
*/

namespace utils {
    static __inline std::chrono::time_point<std::chrono::steady_clock> get_time( ) {
        return std::chrono::high_resolution_clock::now( );
    }

    // performs an accurate sleep until a certain amount of microseconds away from a timepoint by sleeping and spinning the thread
    static __inline void accurate_sleep( int64_t wanted_sleep_us, std::chrono::time_point<std::chrono::steady_clock> start ) {
        auto truncated = ( wanted_sleep_us - std::chrono::duration_cast< std::chrono::microseconds >( utils::get_time( ) - start ).count( ) ) / 1000;
        while ( std::chrono::duration_cast< std::chrono::microseconds >( utils::get_time( ) - start ).count( ) < wanted_sleep_us )
        {
            if ( truncated )
            {
                std::this_thread::sleep_for( std::chrono::milliseconds( truncated ) );
                truncated = 0;
            }
        }
    }

    static __inline float random_float( float min, float max ) {
        float rnd = float(rand( )) / float(RAND_MAX);

        float range = max - min;
        return ( rnd * range ) + min;
    }
}