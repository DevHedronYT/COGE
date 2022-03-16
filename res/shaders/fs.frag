
#version 330 core

out vec4 FragColor;

in vec2 tex_coord;
in float zz;
in float texture_id;

uniform sampler2D uTexture[2];

void main() {
    int index = int(texture_id);
    FragColor = vec4(0.0f, 100.0f, 1.0f, 1.0f) * texture(uTexture[index], tex_coord);
}

