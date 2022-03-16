#include <COGE/manager.h>
#include <stdlib.h>

void ge_mk_res_manager(ge_res_manager_t * manager) {
    manager -> shader = ht_create(100);
    manager -> textures = ht_create(100);
}

u64 ge_mk_res_shader(char * vs, char * fs, const char * name, ge_res_manager_t * manager) {
    ge_shader_t * shader = calloc(1, sizeof(ge_shader_t));
    ge_mk_shader(shader, vs, fs);
    u64 idx = ht_insert(&manager -> shader, name, shader);
    return idx;
}

u32 current_slot = 0;
u64 ge_mk_res_texture(char * tex_path, const char * name, ge_res_manager_t * manager) {
    ge_tex_t * texture = calloc(1, sizeof(ge_tex_t));
    ge_mk_tex(texture, tex_path, current_slot);
    current_slot++;
    u64 idx = ht_insert(&manager -> textures, name, texture);
    return idx;
}


ge_shader_t * ge_res_get_shader(const char * name, ge_res_manager_t * manager) {
    ge_shader_t * shader = ht_get(&manager -> shader, name);
    return shader; 
}

ge_tex_t * ge_res_get_texture(const char * name, ge_res_manager_t * manager) {
    ge_tex_t * texture = ht_get(&manager -> textures, name);
    return texture; 
}

