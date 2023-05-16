#version 450 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 color;

out vec3 g_color;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    g_color = color;
    gl_Position = projection * view * transform * vec4(vertex, 1);
}