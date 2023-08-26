#version 460 core
out vec4 FragColor;


struct Light {
	vec3 position;
	
	vec3 color;
};
uniform Light light;
void main()
{
	FragColor = vec4(light.color, 1.0);
}