#ifndef GE_MOUSE_H 
    #define GE_MOUSE_H
 
    #include <extd_cstd/lib.h>

    void ge_init_mouse(ge_win_t win);
    void ge_mouse_cursor_callback(ge_win_t win, f64 x, f64 y);
    void ge_mouse_btn_callback(ge_win_t win, i32 button, i32 action, i32 mod);
    void ge_mouse_wheel_callback(ge_win_t win, f64 x, f64 y);
    v2_t ge_get_mpos();
    v2_t ge_get_mpos_delta();
    v2_t ge_get_mscroll();
    u08 ge_mbtn(i32 btn); 
    u08 ge_mbtn_changed(i32 btn);
    u08 ge_mbtn_down(i32 btn);
    u08 ge_mbtn_up(i32 btn);
    void ge_init_mouse(ge_win_t win);




#endif
