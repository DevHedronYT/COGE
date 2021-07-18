#ifndef _COGE_MOUSE
    #define _COGE_MOUSE

    #include <gl.h>
    #include <GLFW/glfw3.h>

    void coge_init_mouse();
    void coge_mouse_cursor_pos_callback(GLFWwindow * window, double _x, double _y);
    void coge_mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
    void coge_mouse_wheel_callback(GLFWwindow * window, double _dx, double _dy);
    double coge_get_mouse_pos_x();
    double coge_get_mouse_pos_y();
    double coge_get_mouse_dx();
    double coge_get_mouse_dy();  
    double coge_get_mouse_scroll_dx();    
    double coge_get_mouse_scroll_dy();
    int coge_mouse_button(int button); 
    int coge_mouse_button_changed(int button);
    int coge_mouse_button_down(int button);    
    int coge_mouse_button_up(int button);

#endif
