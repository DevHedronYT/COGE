#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 color;

void main() {
    gl_Position = vec4(aPos, 1.0);

    if (aPos.x < 0.0) {
        color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }

    else if (aPos.x == 0) {
        color = vec4(0.0, 1.0f, 0.0f, 1.0f);
    }

    else {
        color = vec4(0.0f, 0.0f, 1.0f, 1.0f);
    }
}

