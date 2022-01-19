#ifndef STR_H
    #define STR_H
    
    #include "./types.h"  
    #include <string.h>

    // maybe custom string functions
    char * i32_to_str(i32 num);
    char * f64_to_str(f64 num);
    i32    str_to_i32(char * string);

#endif 

