#include <mouse.h>

double g_coge_mouse_pos_x;
double g_coge_mouse_pos_y;
double g_coge_mouse_last_pos_x;
double g_coge_mouse_last_pos_y;
double g_coge_mouse_dx;
double g_coge_mouse_dy;
double g_coge_mouse_scroll_dx; 
double g_coge_mouse_scroll_dy;
int g_coge_is_first_mouse; 
int g_coge_mouse_buttons[GLFW_MOUSE_BUTTON_LAST + 1];
int g_coge_mouse_buttons_changed[GLFW_MOUSE_BUTTON_LAST + 1];



void coge_init_mouse() {
    g_coge_mouse_pos_x = 0;
    g_coge_mouse_pos_y = 0;

    g_coge_mouse_last_pos_x = 0;
    g_coge_mouse_last_pos_y = 0;

    g_coge_mouse_dx = 0;
    g_coge_mouse_dy = 0;

    g_coge_mouse_scroll_dx = 0;
    g_coge_mouse_scroll_dy = 0;

    g_coge_is_first_mouse = 1;
    int i;
    for (i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; i++) {
	g_coge_mouse_buttons[i] = 0;
	g_coge_mouse_buttons_changed[i] = 0;
    }
}

void coge_mouse_cursor_pos_callback(GLFWwindow * window, double _x, double _y) {
    g_coge_mouse_pos_x = _x;
    g_coge_mouse_pos_y = _y;

    if (g_coge_is_first_mouse) {
	g_coge_mouse_last_pos_x = g_coge_mouse_pos_x;
	g_coge_mouse_last_pos_x = g_coge_mouse_pos_y;

	g_coge_is_first_mouse = 0;
    }

    g_coge_mouse_dx = g_coge_mouse_pos_x - g_coge_mouse_last_pos_x;
    g_coge_mouse_dy = g_coge_mouse_pos_y - g_coge_mouse_last_pos_y;

    g_coge_mouse_last_pos_x = g_coge_mouse_pos_x;
    g_coge_mouse_last_pos_y = g_coge_mouse_pos_y;
}

void coge_mouse_button_callback(GLFWwindow * window, int button, int action, int mods) {
    if (action != GLFW_RELEASE) {
	if (!g_coge_mouse_buttons[button]) {
	    g_coge_mouse_buttons[button] = 1;
	}
    }

    else {
	g_coge_mouse_buttons[button] = 0;
    }
    
    g_coge_mouse_buttons_changed[button] = action != GLFW_REPEAT;
}

void coge_mouse_wheel_callback(GLFWwindow * window, double _dx, double _dy) {
    g_coge_mouse_scroll_dx = _dx;
    g_coge_mouse_scroll_dy = _dy;
}

double coge_get_mouse_pos_x() {
    return g_coge_mouse_pos_x;
}
double coge_get_mouse_pos_y() {
    return g_coge_mouse_pos_y;
}

double coge_get_mouse_dx() {
    double _dx = g_coge_mouse_dx;
    g_coge_mouse_dx = 0;

    return _dx;
}
double coge_get_mouse_dy() {
    double _dy = g_coge_mouse_dy;
    g_coge_mouse_dy = 0;

    return _dy;
}

double coge_get_mouse_scroll_dx() {
    double sdx = g_coge_mouse_scroll_dx;
    g_coge_mouse_scroll_dx = 0;

    return sdx;
}
double coge_get_mouse_scroll_dy() {
    double sdy = g_coge_mouse_scroll_dy;
    g_coge_mouse_scroll_dy = 0;

    return sdy;
}

int coge_mouse_button(int button) {
    return g_coge_mouse_buttons[button];
}

int coge_mouse_button_changed(int button) {
    int ret = g_coge_mouse_buttons_changed[button];
    g_coge_mouse_buttons_changed[button] = 0;

    return ret;
}

int coge_mouse_button_down(int button) {
    return g_coge_mouse_buttons[button] && coge_mouse_button_changed(button); 
}

int coge_mouse_button_up(int button) {
    return !g_coge_mouse_buttons[button] && coge_mouse_button_changed(button);
}



