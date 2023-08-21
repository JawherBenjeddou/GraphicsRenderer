#version 460 core

layout (location = 0) in vec3 aPos; //IN LOCAL COORDINATE SYSTEMS
layout (location = 1) in vec3 aNormal;

uniform mat4 model; 
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position = projection * view * model * vec4(aPos,1.0f);
    FragPos = vec3(model * vec4(aPos, 1.0));
    // Transform the normal using the normal matrix
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    Normal = normalize(normalMatrix * aNormal);
}