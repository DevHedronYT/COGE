#ifndef _COGE_UTILS

    #define _COGE_UTILS    
    #include <stdio.h>

    #include <gl.h>
    #include <GLFW/glfw3.h>
    #include "vao.h"
    #include "vbo.h"
    #include "ibo.h"
    #include "log.h"

    // Declarations
    typedef struct {
	coge_vao_t vao;
	coge_vbo_t vbo;
	coge_ibo_t ibo;
    } coge_program_props_t;

    coge_program_props_t coge_gen_program_props_t(float * vertices, unsigned int * indices, unsigned int verticesSize, unsigned int indicesSize, unsigned int vboUsage, unsigned int iboUsage); 
    GLFWwindow * coge_window_init(int width, int height, const char * name);
    void coge_clear_screen(float v0, float v1, float v2, float v3); 
    void coge_draw_vertices(unsigned int vertexNum);

#endif
