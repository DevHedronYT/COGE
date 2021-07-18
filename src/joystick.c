#include <joystick.h>

int g_coge_joystick_present;
int g_coge_joystick_id;
int g_coge_joystick_axes_count;
int g_coge_joystick_button_count;

const float * g_coge_joystick_axes;
const unsigned char * g_coge_joystick_buttons;
const char * g_coge_joystick_name;

int coge_get_joystick_id(int i) {
    return GLFW_JOYSTICK_1 + i;
}

void coge_update_joystick() {
    g_coge_joystick_present = glfwJoystickPresent(g_coge_joystick_id);

    if (g_coge_joystick_present) {
	g_coge_joystick_name = glfwGetJoystickName(g_coge_joystick_id);
	g_coge_joystick_axes = glfwGetJoystickAxes(g_coge_joystick_id, &g_coge_joystick_axes_count);
	g_coge_joystick_buttons = glfwGetJoystickButtons(g_coge_joystick_id, &g_coge_joystick_button_count);
    }
}

void coge_init_joystick(int i) {
    g_coge_joystick_id = coge_get_joystick_id(i);
    coge_update_joystick();
}

float coge_joystick_axes_state(int axis) {
    if (g_coge_joystick_present) {
	return g_coge_joystick_axes[axis];
    }

    return -1;
}


unsigned char coge_joystick_button_state(int button) {
    if (g_coge_joystick_present) {
	return g_coge_joystick_buttons[button];
    }

    return GLFW_RELEASE;
}


int coge_get_joystick_axes_count() {
    return g_coge_joystick_axes_count;
}

int coge_get_joystick_button_count() {
    return g_coge_joystick_button_count;
}

int coge_is_joystick_present() {
    return g_coge_joystick_present;
}

const char * coge_get_joystick_name() {
    return g_coge_joystick_name;
}


