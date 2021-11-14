#include <graphics.h>
#include <GLAD/gl.h>
#include <stdlib.h>
#include <STBI/stb_image.h>

///////////////////////////
///////////////////////////
// Shaders  
///////////////////////////
///////////////////////////
emp_t ge_compile_shader(file_t * src, u32_t id) {
    i32_t result = 0;
    i32_t info_ge_log_len = 0;

    const str_t str_src = src -> content;
    const i32_t len = src -> len;

    call_gl(glShaderSource(id, 1, &str_src, &len));
    call_gl(glCompileShader(id));

    call_gl(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    call_gl(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_ge_log_len));

    if (info_ge_log_len > 0) {
        str_t err = calloc(info_ge_log_len + 1, sizeof(chr_t));
        call_gl(glGetShaderInfoLog(id, info_ge_log_len, NULL, &err[0]));
        ge_log_fe("%s", err);
    }
}

u32_t ge_link_shader(u32_t vs_id, u32_t fs_id) {
    u32_t id = glCreateProgram();
    call_gl(glAttachShader(id, vs_id));
    call_gl(glAttachShader(id, fs_id));
    call_gl(glLinkProgram(id));

    i32_t result = 0;
    i32_t info_ge_log_len = 0;

    call_gl(glGetProgramiv(id, GL_LINK_STATUS, &result));
    call_gl(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &info_ge_log_len));

    if (info_ge_log_len > 0) {
        chr_t err[info_ge_log_len + 1];
        call_gl(glGetProgramInfoLog(id, info_ge_log_len, NULL, &err[0]));
        ge_log_fe("%s", err);
    }

    call_gl(glDetachShader(id, vs_id));
    call_gl(glDetachShader(id, fs_id));

    call_gl(glDeleteShader(vs_id));
    call_gl(glDeleteShader(fs_id));
    return id;
}

emp_t ge_mk_shader(ge_shader_t * shader, str_t vs_path, str_t fs_path) {
    u32_t ids[2];
    ids[0] = glCreateShader(GL_VERTEX_SHADER);
    ids[1] = glCreateShader(GL_FRAGMENT_SHADER);
 
    file_t vs = ge_load_file(vs_path);
    file_t fs = ge_load_file(fs_path);
    
    ge_compile_shader(&vs, ids[0]);
    ge_compile_shader(&fs, ids[1]);
    
    u32_t id = ge_link_shader(ids[0], ids[1]);
    
    shader -> vs_path = vs_path;
    shader -> fs_path = fs_path;
    shader -> vs = vs;
    shader -> fs = fs;
    shader -> id = id;
}

emp_t ge_rm_shader(ge_shader_t * shader) {
    call_gl(glDeleteProgram(shader -> id));
    free(shader -> vs.content);
    free(shader -> fs.content);
}

emp_t ge_bind_shader(ge_shader_t shader) {
    call_gl(glUseProgram(shader.id));
}

emp_t ge_unbind_shaders() {
    call_gl(glUseProgram(0));
}

emp_t ge_set_mat4_uniform(ge_shader_t * shader, str_t uniform, f32_t * ptr) {
    i32_t uniform_loc = glGetUniformLocation(shader -> id, uniform);
    call_gl(glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, ptr)); 
}

emp_t ge_set_int(ge_shader_t * shader, str_t uniform, i32_t i) {
    i32_t uniform_loc = glGetUniformLocation(shader -> id, uniform);
    call_gl(glUniform1i(uniform_loc, i));
}

emp_t ge_shader_hot_reload(ge_shader_t * shader) {
    u32_t ids[2];
    ids[0] = glCreateShader(GL_VERTEX_SHADER);
    ids[1] = glCreateShader(GL_FRAGMENT_SHADER);

    file_t vs = ge_load_file(shader -> vs_path);
    file_t fs = ge_load_file(shader -> fs_path);
    
    if (ge_str_compare(shader -> vs.content, vs.content)
     && ge_str_compare(shader -> fs.content, fs.content)) {
        free(vs.content);
        free(fs.content);
        return;
    }

    call_gl(glDeleteProgram(shader -> id));
    free(shader -> vs.content);
    free(shader -> fs.content);

    ge_compile_shader(&vs, ids[0]);
    ge_compile_shader(&fs, ids[1]);
    
    u32_t id = ge_link_shader(ids[0], ids[1]);
    
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
emp_t ge_mk_ibo(ge_ibo_t * ibo, u32_t * indices, u32_t usage, u32_t indice_size) {
    ibo -> indices = indices;
    ibo -> size    = indice_size;
    ibo -> usage   = usage;

    call_gl(glGenBuffers(1, &ibo -> ibo));
    call_gl(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo -> ibo));
    call_gl(glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibo -> size,
                 ibo -> indices, ibo -> usage));
    ibo -> count = ibo -> size / sizeof(u32_t);
}

