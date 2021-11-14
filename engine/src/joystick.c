#include <joystick.h>


u08_t ge_joystick_present = 0;
i32_t ge_joystick_id = -1;
i32_t ge_joystick_axes_count = -1;
i32_t ge_joystick_btn_count = -1;

const f32_t * ge_joystick_axes;
const u08_t * ge_joystick_btn;
const str_t ge_joystick_name;

u08_t ge_get_joystick_id(u16_t i) {
    return GLFW_JOYSTICK_1 + i;
}

emp_t ge_update_joystick() {
    ge_joystick_present = glfwJoystickPresent(ge_joystick_id);

    if (ge_joystick_present) {
        ge_joystick_name = glfwGetJoystickName(ge_joystick_id);
        ge_joystick_axes = glfwGetJoystickAxes(ge_joystick_id, &ge_joystick_axes_count);
        ge_joystick_btn = glfwGetJoystickButtons(ge_joystick_id, &ge_joystick_btn_count);
    }
}

emp_t ge_init_joystick(u16_t i) { 
    ge_joystick_id = ge_get_joystick_id(i);
    ge_update_joystick();
}

f32_t ge_get_joystick_axes_state(i32_t axis) {
    if (ge_joystick_present) {
        return ge_joystick_axes[axis];
    }
    return -1;
}

u08_t ge_joystick_btn_state(i32_t btn) {
    if (ge_joystick_present) {
        return ge_joystick_btn[btn];
    }
    return GLFW_RELEASE;
}

u32_t ge_get_joystick_axes_count() {
    return ge_joystick_axes_count;
}

u32_t ge_get_joystick_btn_count() {
    return ge_joystick_btn_count;
}

u08_t ge_is_joystick_present() {
    return ge_joystick_present;
}

const str_t ge_get_joystick_name() {
    return ge_joystick_name;
}



