#include <util.h>
    // Implementation

coge_program_props_t coge_gen_program_props_t(float * vertices, unsigned int * indices, unsigned int verticesSize, unsigned int indicesSize, unsigned int vboUsage, unsigned int iboUsage) {
    coge_program_props_t props;

    coge_gen_vao_t(&props.vao);
    coge_bind_vao_t(&props.vao);

    props.vbo.m_data = vertices;
    props.vbo.m_size = verticesSize;
    props.vbo.m_usage = vboUsage;

    coge_gen_vbo_t(&props.vbo);
    coge_bind_vbo_t(&props.vbo);

    props.ibo.m_data = indices;
    props.ibo.m_size = indicesSize;
    props.ibo.m_usage = iboUsage;

    coge_gen_ibo_t(&props.ibo);
    coge_bind_ibo_t(&props.ibo);

    return props;
}


GLFWwindow * coge_window_init(int width, int height, const char * name) {

    if (!glfwInit()) {
	coge_log_error("Error Initializing GLFW", NULL);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    # ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_TRUE);
    # endif
	
    GLFWwindow * window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!window) {
	coge_log_error("Error Making Window", NULL);
	glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGL(glfwGetProcAddress)) {
	coge_log_error("Error Initializing GLAD", NULL);
	glfwTerminate();
    }
    
    coge_log_info("OpenGL Version: %s", glGetString(GL_VERSION));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return window;
}

void coge_clear_screen(float v0, float v1, float v2, float v3) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(v0, v1, v2, v3);
}

void coge_draw_vertices(unsigned int vertexNum) {
    glDrawElements(GL_TRIANGLES, vertexNum, GL_UNSIGNED_INT, 0);
}


