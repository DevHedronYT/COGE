#ifndef __GE_FILE__ 

    #define __GE_FILE__ 

    #include <types.h>

    typedef struct {
        str_t content;
        str_t path;
        u32_t len;
    } file_t;

    i08_t  ge_file_exists(str_t path);
    file_t ge_load_file(str_t path);
    i08_t  ge_write_file(str_t content, str_t path);

#endif
