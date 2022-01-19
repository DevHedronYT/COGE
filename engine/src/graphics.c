#include <COGE/engine.h>
#include <GLAD/gl.h>
#include <stdlib.h>
#include <STBI/stb_image.h>

///////////////////////////
///////////////////////////
// Shaders  
///////////////////////////
///////////////////////////
void ge_compile_shader(file_info_t * src, u32 id) {
    i32 result = 0;
    i32 info_ge_log_len = 0;

    const char * str_src = src -> content;
    const i32 len = src -> len;

    ge_call_gl(glShaderSource(id, 1, &str_src, NULL));
    // ge_call_gl(glShaderSource(id, 1, &str_src, &len));
    ge_call_gl(glCompileShader(id));

    ge_call_gl(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    if (result != GL_TRUE) {
        ge_call_gl(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_ge_log_len));
        char * err = calloc(info_ge_log_len + 1, sizeof(char));
        // ge_call_gl(glGetShaderInfoLog(id, info_ge_log_len, NULL, &err[0]));
        ge_call_gl(glGetShaderInfoLog(id, info_ge_log_len, &info_ge_log_len, err));
        log_fatal_err("shader compilation %s", err);
    
    }
}

u32 ge_link_shader(u32 vs_id, u32 fs_id) {
    u32 id = glCreateProgram();
    ge_call_gl(glAttachShader(id, vs_id));
    ge_call_gl(glAttachShader(id, fs_id));
    ge_call_gl(glLinkProgram(id));

    i32 result = 0;
    i32 info_ge_log_len = 0;

    ge_call_gl(glGetProgramiv(id, GL_LINK_STATUS, &result));

    if (result != GL_TRUE) {
        ge_call_gl(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &info_ge_log_len));
        char * err = calloc(info_ge_log_len + 1, sizeof(char));
        ge_call_gl(glGetProgramInfoLog(id, info_ge_log_len, NULL, &err[0]));
        log_fatal_err("shader linking %s", err);
    }

    ge_call_gl(glDetachShader(id, vs_id));
    ge_call_gl(glDetachShader(id, fs_id));

    ge_call_gl(glDeleteShader(vs_id));
    ge_call_gl(glDeleteShader(fs_id));
    return id;
}

void ge_mk_shader(ge_shader_t * shader, char * vs_path, char * fs_path) {
    u32 ids[2];
    ids[0] = glCreateShader(GL_VERTEX_SHADER);
    ids[1] = glCreateShader(GL_FRAGMENT_SHADER);
 
    file_info_t vs = txt_file_query(vs_path);
    file_info_t fs = txt_file_query(fs_path);
    
    ge_compile_shader(&vs, ids[0]);
    ge_compile_shader(&fs, ids[1]);
    
    u32 id = ge_link_shader(ids[0], ids[1]);
    
    shader -> vs_path = vs_path;
    shader -> fs_path = fs_path;
    shader -> vs = vs;
    shader -> fs = fs;
    shader -> id = id;
}

void ge_rm_shader(ge_shader_t * shader) {
    ge_call_gl(glDeleteProgram(shader -> id));
    free(shader -> vs.content);
    free(shader -> fs.content);
}

void ge_bind_shader(ge_shader_t shader) {
    ge_call_gl(glUseProgram(shader.id));
}

void ge_unbind_shaders() {
    ge_call_gl(glUseProgram(0));
}

void ge_set_mat4_uniform(ge_shader_t * shader, char * uniform, f32 * ptr) {
    i32 uniform_loc = glGetUniformLocation(shader -> id, uniform);
    ge_call_gl(glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, ptr)); 
}

void ge_set_int(ge_shader_t * shader, char * uniform, i32 i) {
    i32 uniform_loc = glGetUniformLocation(shader -> id, uniform);
    ge_call_gl(glUniform1i(uniform_loc, i));
}

void ge_shader_hot_reload(ge_shader_t * shader) {
    u32 ids[2];
    ids[0] = glCreateShader(GL_VERTEX_SHADER);
    ids[1] = glCreateShader(GL_FRAGMENT_SHADER);

    file_info_t vs = txt_file_query(shader -> vs_path);
    file_info_t fs = txt_file_query(shader -> fs_path);
    
    if (!strcmp(shader -> vs.content, vs.content)
     && !strcmp(shader -> fs.content, fs.content)) {
        free(vs.content);
        free(fs.content);
        return;
    }

    ge_call_gl(glDeleteProgram(shader -> id));
    free(shader -> vs.content);
    free(shader -> fs.content);

    ge_compile_shader(&vs, ids[0]);
    ge_compile_shader(&fs, ids[1]);
    
    u32 id = ge_link_shader(ids[0], ids[1]);
    
    shader -> vs = vs;
    shader -> fs = fs;
    shader -> id = id;
    ge_bind_shader(*shader);
}

