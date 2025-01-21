#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;
uniform mat4 rotation;

void main()
{
    mat4 translation;
    translation[0] = vec4(1.0, 0.0, 0.0, 0.0);
    translation[1] = vec4(0.0, 1.0, 0.0, 0.0);
    translation[2] = vec4(0.0, 0.0, 1.0, 0.0);
    translation[3] = vec4(0.8, 0.0, 0.0, 1.0);

    gl_Position = translation * rotation * vec4(aPos, 1.0);
    color = aColor;
}
