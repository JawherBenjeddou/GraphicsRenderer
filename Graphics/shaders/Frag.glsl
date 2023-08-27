#version 460 core
out vec4 FragColor;


in vec3 Normal;
in vec3 FragPos;
in vec2 TextPos;

struct Material{
	sampler2D diffuseMAP; //reference to 2D texture 
	sampler2D specularMAP;

	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambientStrength;
	vec3 diffuseStrength;
	vec3 specularStrength;
};

uniform vec3 u_camerapos;
uniform Light u_light;
uniform Material u_material;

void main()
{
	// ambient
	vec3 ambient = u_light.ambientStrength * vec3(texture(u_material.diffuseMAP, TextPos));
	
	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(u_light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);

	//Changed the lightcolor from the vec3 to the struct for all lighting
	vec3 diffuse = u_light.diffuseStrength * diff * vec3(texture(u_material.diffuseMAP,TextPos));
	
	// specular
	vec3 viewDir = normalize(u_camerapos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0),u_material.shininess);
	vec3 specular = u_light.specularStrength * (spec * vec3(texture(u_material.specularMAP, TextPos))); //TODO material.specular becomes a sampler2D and bind it to the metal border texture 
	
	
	FragColor = vec4(ambient + diffuse + specular,1.0);
}