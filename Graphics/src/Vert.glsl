#version 460 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;
out vec4 color;
uniform vec4 u_Color;
void main()
{
gl_Position = aPos; 
color = u_Color; 
};