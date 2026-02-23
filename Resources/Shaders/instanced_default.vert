#version 330 core

layout(location=0) in vec3 vPos;
layout(location=1) in vec3 vCol;
layout(location=2) in vec2 vTex;
layout(location=3) in vec3 model1;

out vec4 outColor;
out vec2 texPos;

uniform mat4 VP;

void main(){
    
    gl_Position=VP*vec4(vPos+model1,1.0f);

    texPos=vTex;
    outColor=vec4(vCol,1.0f);

}