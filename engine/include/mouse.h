#ifndef __GE_MOUSE__
    #define __GE_MOUSE__
 
    #include <ge.h>

    emp_t ge_init_mouse(ge_win_t win);
    emp_t ge_mouse_cursor_callback(ge_win_t win, f64_t x, f64_t y);
    emp_t ge_mouse_btn_callback(ge_win_t win, i32_t button, i32_t action, i32_t mod);
    emp_t ge_mouse_wheel_callback(ge_win_t win, f64_t x, f64_t y);
    ge_v2_t ge_get_mpos();
    ge_v2_t ge_get_mpos_delta();
    ge_v2_t ge_get_mscroll();
    u08_t ge_mbtn(i32_t btn); 
    u08_t ge_mbtn_changed(i32_t btn);
    u08_t ge_mbtn_down(i32_t btn);
    u08_t ge_mbtn_up(i32_t btn);
    emp_t ge_init_mouse(ge_win_t win);




#endif
