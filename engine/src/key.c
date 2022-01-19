#include <COGE/engine.h>

u08 keys[GLFW_KEY_LAST + 1] = {0};
u08 keys_changed[GLFW_KEY_LAST + 1] = {0};

void ge_key_callback(ge_win_t window, i32 key, i32 scancode, i32 action, i32 mods) {
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

u08 ge_key(i32 key) {
    return keys[key];
}

u08 ge_key_changed(i32 key) {
    i32 ret = keys_changed[key];
    keys_changed[key] = 0;
    return ret;
}

u08 ge_key_down(i32 key) {
    return keys[key] && ge_key_changed(key);
}

u08 ge_key_up(i32 key) {
    return !keys[key] && ge_key_changed(key);
}

u08 ge_key_held_down(ge_win_t win, i32 key) {
    if (glfwGetKey(win, key)) {
        return 1;
    }

    return 0;
}

u08 ge_key_held_up(ge_win_t win, i32 key) {
    if (!glfwGetKey(win, key)) {
        return 1;
    }

    return 0;
}

void ge_init_keyboard(ge_win_t win) {
    glfwSetKeyCallback(win, ge_key_callback);
}

u08 ge_check_keyboard_events(ge_keyboard_event_t * e) {
    for (u32 i = 0; i < GLFW_KEY_LAST; i++) {
        if (ge_key(e -> keys[i])) {
            return 1;
        }
    }
    return 0;
} 



