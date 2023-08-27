#version 460 core

layout (location = 0) in vec3 aPos; //IN LOCAL COORDINATE SYSTEMS
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;

uniform mat4 model; 
uniform mat4 view;
uniform mat4 projection;

uniform mat4 u_normalMatrix;

out vec3 Normal;
out vec3 FragPos;
out vec2 TextPos;
void main()
{
    gl_Position = projection * view * model * vec4(aPos,1.0f);
    FragPos = vec3(model * vec4(aPos, 1.0));
  
    Normal = normalize(mat3(u_normalMatrix) * aNormal);

    TextPos = aTexture;
}