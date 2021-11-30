#ifndef __GE_GRAPHICS__
    #define __GE_GRAPHICS__
    
    #include <ge.h>

    ///////////////////////////
    ///////////////////////////
    // Shaders  
    ///////////////////////////
    ///////////////////////////
    typedef struct {
        str_t vs_path;
        str_t fs_path;
        file_t vs;
        file_t fs;
        u32_t id;
    } ge_shader_t; 

    emp_t ge_compile_shader(file_t * src, u32_t id); 
    u32_t ge_link_shader(u32_t vs_id, u32_t fs_id);
    emp_t ge_mk_shader(ge_shader_t * shader, str_t vs_path, str_t fs_path);
    emp_t ge_rm_shader(ge_shader_t * shader);
    emp_t ge_bind_shader(ge_shader_t shader);
    emp_t ge_unbind_shaders();
    emp_t ge_set_mat4_uniform(ge_shader_t * shader, str_t uniform, f32_t * ptr);
    emp_t ge_set_int(ge_shader_t * shader, str_t uniform, i32_t i);
    emp_t ge_shader_hot_reload(ge_shader_t * shader);

    // Track the set uniforms

    ///////////////////////////
    ///////////////////////////
    // Index Buffer
    ///////////////////////////
    ///////////////////////////
    typedef struct {
        const u32_t * indices;
        u32_t size;
        u32_t usage; 
        u32_t ibo;
        u32_t count;
    } ge_ibo_t;

    // Size is needed in bytes
    emp_t ge_mk_ibo(ge_ibo_t * ibo, u32_t * indices, u32_t usage, u32_t indice_size);    
    emp_t ge_rm_ibo(ge_ibo_t * ibo);
    emp_t ge_bind_ibo(ge_ibo_t ibo);
    emp_t ge_unbind_ibos();

    ///////////////////////////
    ///////////////////////////
    // Vertex Buffer 
    ///////////////////////////
    ///////////////////////////
    typedef struct {
        u32_t size;
        const ret_t data;
        u32_t usage;
        u32_t vbo;
    } ge_vbo_t;

    emp_t ge_mk_vbo(ge_vbo_t * vbo, f32_t * verts, u32_t size, u32_t usage); 
    emp_t ge_rm_vbo(ge_vbo_t * vbo);
    emp_t ge_bind_vbo(ge_vbo_t vbo);
    emp_t ge_unbind_vbos();

    // stride is the offset
    // between the next vertex
    // offset is the offset
    // between the next common 
    // element
    #define ge_vertex_buffer_layout(idx, elems, type, normalized, stride, offset) \
        call_gl(glVertexAttribPointer(idx, elems, type, normalized, stride, (ret_t)(offset))); \
        call_gl(glEnableVertexAttribArray(idx)); 


    ///////////////////////////
    ///////////////////////////
    // Vertex Array
    ///////////////////////////
    ///////////////////////////
    typedef struct {
        u32_t vao;
    } ge_vao_t;

    emp_t ge_mk_vao(ge_vao_t * vao);
    emp_t ge_rm_vao(ge_vao_t * vao);
    emp_t ge_bind_vao(ge_vao_t vao);
    emp_t ge_unbind_vaos();

    ///////////////////////////
    ///////////////////////////
    // Textures  
    ///////////////////////////
    ///////////////////////////
    typedef struct {
        u32_t id;
        str_t path;
        u16_t slot;
        u08_t * buffer;
        i32_t w;
        i32_t h; 
        i32_t bpp;
    } ge_tex_t;


    emp_t ge_mk_tex(ge_tex_t * tex, str_t path, u16_t slot); 
    emp_t ge_bind_tex(ge_tex_t * tex); 


    ///////////////////////////
    ///////////////////////////
    // Drawing 
    ///////////////////////////
    ///////////////////////////
    emp_t ge_draw_verts(u32_t vert_num);


#endif
