#ifndef _COGE_JOYSTICK 

    #define _COGE_JOYSTICK
    #include <gl.h>
    #include <GLFW/glfw3.h>
				
    #define COGE_JOYSTICK_BTN_LEFT 0
    #define COGE_JOYSTICK_BTN_DOWN 1
    #define COGE_JOYSTICK_BTN_RIGHT 2
    #define COGE_JOYSTICK_BTN_UP 3	
    #define COGE_JOYSTICK_SHOULDER_LEFT 4
    #define COGE_JOYSTICK_SHOULDER_RIGHT 5	
    #define COGE_JOYSTICK_TRIGGER_LEFT 6
    #define COGE_JOYSTICK_TRIGGER_RIGHT 7
    #define COGE_JOYSTICK_SELECT 8		
    #define COGE_JOYSTICK_START 9			
    #define COGE_JOYSTICK_LEFT_STICK 10				
    #define COGE_JOYSTICK_RIGHT_STICK 11		   	        
    #define COGE_JOYSTICK_HOE 12			
    #define COGE_JOYSTICK_CLICK 13	
    #define COGE_JOYSTICK_DPAD_UP 14				
    #define COGE_JOYSTICK_DPAD_RIGHT 15		
    #define COGE_JOYSTICK_DPAD_DOWN 16			
    #define COGE_JOYSTICK_DPAD_LEFT 17		

    //       PS                    XBox
    //	Square		|	X
    //	X		|	A
    //	Circle		|	B
    //	Triangle	|	Y
    //	L1		|	LB
    //	R1		|	RB
    //	L2		|	LT
    //	R2		|	RT
    //	Share		|	Address
    //	Options		|	Menu
    //	L3		|	LS
    //	R3		|	RS
    //	Home		|	Home
    //	Touch pad	|	n/a
    //	Dpad up		|	Dpad up
    //	Dpad right	|	Dpad right
    //	Dpad down	|	Dpad down
    //	Dpad left	|	Dpad left

    // Declarations
    int 	  coge_get_joystick_id(int i);
    void 	  coge_update_joystick();
    void	  coge_init_joystick(int i);
    float 	  coge_joystick_axes_state(int axis);
    unsigned char coge_joystick_button_state(int button);
    int 	  coge_get_joystick_axes_count();    
    int 	  coge_get_joystick_button_count();
    int 	  coge_is_joystick_present();
    const char *  coge_get_joystick_name();

#endif
