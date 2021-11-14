#ifndef __GE_KEY__
    #define __GE_KEY__
    
    #include <ge.h>

    emp_t ge_init_keyboard(ge_win_t win);
    emp_t ge_key_callback(ge_win_t window, i32_t key, i32_t scancode, i32_t action, i32_t mods);
    u08_t ge_key(i32_t key);
    u08_t ge_key_changed(i32_t key);
    u08_t ge_key_down(i32_t key);
    u08_t ge_key_up(i32_t key);
    u08_t ge_key_held_down(ge_win_t win, i32_t key);



#endif
