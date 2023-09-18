#version 460 core
out vec4 FragColor;


uniform vec3 color;
void main() {
    FragColor = vec4(vec3(0.0f,0.5f,0.5f),1.0f);
}