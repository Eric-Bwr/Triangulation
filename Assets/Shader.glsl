#vertex
#version 330 core

void main() {
    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}

    #geometry
    #version 330 core

#define POINTS 100
#define POINTS_VERT 200

layout (points) in;
layout (line_strip, max_vertices = POINTS_VERT) out;

uniform vec2 mouse;
uniform vec2 coords[POINTS];

void drawPoint(int index){
    gl_Position = vec4(coords[index].x, coords[index].y, 0.0, 1.0);
    EmitVertex();
}

void main(){
    for(int i = 0; i < POINTS; i += 2){
        drawPoint(i);
    }
   //gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
   //EmitVertex();
   //gl_Position = vec4(mouse.x / 1920 * 1.25 * 1, (1 - (mouse.y / 1080) * 1.25) - 1, 0.0, 1.0);
   //EmitVertex();
    EndPrimitive();
}

    #fragment
    #version 330 core

uniform float time;

out vec4 FragColor;

void main() {
    FragColor = vec4(sin(time) + 1 / 2, cos(time) + 1 / 2, tan(time) + 1 / 2, 1.0);
}