#vertex
#version 330 core

void main() {
    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}

    #geometry
    #version 330 core

#define VERT 400

layout (points) in;
layout (line_strip, max_vertices = 800) out;

uniform vec2 mouse;
uniform float time;

void drawLine(int index){
    gl_Position = vec4(cos(index) * cos(time), sin(index) * cos(time), 0.0, 1.0);
    EmitVertex();
    gl_Position = vec4(sin(index) * tan(time), cos(index) * sin(time), 0.0, 1.0);
    EmitVertex();
}

void main(){
    for(int i = 0; i < VERT; i++){
        drawLine(i);
    }
   //gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
   //EmitVertex();
   //gl_Position = vec4(mouse.x / 1920 * 1.25 * 1, (1 - (mouse.y / 1080) * 1.25) - 1, 0.0, 1.0);
   //EmitVertex();
    EndPrimitive();
}

    #fragment
    #version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}