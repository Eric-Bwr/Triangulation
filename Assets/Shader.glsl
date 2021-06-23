#vertex
#version 330 core

void main() {
    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}

#geometry
#version 330 core

layout (points) in;
layout (line_strip, max_vertices = 4) out;

uniform float time;

void drawLine(){
    gl_Position = gl_in[0].gl_Position + vec4(sin(time), -0.25, 0.0, 0.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(+0.25, +0.25, 0.0, 0.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(sin(time), -0.5, 0.0, 0.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(+0.25, sin(time), 0.0, 0.0);
    EmitVertex();
}

void main(){
    drawLine();
    EndPrimitive();
}

#fragment
#version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}