#include <mouse.h>

ge_v2_t ge_mpos = {0};
ge_v2_t ge_last_mpos = {0};
ge_v2_t ge_dt_mpos = {0};
ge_v2_t ge_mscroll_dt = {0};
u08_t ge_is_first_mouse = 0;
u08_t ge_mouse_btns[GLFW_MOUSE_BUTTON_LAST + 1] = {0};
u08_t ge_mouse_btns_changed[GLFW_MOUSE_BUTTON_LAST + 1] = {0};

emp_t ge_mouse_cursor_callback(ge_win_t win, f64_t x, f64_t y) {
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

emp_t ge_mouse_btn_callback(ge_win_t win, i32_t button, i32_t action, i32_t mod) {
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

emp_t ge_mouse_wheel_callback(ge_win_t win, f64_t x, f64_t y) {
    ge_mscroll_dt.x = x;
    ge_mscroll_dt.y = y;
}

ge_v2_t ge_get_mpos() {
    return ge_mpos;
}

ge_v2_t ge_get_mpos_delta() {
    return ge_dt_mpos;
}

ge_v2_t ge_get_mscroll() {
    return ge_mscroll_dt;
}

u08_t ge_mbtn(i32_t btn) {
    return ge_mouse_btns[btn];
}

u08_t ge_mbtn_changed(i32_t btn) {
    u08_t ret = ge_mouse_btns_changed[btn];
    ge_mouse_btns_changed[btn] = 0;
    return ret;
}

u08_t ge_mbtn_down(i32_t btn) {
    return ge_mouse_btns[btn] && ge_mbtn_changed(btn);
}

u08_t ge_mbtn_up(i32_t btn) {
    return !ge_mouse_btns[btn] && ge_mbtn_changed(btn);
}

emp_t ge_init_mouse(ge_win_t win) {
    glfwSetCursorPosCallback(win, ge_mouse_cursor_callback);
    glfwSetMouseButtonCallback(win, ge_mouse_btn_callback);
    glfwSetScrollCallback(win, ge_mouse_wheel_callback);
}



