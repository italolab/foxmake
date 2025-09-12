#ifndef LIBMATH_H
#define LIBMATH_H

#ifdef BUILDING_DLL
    #define LIBMATH_API __declspec(dllexport)
#else
    #define LIBMATH_API __declspec(dllimport)
#endif

namespace libmath {

    LIBMATH_API int fatorial( int n );

}

#endif