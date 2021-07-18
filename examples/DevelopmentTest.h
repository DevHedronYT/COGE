#pragma once 

#include "Test.h"

coge_texture_t tex;
float vertices[20] = {
 	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f        
};


unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
};

unsigned int vertexNum;
unsigned int columns;

float movementVec[4] = {
    0, 0, 0, 0
};


void Init() {
    window = coge_window_init(640, 480, "Dev Testing");
    shaderID = coge_load_shader("res/Shaders/vertex_core_one.glsl", "res/Shaders/fragment_core_one.glsl");

    glUseProgram(0);
    glUseProgram(shaderID);

    tex.m_path = "res/Images/Hedron.png";
    tex.m_slot = 0;

    coge_gen_texture_t(&tex);
    coge_bind_texture_t(&tex); 

    props = coge_gen_program_props_t(vertices, indices, sizeof(vertices), sizeof(indices), GL_STATIC_DRAW, GL_STATIC_DRAW);
   
    vertexNum = sizeof(indices) / sizeof(indices[0]);
    columns = 5;


    unsigned int index[2]  = { 0, 1 };
    int size[4]            = { 3, 2 };
    /*    long stride            = sizeof(Vertex);
          int pointers[4]        = { offsetof(Vertex, Position), offsetof(Vertex, Color), offsetof(Vertex, TexCoords), offsetof(Vertex, TexID) }; */

    int stride = columns * sizeof(float);
    long pointers[2] = { 0, 3 * sizeof(float) };
    int vertex_pointer_num = 2;
    
    int i;

    for (i = 0; i < vertex_pointer_num; i++) {
        glEnableVertexAttribArray(index[i]);
        glVertexAttribPointer(index[i], size[i], GL_FLOAT, GL_FALSE, stride, (void *) pointers[i]);
    }


    uLocation = glGetUniformLocation(shaderID, "uTexture");
    glUniform1i(uLocation, tex.m_slot);
    ResetULoc();

    coge_init_keyboard();
    glfwSetKeyCallback(window, coge_keyboard_key_callback);

    coge_init_mouse();
    glfwSetCursorPosCallback(window, coge_mouse_cursor_pos_callback);
    glfwSetMouseButtonCallback(window, coge_mouse_button_callback);
    glfwSetScrollCallback(window, coge_mouse_wheel_callback);
    
    coge_init_joystick(0);
    coge_update_joystick();

    if (coge_is_joystick_present()) {
	coge_log_warning("No Joystick", NULL);
    }

    else {
	coge_log_warning("No Joystick", NULL);
    }

    uLocation = glGetUniformLocation(shaderID, "move");
    glUseProgram(0);
}

void Update() {
    
    if (coge_keyboard_key_down(GLFW_KEY_R)) {
	movementVec[0] = 0;
	movementVec[1] = 1;
	movementVec[2] = 2;
	movementVec[3] = 3;
    }

    if (coge_keyboard_key_held_down(window, GLFW_KEY_W)) {
	if (movementVec[3] >= 2) {
	    movementVec[3] -= 0.5;
	}
    }

    if (coge_keyboard_key_held_down(window, GLFW_KEY_S)) {
	movementVec[3] += 1;
    }


    if (coge_keyboard_key_held_down(window, GLFW_KEY_LEFT) || coge_keyboard_key_held_down(window, GLFW_KEY_A)) {
	movementVec[0] += 0.1; 
    }

    if (coge_keyboard_key_held_down(window, GLFW_KEY_RIGHT) || coge_keyboard_key_held_down(window, GLFW_KEY_D)) {
	movementVec[0] -= 0.1; 
    }

    if (coge_keyboard_key_held_down(window, GLFW_KEY_UP)) {
	movementVec[1] -= 0.1;
    }

    if (coge_keyboard_key_held_down(window, GLFW_KEY_DOWN)) {
	movementVec[1] += 0.1;
    }


    glUseProgram(shaderID);
    glUniform4f(uLocation, movementVec[0], movementVec[1], movementVec[2], movementVec[3]);
}

void Render() {
    RenderBegin(0.2f, 0.3f, 0.5f, 1.0f);

	coge_draw_vertices(vertexNum);

    RenderEnd();
}

