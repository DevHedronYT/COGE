#ifndef GE_DECL_H

    #ifndef SIGNAL_H 
        #define SIGNAL_H
        #include <signal.h>
    #endif

    #define GE_DECL_H 
    
    #include <GLAD/gl.h>
    #include <GLFW/glfw3.h>

   
    #define dbg_brk  raise(SIGABRT)
    #define cls_err() { while (glGetError() != GL_NO_ERROR); }
    #define ge_assert_glfunc(x) if (!(x)) dbg_brk;

    #define ge_call_gl(x) cls_err(); x; ge_assert_glfunc(ge_log_call(#x, __FILE__, __LINE__)); 
    #define ge_win_t GLFWwindow *


    void ge_sleep(u32 ms);
    i08  ge_log_call(const char * func, const char * file, i32 line);

    void     ge_init();
    ge_win_t ge_mk_win(u32 w, u32 h, const char * name, u08 vsync);
    void     ge_fill_win(f32 v0, f32 v1, f32 v2, f32 v3);


    const char * ge_get_ogl_version();


#endif

