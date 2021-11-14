#ifndef __GE_TYPES__ 

    #define __GE_TYPES__ 

    #define i08_t signed char 
    #define i16_t short 
    #define i32_t int 
    #define i64_t long long 
    #define f32_t float 
    #define f64_t double
    #define u08_t unsigned char 
    #define u16_t unsigned short 
    #define u32_t unsigned 
    #define u64_t unsigned long long 
    #define emp_t void
    #define ret_t void *
    #define str_t char *
    #define chr_t char

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
