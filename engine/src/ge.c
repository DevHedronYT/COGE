#include <COGE/engine.h>
#include <stdlib.h>


#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

void ge_sleep(u32 ms) {
    #ifdef _WIN32
        Sleep(ms);
    #else
        usleep(ms * 1000);
    #endif
}

i08 ge_log_call(const char * func, const char * file, i32 line) {
    GLenum err;
    while ((err = glGetError())) {
        log_fatal_err("[OpenGL Error]: %s %s, ERR CODE: %d, LINE NO: %d", func, file, err, line);
        return 0;
    }
    return 1;
}


void ge_init() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif  
}


ge_win_t ge_mk_win(u32 w, u32 h, const char * name, u08 vsync) {
    ge_win_t win = glfwCreateWindow(w, h, name, NULL, NULL);

    assert(win != NULL);

    glfwMakeContextCurrent(win);
    glfwSwapInterval(vsync);

    if (!gladLoadGL(glfwGetProcAddress)) {
        log_msg("Failed to load GLAD");
        glfwTerminate();
        return NULL;
    }

    ge_call_gl(glEnable(GL_BLEND));
    ge_call_gl(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    ge_init_keyboard(win);
    ge_init_mouse(win);
    ge_init_joystick(0);

    return win;
}

void ge_fill_win(f32 v0, f32 v1, f32 v2, f32 v3) {
    ge_call_gl(glClear(GL_COLOR_BUFFER_BIT));
    ge_call_gl(glClearColor(v0, v1, v2, v3));
}

const char * ge_get_ogl_version() {
    return (char *) glGetString(GL_VERSION);
}
