#include <stdio.h>
#include <stdlib.h>
#include <file.h>
#include <str.h>

i08_t ge_file_exists(str_t path) {
    FILE * f = fopen(path, "r");
    if (f) {
        fclose(f);
        return 1;
    }
    fclose(f);
    return 0;
}

file_t ge_load_file(str_t path) {
    FILE * f = fopen(path, "r");
    file_t file_final;

    if (f) {
        fseek(f, 0, SEEK_END);
        file_final.len = ftell(f);
        file_final.content = (str_t) calloc(file_final.len + 1, sizeof(chr_t));
        rewind(f);
        fread(file_final.content, sizeof(chr_t), file_final.len, f);
        file_final.content[file_final.len + 1] = '\0';
        fclose(f);

        file_final.path = path;

        return file_final;
    }

    else {
        return (file_t){"NULL", path, -1};
    }
}

i08_t ge_write_file(str_t content, str_t path) { 
    FILE * f = fopen(path, "wb");
    
    if (!f) { return 0;  }
    i32_t len = ge_str_length(content);
    fwrite(content, sizeof(chr_t), len, f);
    fclose(f);
    return 1;
}


