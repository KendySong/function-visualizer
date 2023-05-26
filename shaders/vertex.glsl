#version 450 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 color;

uniform float maxFunctionOut;

out vec3 g_color;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    float height = vertex.y;
    if (height > maxFunctionOut)
    {
        height = maxFunctionOut;
    }

    if (height < -maxFunctionOut)
    {
        height = -maxFunctionOut;
    }

    g_color = color;
    gl_Position = projection * view * vec4(vertex.x, height, vertex.z, 1);
}