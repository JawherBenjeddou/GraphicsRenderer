#version 460 core
out vec4 FragColor;


in vec3 Normal;
in vec3 FragPos;
in vec2 TextPos;


uniform vec3 camerapos;

struct Material{
	sampler2D diffuseMAP; //reference to 2D texture 
	vec3 specular;

	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambientStrength;
	vec3 diffuseStrength;
	vec3 specularStrength;
};

uniform Light light;
uniform Material material;

void main()
{
	// ambient
	vec3 ambient = light.ambientStrength * vec3(texture(material.diffuseMAP, TextPos));
	
	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);

	//Changed the lightcolor from the vec3 to the struct for all lighting
	vec3 diffuse = light.diffuseStrength * diff * vec3(texture(material.diffuseMAP,TextPos));
	
	// specular
	vec3 viewDir = normalize(camerapos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shininess);
	vec3 specular = light.specularStrength * (spec * material.specular);
	
	
	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
}