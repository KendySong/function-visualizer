#version 450 core
in vec3 g_color;

out vec4 o_color;

void main()
{
    o_color = vec4(g_color, 1);
}