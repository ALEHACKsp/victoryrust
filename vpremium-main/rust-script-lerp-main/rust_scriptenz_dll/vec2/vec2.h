#pragma once
#include <string>

#define INF std::numeric_limits<float>::infinity()

class vec2
{
public:
    vec2( float x_ = 0.f, float y_ = 0.f );
    explicit vec2( const float* flt );

    void invalidate( );
    bool is_valid( ) const;
    void zero( ); /* nulls the vector, x = y = 0*/
    bool is_null( ) const;
    std::string as_string( size_t decimal_places = 2 ) const;

    /* operators */
    float& operator[]( int i );
    float operator[]( int i ) const;
    bool operator==( const vec2& src ) const;
    bool operator!=( const vec2& src ) const;
    vec2& operator+=( const vec2& v );
    vec2& operator-=( const vec2& v );
    vec2& operator*=( float fl );
    vec2& operator*=( const vec2& v );
    vec2& operator/=( const vec2& v );
    vec2& operator+=( float fl );
    vec2& operator/=( float fl );
    vec2& operator-=( float fl );
    vec2& operator=( const vec2& vOther );
    vec2 operator-( void ) const;
    vec2 operator+( const vec2& v ) const;
    vec2 operator-( const vec2& v ) const;
    vec2 operator*( float fl ) const;
    vec2 operator*( const vec2& v ) const;
    vec2 operator/( float fl ) const;
    vec2 operator/( const vec2& v ) const;

    /* misc math funcs */
    float length( ) const;
    float length_sqr( ) const;
    float dot( const vec2& vec ) const;
    void multiply_add( const vec2& vec, float flt );

    float x, y;
};