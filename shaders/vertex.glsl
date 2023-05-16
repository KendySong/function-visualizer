#version 450 core
layout (location = 0) in vec3 vertex;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * transform * vec4(vertex, 1);
}