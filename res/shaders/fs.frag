
#version 330 core

out vec4 FragColor;

in vec2 tex_coord;
in float zz;

uniform sampler2D uTexture;

void main() {
    FragColor = vec4(zz, 1.0f, 1.0f, 1.0f) * texture(uTexture, tex_coord);
}

