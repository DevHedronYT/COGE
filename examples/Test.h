#ifndef _COGE_TEST
#define _COGE_TEST

#include <GLFW/glfw3.h>
#include <gl.h>

// Credits: https://github.com/templalizer1284/cshader

#include <ibo.h>
#include <joystick.h>
#include <keyboard.h>
#include <log.h>
#include <mouse.h>
#include <shader.h>
#include <tex.h>
#include <util.h>
#include <vao.h>
#include <vbo.h>

GLFWwindow *window;
unsigned int shaderID;
int uLocation;
coge_program_props_t props;

void Init();
void Update();
void RenderBegin(float r, float g, float b, float a) {
    coge_clear_screen(r, g, b, a);
}

void Render();

void RenderEnd() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Destroy() {
    glUseProgram(0);
    glfwTerminate();
}

void ResetULoc() { uLocation = -1; }

void Run() {
    Init();

    while (!glfwWindowShouldClose(window)) {
        Update();
        Render();
    }

    Destroy();
}

#endif