// Track the set uniforms

///////////////////////////
///////////////////////////
// Index Buffer
///////////////////////////
///////////////////////////

// Size is needed in bytes
void ge_mk_ibo(ge_ibo_t * ibo, u32 * indices, u32 usage, u32 indice_size) {
    ibo -> indices = indices;
    ibo -> size    = indice_size;
    ibo -> usage   = usage;

    ge_call_gl(glGenBuffers(1, &ibo -> ibo));
    ge_call_gl(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo -> ibo));
    ge_call_gl(glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibo -> size,
                 ibo -> indices, ibo -> usage));
    ibo -> count = ibo -> size / sizeof(u32);
}

void ge_rm_ibo(ge_ibo_t * ibo) {
    ge_call_gl(glDeleteBuffers(1, &ibo -> ibo));
}

void ge_bind_ibo(ge_ibo_t ibo) {
    ge_call_gl(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.ibo));
}

void ge_unbind_ibos() {
    ge_call_gl(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

///////////////////////////
///////////////////////////
// Vertex Buffer 
///////////////////////////
///////////////////////////

void ge_mk_vbo(ge_vbo_t * vbo, f32 * verts, u32 size, u32 usage) {
    vbo -> data = verts;
    vbo -> size = size;
    vbo -> usage = usage;
    ge_call_gl(glGenBuffers(1, &vbo -> vbo));
    ge_call_gl(glBindBuffer(GL_ARRAY_BUFFER, vbo -> vbo));
    ge_call_gl(glBufferData(GL_ARRAY_BUFFER, vbo -> size, 
                         vbo -> data, vbo -> usage));
}

void ge_rm_vbo(ge_vbo_t * vbo) {
    ge_call_gl(glDeleteBuffers(1, &vbo -> vbo));
}

void ge_bind_vbo(ge_vbo_t vbo) {
    ge_call_gl(glBindBuffer(GL_ARRAY_BUFFER, vbo.vbo));
}

void ge_unbind_vbos() {
    ge_call_gl(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

// stride is the offset
// between the next vertex
// offset is the offset
// between the next common 
// element
//


///////////////////////////
///////////////////////////
// Vertex Array
///////////////////////////
///////////////////////////

void ge_mk_vao(ge_vao_t * vao) {
    ge_call_gl(glGenVertexArrays(1, &vao -> vao));
    ge_call_gl(glBindVertexArray(vao -> vao));
}

void ge_rm_vao(ge_vao_t * vao) {
    ge_call_gl(glDeleteVertexArrays(1, &vao -> vao));
}

void ge_bind_vao(ge_vao_t vao) {
    ge_call_gl(glBindVertexArray(vao.vao));
}

void ge_unbind_vaos() {
    ge_call_gl(glBindVertexArray(0));
}

///////////////////////////
///////////////////////////
// Textures  
///////////////////////////
///////////////////////////

void ge_mk_tex(ge_tex_t * tex, char * path, u16 slot) {
    tex -> path = path;
    tex -> slot = slot;

    stbi_set_flip_vertically_on_load(0);
    
    tex -> buffer = stbi_load(tex -> path, &tex -> w, &tex -> h, &tex -> bpp, 4);

    ge_call_gl(glGenTextures(1, &tex -> id));
    ge_call_gl(glBindTexture(GL_TEXTURE_2D, tex -> id));

    ge_call_gl(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    ge_call_gl(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    ge_call_gl(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    ge_call_gl(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));


    ge_call_gl(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex -> w, tex -> h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex -> buffer));

    ge_call_gl(glBindTexture(GL_TEXTURE_2D, tex -> slot));
    if (tex -> buffer) {
        stbi_image_free(tex -> buffer);
    }
    
} 

void ge_bind_tex(ge_tex_t * tex) { 
    ge_call_gl(glActiveTexture(GL_TEXTURE0 + tex -> slot));
    ge_call_gl(glBindTexture(GL_TEXTURE_2D, tex -> id));
}

///////////////////////////
///////////////////////////
// Drawing 
///////////////////////////
///////////////////////////

void ge_draw_verts(u32 vert_num) {
    ge_call_gl(glDrawElements(GL_TRIANGLES, vert_num, GL_UNSIGNED_INT, 0));
}







