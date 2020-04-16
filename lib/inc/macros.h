#ifndef MACROS_INCLUDED
#define MACROS_INCLUDED
#if defined( __clang__ ) || defined( __GNUC__ ) || defined( __GNUG__ )
    #define unlikely( x ) __builtin_expect( !!( x ), 0 )
    #define likely( x ) __builtin_expect( !!( x ), 1 )
#else
    #define unlikely( x ) ( x )
    #define likely( x ) ( x )
#endif
namespace constants
{
inline constexpr float oneOverForty = 1.f / 40.f;
}
#endif
