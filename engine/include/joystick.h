#ifndef __GE_JOYSTICK__

    #define __GE_JOYSTICK__
    #include <ge.h>


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

    emp_t ge_init_joystick(u16_t i);
    u08_t ge_get_joystick_id(u16_t i);
    emp_t ge_update_joystick();    
    emp_t ge_init_joystick(u16_t i);
    f32_t ge_get_joystick_axes_state(i32_t axis);
    u08_t ge_joystick_btn_state(i32_t btn);
    u32_t ge_get_joystick_axes_count();
    u32_t ge_get_joystick_btn_count();
    u08_t ge_is_joystick_present();
    const str_t ge_get_joystick_name();


#endif
