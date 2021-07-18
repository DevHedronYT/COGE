#ifndef _COGE_KEYBOARD 
    
    #define _COGE_KEYBOARD

    #include <gl.h>
    #include <GLFW/glfw3.h>

    void coge_init_keyboard();
    void coge_keyboard_key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
    int coge_keyboard_key(int key);
    int coge_keyboard_key_changed(int key);
    int coge_keyboard_key_down(int key);
    int coge_keyboard_key_up(int key);
    int coge_keyboard_key_held_down(GLFWwindow *window, int key);
    int coge_keyboard_key_held_up(GLFWwindow *window, int key);

#endif   
