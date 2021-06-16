#pragma once

#include "GLAD/gl.h"
#include "GLFW/glfw3.h"

/* analog input	button values */	
 							        //	PS	        |	XBOX
#define GLFW_JOYSTICK_BTN_LEFT 0				//	Square		|	X
#define GLFW_JOYSTICK_BTN_DOWN 1				//	X		|	A
#define GLFW_JOYSTICK_BTN_RIGHT 2				//	Circle		|	B
#define GLFW_JOYSTICK_BTN_UP 3					//	Triangle	|	Y
#define GLFW_JOYSTICK_SHOULDER_LEFT 4			        //	L1		|	LB
#define GLFW_JOYSTICK_SHOULDER_RIGHT 5			        //	R1		|	RB
#define GLFW_JOYSTICK_TRIGGER_LEFT 6			        //	L2		|	LT
#define GLFW_JOYSTICK_TRIGGER_RIGHT 7		               	//	R2		|	RT
#define GLFW_JOYSTICK_SELECT 8					//	Share		|	Address
#define GLFW_JOYSTICK_START 9					//	Options		|	Menu
#define GLFW_JOYSTICK_LEFT_STICK 10				//	L3		|	LS
#define GLFW_JOYSTICK_RIGHT_STICK 11		   	        //	R3		|	RS
#define GLFW_JOYSTICK_HOE 12					//	Home		|	Home
#define GLFW_JOYSTICK_CLICK 13					//	Touch pad	|	n/a
#define GLFW_JOYSTICK_DPAD_UP 14				//	Dpad up		|	Dpad up
#define GLFW_JOYSTICK_DPAD_RIGHT 15				//	Dpad right	|	Dpad right
#define GLFW_JOYSTICK_DPAD_DOWN 16				//	Dpad down	|	Dpad down
#define GLFW_JOYSTICK_DPAD_LEFT 17				//	Dpad left	|	Dpad left
int present;
int id;
const char * name;
int axesCount;
const float * axes;
int buttonCount;
const unsigned char * JoystickButtons;


int GetJoystickID(int i) {
    return GLFW_JOYSTICK_1 + i;
}

void UpdateJoysticks() {
    present = glfwJoystickPresent(id);

    if (present) {
        name = glfwGetJoystickName(id);
        axes = glfwGetJoystickAxes(id, &axesCount);
        JoystickButtons = glfwGetJoystickButtons(id, &buttonCount);
    }
}

void InitJoysticks(int i) {
    id = GetJoystickID(i);
    UpdateJoysticks();
}

float JoystickAxesState(int axis) {
    if (present) {
        return axes[axis];
    }

    return -1;
}

unsigned char JoystickButtonState(int button) {
    if (present) {
        return JoystickButtons[button];
    }

    return GLFW_RELEASE;
}

int GetJoystickAxesCount() {
    return axesCount;
}

int GetJoystickButtonCount() {
    return buttonCount;
}

int JoystickIsPresent() {
    return present;
}

const char * GetJoystickName() {
    return name;
}


