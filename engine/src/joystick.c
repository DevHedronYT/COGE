#include <COGE/engine.h>


u08 ge_joystick_present = 0;
i32 ge_joystick_id = -1;
i32 ge_joystick_axes_count = -1;
i32 ge_joystick_btn_count = -1;

const f32 * ge_joystick_axes;
const u08 * ge_joystick_btn;
const char * ge_joystick_name;

u08 ge_get_joystick_id(u16 i) {
    return GLFW_JOYSTICK_1 + i;
}

void ge_update_joystick() {
    ge_joystick_present = glfwJoystickPresent(ge_joystick_id);

    if (ge_joystick_present) {
        ge_joystick_name = glfwGetJoystickName(ge_joystick_id);
        ge_joystick_axes = glfwGetJoystickAxes(ge_joystick_id, &ge_joystick_axes_count);
        ge_joystick_btn = glfwGetJoystickButtons(ge_joystick_id, &ge_joystick_btn_count);
    }
}

void ge_init_joystick(u16 i) { 
    ge_joystick_id = ge_get_joystick_id(i);
    ge_update_joystick();
}

f32 ge_get_joystick_axes_state(i32 axis) {
    if (ge_joystick_present) {
        return ge_joystick_axes[axis];
    }
    return -1;
}

u08 ge_joystick_btn_state(i32 btn) {
    if (ge_joystick_present) {
        return ge_joystick_btn[btn];
    }
    return GLFW_RELEASE;
}

u32 ge_get_joystick_axes_count() {
    return ge_joystick_axes_count;
}

u32 ge_get_joystick_btn_count() {
    return ge_joystick_btn_count;
}

u08 ge_is_joystick_present() {
    return ge_joystick_present;
}

const char * ge_get_joystick_name() {
    return ge_joystick_name;
}



