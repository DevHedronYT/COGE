#include <COGE/engine.h>

v2_t ge_mpos = {0};
v2_t ge_last_mpos = {0};
v2_t ge_dt_mpos = {0};
v2_t ge_mscroll_dt = {0};
u08 ge_is_first_mouse = 0;
u08 ge_mouse_btns[GLFW_MOUSE_BUTTON_LAST + 1] = {0};
u08 ge_mouse_btns_changed[GLFW_MOUSE_BUTTON_LAST + 1] = {0};

void ge_mouse_cursor_callback(ge_win_t win, f64 x, f64 y) {
    ge_mpos.x = x;
    ge_mpos.y = y;

    if (ge_is_first_mouse) {
        ge_last_mpos.x = ge_mpos.x;
        ge_last_mpos.y = ge_mpos.y;
        ge_is_first_mouse = 0;
    }
    ge_dt_mpos.x = ge_mpos.x - ge_last_mpos.x;
    ge_dt_mpos.y = ge_mpos.y - ge_last_mpos.y;

    ge_last_mpos.x = ge_mpos.x;
    ge_last_mpos.y = ge_mpos.y;
} 

void ge_mouse_btn_callback(ge_win_t win, i32 button, i32 action, i32 mod) {
    if (action != GLFW_RELEASE) {
        if (!ge_mouse_btns[button]) {
            ge_mouse_btns[button] = 1;
        }
    }

    else {
        ge_mouse_btns[button] = 0;
    }
    
    ge_mouse_btns_changed[button] = action != GLFW_REPEAT;
}

void ge_mouse_wheel_callback(ge_win_t win, f64 x, f64 y) {
    ge_mscroll_dt.x = x;
    ge_mscroll_dt.y = y;
}

v2_t ge_get_mpos() {
    return ge_mpos;
}

v2_t ge_get_mpos_delta() {
    return ge_dt_mpos;
}

v2_t ge_get_mscroll() {
    return ge_mscroll_dt;
}

u08 ge_mbtn(i32 btn) {
    return ge_mouse_btns[btn];
}

u08 ge_mbtn_changed(i32 btn) {
    u08 ret = ge_mouse_btns_changed[btn];
    ge_mouse_btns_changed[btn] = 0;
    return ret;
}

u08 ge_mbtn_down(i32 btn) {
    return ge_mouse_btns[btn] && ge_mbtn_changed(btn);
}

u08 ge_mbtn_up(i32 btn) {
    return !ge_mouse_btns[btn] && ge_mbtn_changed(btn);
}

void ge_init_mouse(ge_win_t win) {
    glfwSetCursorPosCallback(win, ge_mouse_cursor_callback);
    glfwSetMouseButtonCallback(win, ge_mouse_btn_callback);
    glfwSetScrollCallback(win, ge_mouse_wheel_callback);
}



