#version 330 core

out vec4 FragColor;
in vec4 outColor;
in vec2 texPos;

uniform sampler2D u_Tex;

void main(){

    FragColor=texture(u_Tex,texPos);
}
