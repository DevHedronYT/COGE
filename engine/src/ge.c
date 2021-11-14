#include <ge.h>
#include <stdlib.h>


#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

emp_t ge_sleep(u32_t ms) {
    #ifdef _WIN32
        Sleep(ms);
    #else
        usleep(ms * 1000);
    #endif
}

i08_t ge_log_call(const str_t func,
                  const str_t file, 
                  i32_t line) {
    GLenum err;
    while ((err = glGetError())) {
        ge_log_fe("[OpenGL Error]: %s %s, ERR CODE: %d, LINE NO: %d", func, file, err, line);
        return 0;
    }
    return 1;
}


str_t error = NULL;

emp_t ge_init() {
    error = calloc(512, sizeof(chr_t));
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif  
}


ge_win_t ge_mk_win(u32_t w, u32_t h, const str_t name, u08_t vsync) {
    ge_win_t win = glfwCreateWindow(w, h, name, NULL, NULL);
    if (!win) {
        error = "Failed To Create Window";
        glfwTerminate();
        return NULL;
    }

    free(error);
    error = NULL;

    glfwMakeContextCurrent(win);
    glfwSwapInterval(vsync);

    if (!gladLoadGL(glfwGetProcAddress)) {
        if (error == NULL) { error = calloc(512, sizeof(chr_t)); }
        error = "Failed To Initialize GLAD";
        glfwTerminate();
        return NULL;
    }

    free(error);
    error = NULL;   
    call_gl(glEnable(GL_BLEND));
    call_gl(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    ge_init_keyboard(win);
    ge_init_mouse(win);
    ge_init_joystick(0);
    return win;
}

const str_t ge_get_renderer_version() {
    return (str_t) glGetString(GL_VERSION);
}

str_t ge_get_err() {
    return error;
}

emp_t ge_cls(f32_t v0, f32_t v1, f32_t v2, f32_t v3) {
    call_gl(glClear(GL_COLOR_BUFFER_BIT));
    call_gl(glClearColor(v0, v1, v2, v3));
}

