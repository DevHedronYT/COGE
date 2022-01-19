#ifndef FILE_H
    #define FILE_H 
    #include "./types.h"

    typedef struct {
        char * content;
        const char * path;
        u32 len;
    } file_info_t;

    i08         file_exists   (const char * path);
    file_info_t txt_file_query(const char * path);
    i08         txt_file_write(const char * content, const char * path, const size_t len); 

#endif
