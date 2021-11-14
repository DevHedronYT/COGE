
#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 tex_pos;
layout (location = 2) in float z;

uniform mat4 projection;
uniform mat4 rotation;
uniform mat4 view;

out vec2 tex_coord;
out float zz;

void main() {
    gl_Position = projection * view * rotation * vec4(pos, 0, 1);
    tex_coord = tex_pos;
    zz = z;
}
