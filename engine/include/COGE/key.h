#ifndef GE_KEY_H
    #define GE_KEY_H 
    
    #include "./ge.h"
    #include <extd_cstd/lib.h>

    typedef struct {
        i32 keys[GLFW_KEY_LAST];
    } ge_keyboard_event_t;
    #define ge_mk_keyboard_event(...) (ge_keyboard_event_t) { {__VA_ARGS__}  }

    void ge_init_keyboard(ge_win_t win);
    void ge_key_callback(ge_win_t window, i32 key, i32 scancode, i32 action, i32 mods);
    u08  ge_key(i32 key);
    u08  ge_key_changed(i32 key);
    u08  ge_key_down(i32 key);
    u08  ge_key_up(i32 key);
    u08  ge_key_held_down(ge_win_t win, i32 key);
    u08  ge_check_keyboard_events(ge_keyboard_event_t * e);


#endif
