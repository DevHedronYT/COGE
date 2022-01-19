#ifndef MANAGER_H
    #define MANAGER_H

    #include <COGE/engine.h>
    typedef struct {
        ht_t shader;
        ht_t textures;
    } ge_res_manager_t;

    void ge_mk_res_manager(ge_res_manager_t * manager);
    u64 ge_mk_res_shader(char * vs, char * fs, const char * name, ge_res_manager_t * manager);
    u64 ge_mk_res_texture(char * tex_path, const char * name, ge_res_manager_t * manager);
    ge_shader_t * ge_res_get_shader(const char * name, ge_res_manager_t * manager);
    ge_tex_t * ge_res_get_texture(const char * name, ge_res_manager_t * manager);

   
#endif