#ifndef GE_JOYSTICK_H

    #define GE_JOYSTICK_H 
    #include <extd_cstd/lib.h>


    #define GE_JOYSTICK_BTN_LEFT 0
    #define GE_JOYSTICK_BTN_DOWN 1
    #define GE_JOYSTICK_BTN_RIGHT 2
    #define GE_JOYSTICK_BTN_UP 3	
    #define GE_JOYSTICK_SHOULDER_LEFT 4
    #define GE_JOYSTICK_SHOULDER_RIGHT 5	
    #define GE_JOYSTICK_TRIGGER_LEFT 6
    #define GE_JOYSTICK_TRIGGER_RIGHT 7
    #define GE_JOYSTICK_SELECT 8		
    #define GE_JOYSTICK_START 9			
    #define GE_JOYSTICK_LEFT_STICK 10				
    #define GE_JOYSTICK_RIGHT_STICK 11		   	        
    #define GE_JOYSTICK_HOE 12			
    #define GE_JOYSTICK_CLICK 13	
    #define GE_JOYSTICK_DPAD_UP 14				
    #define GE_JOYSTICK_DPAD_RIGHT 15		
    #define GE_JOYSTICK_DPAD_DOWN 16			
    #define GE_JOYSTICK_DPAD_LEFT 17		

    void ge_init_joystick(u16 i);
    u08  ge_get_joystick_id(u16 i);
    void ge_update_joystick();    
    void ge_init_joystick(u16 i);
    f32  ge_get_joystick_axes_state(i32 axis);
    u08  ge_joystick_btn_state(i32 btn);
    u32  ge_get_joystick_axes_count();
    u32  ge_get_joystick_btn_count();
    u08  ge_is_joystick_present();
    const char * ge_get_joystick_name();


#endif
