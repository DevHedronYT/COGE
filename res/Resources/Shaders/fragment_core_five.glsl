#version 330 core

out vec4 FragColor;
in vec4 ourColor;
in vec2 TexCoord;

in float v_TexIndex;

uniform sampler2D u_Textures[3];

void main() {

    int index = int(v_TexIndex);

    if (index == 0)  FragColor = ourColor;
    else FragColor = texture(u_Textures[index], TexCoord);
    
}


