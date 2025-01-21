#version 460 core

layout (location = 0) in vec3 aPos;

uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 translation;

void main()
{
    gl_Position = rotation * translation * scale * vec4(aPos, 1.0);
}
