#include <vbo.h>

void coge_gen_vbo_t(coge_vbo_t * vbo) {    
    glGenBuffers(1, &vbo -> m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo -> m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vbo -> m_size, vbo -> m_data, vbo -> m_usage);
}

void coge_del_vbo_t(coge_vbo_t * vbo) {
    glDeleteBuffers(1, &vbo -> m_vbo);
}

void coge_bind_vbo_t(coge_vbo_t * vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo -> m_vbo);
}

void coge_unbind_vbo_t() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


