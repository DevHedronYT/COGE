#ifndef __GE_STR__ 

    #define __GE_STR__ 
    
    #include <types.h>  

    str_t ge_str_split      (const str_t str_one, chr_t c);
    i32_t ge_str_length     (const str_t str_one);
    str_t ge_str_concat     (const str_t str_one, const str_t str_two);
    i32_t ge_str_compare    (const str_t str_one, const str_t str_two);
    str_t ge_str_reverse    (str_t str_one);
    i32_t ge_str_subchar    (str_t str_one, chr_t letter);
    i32_t ge_str_ends_with  (str_t str_one, str_t str_two);
    i32_t ge_str_substring  (const str_t str_one, const str_t str_two);
    i32_t ge_str_starts_with(const str_t str_one, const str_t str_two);
    str_t ge_i32_to_str     (i32_t num);
    i32_t ge_str_to_i32     (str_t string);
    str_t ge_f64_to_str     (f64_t num);

#endif 

