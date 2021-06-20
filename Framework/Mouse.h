#ifndef _COGE_MOUSE
    #define _COGE_MOUSE

    #include "External/GLAD/gl.h"
    #include "External/GLFW/glfw3.h"


    // Declarations
    double x, y;
    double lastX, lastY;
    double dx, dy;
    double scrollDX, scrollDY;
    int firstMouse; 
    int buttons[GLFW_MOUSE_BUTTON_LAST + 1];
    int buttonsChanged[GLFW_MOUSE_BUTTON_LAST + 1];


    void InitMouse();
    void CursorPosCallback(GLFWwindow *window, double _x, double _y);
    void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    double GetMouseX();
    double GetMouseY();
    double GetDX();
    double GetDY();  
    double GetScrollDX();    
    double GetScrollDY();
    int Button(int button); 
    int ButtonChanged(int button);
    int ButtonDown(int button);    
    int ButtonUp(int button);


    // Implementation
    void InitMouse() {
	x = 0;
	y = 0;

	lastX = 0;
	lastY = 0;

	dx = 0;
	dy = 0;

	scrollDX = 0;
	scrollDY = 0;

	firstMouse = 1;
	int i;
	for (i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; i++) {
	    buttons[i] = 0;
	    buttonsChanged[i] = 0;
	}
    }

    void CursorPosCallback(GLFWwindow * window, double _x, double _y) {
	x = _x;
	y = _y;

	if (firstMouse) {
	    lastX = x;
	    lastY = y;

	    firstMouse = 0;
	}

	dx = x - lastX;
	dy = y - lastY;

	lastX = x;
	lastY = y;
    }

    void MouseButtonCallback(GLFWwindow * window, int button, int action, int mods) {
	if (action != GLFW_RELEASE) {
	    if (!buttons[button]) {
		buttons[button] = 1;
	    }
	}

	else {
	    buttons[button] = 0;
	}
	
	buttonsChanged[button] = action != GLFW_REPEAT;
    }

    void MouseWheelCallback(GLFWwindow * window, double _dx, double _dy) {
	scrollDX = _dx;
	scrollDY = _dy;
    }

    double GetMouseX() {
	return x;
    }
    double GetMouseY() {
	return y;
    }

    double GetDX() {
	double _dx = dx;
	dx = 0;

	return _dx;
    }
    double GetDY() {
	double _dy = dy;
	dy = 0;

	return _dy;
    }

    double GetScrollDX() {
	double sdx = scrollDX;
	scrollDX = 0;

	return sdx;
    }
    double GetScrollDY() {
	double sdy = scrollDY;
	scrollDY = 0;

	return sdy;
    }

    int Button(int button) {
	return buttons[button];
    }

    int ButtonChanged(int button) {
	int ret = buttonsChanged[button];
	buttonsChanged[button] = 0;

	return ret;
    }

    int ButtonDown(int button) {
	return buttons[button] && ButtonChanged(button); 
    }

    int ButtonUp(int button) {
	return !buttons[button] && ButtonChanged(button);
    }

#endif
