#vertex
#version 330 core

void main() {
    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}

#geometry
#version 330 core

#define VERT 400

layout (points) in;
layout (line_strip, max_vertices = VERT) out;

uniform float time;



// A single iteration of Bob Jenkins' One-At-A-Time hashing algorithm.
uint hash( uint x ) {
    x += ( x << 10u );
    x ^= ( x >>  6u );
    x += ( x <<  3u );
    x ^= ( x >> 11u );
    x += ( x << 15u );
    return x;
}

// Compound versions of the hashing algorithm I whipped together.
uint hash( uvec2 v ) { return hash( v.x ^ hash(v.y)                         ); }
uint hash( uvec3 v ) { return hash( v.x ^ hash(v.y) ^ hash(v.z)             ); }
uint hash( uvec4 v ) { return hash( v.x ^ hash(v.y) ^ hash(v.z) ^ hash(v.w) ); }

// Construct a float with half-open range [0:1] using low 23 bits.
// All zeroes yields 0.0, all ones yields the next smallest representable value below 1.0.
float floatConstruct( uint m ) {
    const uint ieeeMantissa = 0x007FFFFFu; // binary32 mantissa bitmask
    const uint ieeeOne      = 0x3F800000u; // 1.0 in IEEE binary32

    m &= ieeeMantissa;                     // Keep only mantissa bits (fractional part)
    m |= ieeeOne;                          // Add fractional part to 1.0

    float  f = uintBitsToFloat( m );       // Range [1:2]
    return f - 1.0;                        // Range [0:1]
}

float random( float x ) { return floatConstruct(hash(floatBitsToUint(x))); }

void drawLine(int index){
    gl_Position = gl_in[0].gl_Position + vec4(cos(index) * cos(time), sin(index) * tan(time), 0.0, 0.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(sin(index) * tan(time), cos(index) * sin(time), 0.0, 0.0);
    EmitVertex();
}

void main(){
    for(int i = 0; i < VERT; i++)
        drawLine(i);
    EndPrimitive();
}

#fragment
#version 330 core

uniform float time;

out vec4 FragColor;

void main() {
    FragColor = vec4(sin(time) + 1 / 2, cos(time) + 1 / 2, tan(time) + 1 / 2, 1.0);
}