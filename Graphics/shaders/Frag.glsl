#version 460 core
out vec4 FragColor;
in vec2 texCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float visibility;
void main()
{
	FragColor = mix(texture(texture1, texCoord),texture(texture2, texCoord), visibility);
};