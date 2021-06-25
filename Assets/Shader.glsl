#vertex
#version 330 core

void main() {
    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}

#geometry
#version 330 core

#define POINTS 1

layout (points) in;
layout (line_strip, max_vertices = 20) out;

uniform vec2[1] coords;

void drawLine(int index){
    gl_Position = vec4(coords[index].x, coords[index].y, 0.0, 1.0);
    EmitVertex();
    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
    EmitVertex();
}

void main(){
    for(int i = 0; i < POINTS; i++)
        drawLine(i);
    EndPrimitive();
}

#fragment
#version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.0, 1.0, 1.0);
}