#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexture;

out vec4 color;
out vec2 texCoord;

uniform mat4 transform;
void main()
{
    gl_Position =transform * vec4(aPos,1.0f);
    color = vec4(aColor,1.0f);
    texCoord = aTexture;
}