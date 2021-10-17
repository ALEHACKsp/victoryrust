#include "../pch/pch.h"
#include "vec2.h"

vec2::vec2( float x_, float y_ ): x( x_ ), y( y_ ) {

}

vec2::vec2( const float* flt ) : x( 0.f ), y( 0.f ) {
    if ( flt )
        for ( auto i = 0; i < 2; i++ )
            this[ i ] = flt[ i ];
}

void vec2::invalidate( ) {
    x = y = INFINITY;
}

bool vec2::is_valid( ) const {
    return std::isfinite( x ) && std::isfinite( y );
}

void vec2::zero( ) {
    x = y = 0.f;
}

bool vec2::is_null( ) const {
    return ( x == y == 0.f );
}

std::string vec2::as_string( size_t decimal_places ) const {
    std::stringstream stream;
    stream << std::fixed << std::setprecision( decimal_places );
    stream << "x: " << x << ", y: " << y;

    return stream.str( );
}

float& vec2::operator[]( int i ) {
    return reinterpret_cast< float* >( this )[ i ];
}

float vec2::operator[]( int i ) const {
    return ( ( float* )this )[ i ];
}

bool vec2::operator==( const vec2& src ) const {
    return ( src.x == x ) && ( src.y == y );
}

bool vec2::operator!=( const vec2& src ) const {
    return ( src.x != x ) || ( src.y != y );
}

vec2& vec2::operator+=( const vec2& v ) {
    x += v.x;
    y += v.y;
    return *this;
}

vec2& vec2::operator-=( const vec2& v ) {
    x -= v.x;
    y -= v.y;
    return *this;
}

vec2& vec2::operator*=( float fl ) {
    x *= fl;
    y *= fl;
    return *this;
}

vec2& vec2::operator*=( const vec2& v ) {
    x *= v.x;
    y *= v.y;
    return *this;
}

vec2& vec2::operator/=( const vec2& v ) {
    x /= v.x;
    y /= v.y;
    return *this;
}

vec2& vec2::operator+=( float fl ) {
    x += fl;
    y += fl;
    return *this;
}

vec2& vec2::operator/=( float fl ) {
    x /= fl;
    y /= fl;
    return *this;
}

vec2& vec2::operator-=( float fl ) {
    x -= fl;
    y -= fl;
    return *this;
}

vec2& vec2::operator=( const vec2& vOther ) {
    x = vOther.x;
    y = vOther.y;
    return *this;
}

vec2 vec2::operator-( ) const {
    return vec2( -x, -y );
}

vec2 vec2::operator+( const vec2& v ) const {
    return vec2( x + v.x, y + v.y );
}

vec2 vec2::operator-( const vec2& v ) const {
    return vec2( x - v.x, y - v.y );
}

vec2 vec2::operator*( float fl ) const {
    return vec2( x * fl, y * fl );
}

vec2 vec2::operator*( const vec2& v ) const {
    return vec2( x * v.x, y * v.y );
}

vec2 vec2::operator/( float fl ) const {
    return vec2( x / fl, y / fl );
}

vec2 vec2::operator/( const vec2& v ) const {
    return vec2( x / v.x, y / v.y );
}

float vec2::length_sqr( ) const {
    return ( x * x + y * y );
}

float vec2::length( ) const {
    return sqrt( length_sqr( ) );
}

float vec2::dot( const vec2& vec ) const {
    return ( x * vec.x + y * vec.y );
}

void vec2::multiply_add( const vec2& vec, float flt ) {
    for ( int i = 0; i < 2; ++i )
        this[ i ] += vec[ i ] * flt;
}