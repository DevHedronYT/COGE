#ifndef TYPES_H 
    #define TYPES_H

    #include <stdint.h>
    #include <stddef.h>
    typedef uint8_t  u08;
    typedef uint16_t u16;
    typedef uint32_t u32; 
    typedef uint64_t u64;

    typedef int8_t  i08;
    typedef int16_t i16; 
    typedef int32_t i32;
    typedef int64_t i64;

    typedef float f32;
    typedef double f64;

    #define i08_min -128
    #define i16_min -32768
    #define i32_min -2147483647 - 1
    #define i64_min -9223372036854775807LL - 1
    
    #define i08_max  127 
    #define i16_max  32767
    #define i32_max  2147483647
    #define i64_max  9223372036854775807LL

    #define u08_max  0xff
    #define u16_max  0xffff
    #define u32_max  0xffffffff
    #define u64_max  0xffffffffffffffffULL 

#endif
