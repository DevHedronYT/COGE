#include <print.h>
#include <str.h>
#include <types.h>
#include <file.h>
#include <me.h>
#include <key.h>
#include <mouse.h>
#include <joystick.h>
#include <graphics.h>

#ifndef __GE_DECL__

    #ifndef _signal_h
        #define _signal_h
        #include <signal.h>
    #endif

    #define __GE_DECL__
    
    #include <GLAD/gl.h>
    #include <GLFW/glfw3.h>
    #define ge_win_t GLFWwindow*

    #define dbg_brk raise(SIGABRT)

    #define cls_err() ({ while (glGetError() != GL_NO_ERROR); })
    #define ge_assert(x) if (!(x)) dbg_brk;
    #define call_gl(x) cls_err(); x; ge_assert(ge_log_call(#x, __FILE__, __LINE__)); 


    emp_t ge_sleep(u32_t ms);
    i08_t ge_log_call(const str_t func, 
                      const str_t file,
                      i32_t line);

    emp_t ge_init();
    ge_win_t ge_mk_win(u32_t w, u32_t h, const str_t name, u08_t vsync);
    const str_t ge_get_renderer_version();
    str_t ge_get_err();
    emp_t ge_cls(f32_t v0, f32_t v1, f32_t v2, f32_t v3);


#endif

