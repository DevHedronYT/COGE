#include <vao.h>

// Implementation
void coge_gen_vao_t(coge_vao_t * vao)  {
    glGenVertexArrays(1, &vao -> m_vao);
    glBindVertexArray(vao -> m_vao);
} 

void coge_del_vao_t(coge_vao_t * vao) {
    glDeleteVertexArrays(1, &vao -> m_vao);
}

void coge_bind_vao_t(coge_vao_t * vao) {
    glBindVertexArray(vao -> m_vao);
}

void coge_unbind_vao_t() {
    glBindVertexArray(0);
}
