#include <key.h>

u08_t keys[GLFW_KEY_LAST + 1] = {0};
u08_t keys_changed[GLFW_KEY_LAST + 1] = {0};

emp_t ge_key_callback(ge_win_t window, i32_t key, i32_t scancode, i32_t action, i32_t mods) {
    if (action != GLFW_RELEASE) {
        if (!keys[key]) {
            keys[key] = 1;
        }
    }

    else {
        keys[key] = 0;
    }

    keys_changed[key] = action != GLFW_REPEAT; 
}

u08_t ge_key(i32_t key) {
    return keys[key];
}

u08_t ge_key_changed(i32_t key) {
    i32_t ret = keys_changed[key];
    keys_changed[key] = 0;
    return ret;
}

u08_t ge_key_down(i32_t key) {
    return keys[key] && ge_key_changed(key);
}

u08_t ge_key_up(i32_t key) {
    return !keys[key] && ge_key_changed(key);
}

u08_t ge_key_held_down(ge_win_t win, i32_t key) {
    if (glfwGetKey(win, key)) {
        return 1;
    }

    return 0;
}

u08_t ge_key_held_up(ge_win_t win, i32_t key) {
    if (!glfwGetKey(win, key)) {
        return 1;
    }

    return 0;
}

emp_t ge_init_keyboard(ge_win_t win) {
    glfwSetKeyCallback(win, ge_key_callback);
}


