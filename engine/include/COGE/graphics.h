#ifndef GE_GRAPHICS_H 
    #define GE_GRAPHICS_H
    
    #include <extd_cstd/lib.h>

    ///////////////////////////
    ///////////////////////////
    // Shaders  
    ///////////////////////////
    ///////////////////////////
    typedef struct {
        char * vs_path;
        char * fs_path;
        file_info_t vs;
        file_info_t fs;
        u32 id;
    } ge_shader_t; 

    void ge_compile_shader(file_info_t * src, u32 id); 
    u32 ge_link_shader(u32 vs_id, u32 fs_id);
    void ge_mk_shader(ge_shader_t * shader, char * vs_path, char * fs_path);
    void ge_rm_shader(ge_shader_t * shader);
    void ge_bind_shader(ge_shader_t shader);
    void ge_unbind_shaders();
    void ge_set_mat4_uniform(ge_shader_t * shader, char * uniform, f32 * ptr);
    void ge_set_int(ge_shader_t * shader, char * uniform, i32 i);
    void ge_shader_hot_reload(ge_shader_t * shader);

    // Track the set uniforms

    ///////////////////////////
    ///////////////////////////
    // Index Buffer
    ///////////////////////////
    ///////////////////////////
    typedef struct {
        const u32 * indices;
        u32 size;
        u32 usage; 
        u32 ibo;
        u32 count;
    } ge_ibo_t;

    // Size is needed in bytes
    void ge_mk_ibo(ge_ibo_t * ibo, u32 * indices, u32 usage, u32 indice_size);    
    void ge_rm_ibo(ge_ibo_t * ibo);
    void ge_bind_ibo(ge_ibo_t ibo);
    void ge_unbind_ibos();

    ///////////////////////////
    ///////////////////////////
    // Vertex Buffer 
    ///////////////////////////
    ///////////////////////////
    typedef struct {
        u32 size;
        const void * data;
        u32 usage;
        u32 vbo;
    } ge_vbo_t;

    void ge_mk_vbo(ge_vbo_t * vbo, f32 * verts, u32 size, u32 usage); 
    void ge_rm_vbo(ge_vbo_t * vbo);
    void ge_bind_vbo(ge_vbo_t vbo);
    void ge_unbind_vbos();

    // stride is the offset
    // between the next vertex
    // offset is the offset
    // between the next common 
    // element
    #define ge_vertex_buffer_layout(idx, elems, type, normalized, stride, offset) \
        ge_call_gl(glVertexAttribPointer(idx, elems, type, normalized, stride, (void *)(offset))); \
        ge_call_gl(glEnableVertexAttribArray(idx)); 


    ///////////////////////////
    ///////////////////////////
    // Vertex Array
    ///////////////////////////
    ///////////////////////////
    typedef struct {
        u32 vao;
    } ge_vao_t;

    void ge_mk_vao(ge_vao_t * vao);
    void ge_rm_vao(ge_vao_t * vao);
    void ge_bind_vao(ge_vao_t vao);
    void ge_unbind_vaos();

    ///////////////////////////
    ///////////////////////////
    // Textures  
    ///////////////////////////
    ///////////////////////////
    typedef struct {
        u32 id;
        char * path;
        u16 slot;
        u08 * buffer;
        i32 w;
        i32 h; 
        i32 bpp;
    } ge_tex_t;


    void ge_mk_tex(ge_tex_t * tex, char * path, u16 slot); 
    void ge_bind_tex(ge_tex_t * tex); 


    ///////////////////////////
    ///////////////////////////
    // Drawing 
    ///////////////////////////
    ///////////////////////////
    void ge_draw_verts(u32 vert_num);


#endif
