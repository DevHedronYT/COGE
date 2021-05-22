#include "VertexArray.h"


void GenVAO(VAO * vao)  {
    glGenVertexArrays(1, &vao -> vao);
    glBindVertexArray(vao -> vao);
} 

// Error might occur, remove the ampersands

void RmVAO(VAO * vao) {
    glDeleteVertexArrays(1, &vao -> vao);
}

void BindVAO(VAO * vao) {
    glBindVertexArray(vao -> vao);
}

void UnbindVAO() {
    glBindVertexArray(0);
}