emp_t ge_rm_ibo(ge_ibo_t * ibo) {
    call_gl(glDeleteBuffers(1, &ibo -> ibo));
}

emp_t ge_bind_ibo(ge_ibo_t ibo) {
    call_gl(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.ibo));
}

emp_t ge_unbind_ibos() {
    call_gl(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

///////////////////////////
///////////////////////////
// Vertex Buffer 
///////////////////////////
///////////////////////////

emp_t ge_mk_vbo(ge_vbo_t * vbo, f32_t * verts, u32_t size, u32_t usage) {
    vbo -> data = verts;
    vbo -> size = size;
    vbo -> usage = usage;
    call_gl(glGenBuffers(1, &vbo -> vbo));
    call_gl(glBindBuffer(GL_ARRAY_BUFFER, vbo -> vbo));
    call_gl(glBufferData(GL_ARRAY_BUFFER, vbo -> size, 
                         vbo -> data, vbo -> usage));
}

emp_t ge_rm_vbo(ge_vbo_t * vbo) {
    call_gl(glDeleteBuffers(1, &vbo -> vbo));
}

emp_t ge_bind_vbo(ge_vbo_t vbo) {
    call_gl(glBindBuffer(GL_ARRAY_BUFFER, vbo.vbo));
}

emp_t ge_unbind_vbos() {
    call_gl(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

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

emp_t ge_mk_vao(ge_vao_t * vao) {
    call_gl(glGenVertexArrays(1, &vao -> vao));
    call_gl(glBindVertexArray(vao -> vao));
}

emp_t ge_rm_vao(ge_vao_t * vao) {
    call_gl(glDeleteVertexArrays(1, &vao -> vao));
}

emp_t ge_bind_vao(ge_vao_t vao) {
    call_gl(glBindVertexArray(vao.vao));
}

emp_t ge_unbind_vaos() {
    call_gl(glBindVertexArray(0));
}

///////////////////////////
///////////////////////////
// Textures  
///////////////////////////
///////////////////////////

emp_t ge_mk_tex(ge_tex_t * tex, str_t path, u16_t slot) {
    tex -> path = path;
    tex -> slot = slot;

    stbi_set_flip_vertically_on_load(0);
    
    u32_t color;
    u08_t cmp = ge_str_length(tex -> path) > 1;

    if (cmp) {
        tex -> buffer = stbi_load(tex -> path, &tex -> w, &tex -> h, &tex -> bpp, 4);
    }

    else {
        color = 0xffffffff;
    }

    call_gl(glGenTextures(1, &tex -> id));
    call_gl(glBindTexture(GL_TEXTURE_2D, tex -> id));

    call_gl(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    call_gl(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    call_gl(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    call_gl(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));


    if (cmp) {
        call_gl(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex -> w, tex -> h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex -> buffer));
    }

    else {
        call_gl(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color));
    }

    glActiveTexture(tex -> slot);
    call_gl(glBindTexture(GL_TEXTURE_2D, tex -> id));

    if (tex -> buffer) {
        stbi_image_free(tex -> buffer);
    }
    
} 

emp_t ge_bind_tex(ge_tex_t * tex) { 
    glActiveTexture(tex -> slot);
    call_gl(glBindTexture(GL_TEXTURE_2D, tex -> id));
}


///////////////////////////
///////////////////////////
// Drawing 
///////////////////////////
///////////////////////////

emp_t ge_draw_verts(u32_t vert_num) {
    call_gl(glDrawElements(GL_TRIANGLES, vert_num, GL_UNSIGNED_INT, 0));
}







