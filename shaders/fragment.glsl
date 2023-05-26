#version 450 core
in vec3 g_color;

uniform bool isMeshFunction;
uniform vec3 meshColor;

out vec4 o_color;

void main()
{
    if (isMeshFunction)
    {
        o_color = vec4(meshColor, 1);
    }
    else
    {
        o_color = vec4(g_color, 1);
    }

    
}