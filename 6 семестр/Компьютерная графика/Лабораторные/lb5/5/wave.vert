#define PI 3.1415926535897932384626433832795

uniform float freq;
uniform float amplitude;

varying vec4 vertex_color;

void main() {
    vec4 pos = gl_Vertex;
    pos.y = pos.y + sin(pos.x * PI * freq) * amplitude;
    gl_Position = gl_ModelViewProjectionMatrix * pos;
    vertex_color = gl_Color;
}