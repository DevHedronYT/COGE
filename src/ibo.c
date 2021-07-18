#include <ibo.h>

// Implementation
void coge_gen_ibo_t(coge_ibo_t * indexBuffer) {
    glGenBuffers(1, &indexBuffer -> m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer -> m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer -> m_size, indexBuffer -> m_data, indexBuffer -> m_usage);
    indexBuffer -> m_count = indexBuffer -> m_size / sizeof(unsigned int);
}

void coge_rm_ibo_t(coge_ibo_t * indexBuffer) {
    glDeleteBuffers(1, &indexBuffer -> m_ibo);
}

void coge_bind_ibo_t(coge_ibo_t * indexBuffer) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer -> m_ibo);
}

void coge_unbind_ibo_t() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
