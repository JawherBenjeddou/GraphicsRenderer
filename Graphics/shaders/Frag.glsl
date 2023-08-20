#version 460 core
out vec4 FragColor;
in vec2 texCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float visibility;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	FragColor = vec4(lightColor * objectColor, 1.0);
}