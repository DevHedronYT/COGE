#include <keyboard.h>

int g_coge_keyboard_keys[GLFW_KEY_LAST + 1];
int g_coge_keyboard_keys_changed[GLFW_KEY_LAST + 1];

void coge_init_keyboard() {
    int i;
    for (i = 0; i < GLFW_KEY_LAST + 1; i++) {
	g_coge_keyboard_keys[i] = 0;
	g_coge_keyboard_keys_changed[i] = 0;
    }
}

void coge_keyboard_key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
    if (action != GLFW_RELEASE) {
	if (!g_coge_keyboard_keys[key]) {
	    g_coge_keyboard_keys[key] = 1;
	}
    }

    else {
	g_coge_keyboard_keys[key] = 0;
    }

    g_coge_keyboard_keys_changed[key] = action != GLFW_REPEAT; 
}

int coge_keyboard_key(int key) {
    return g_coge_keyboard_keys[key];
}

int coge_keyboard_key_changed(int key) {
    int ret = g_coge_keyboard_keys_changed[key];
    g_coge_keyboard_keys_changed[key] = 0;

    return ret;
}

int coge_keyboard_key_down(int key) {
    return g_coge_keyboard_keys[key] && coge_keyboard_key_changed(key);
}

int coge_keyboard_key_up(int key) {
    return !g_coge_keyboard_keys[key] && coge_keyboard_key_changed(key);
}

int coge_keyboard_key_held_down(GLFWwindow * window, int key) {
    if (glfwGetKey(window, key)) {
	return 1;
    }

    return 0;
}

int coge_keyboard_key_held_up(GLFWwindow * window, int key) {
    if (!glfwGetKey(window, key)) {
	return 1;
    }

    return 0;
}


