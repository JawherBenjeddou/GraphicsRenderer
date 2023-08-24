#version 460 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightCubePos;
uniform vec3 camerapos;



void main()
{
	//Ambient
	//-------
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	

	//Diffuse
	//--------
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightCubePos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	//Specular
	//--------
	float specularStrength = 0.5f;
	//View direction from the camera to the object
	vec3 viewdir = normalize(camerapos - FragPos); 
	// We negate the light direction bcs reflet() expect the first vector to point from the light  src towards fragments pos
	vec3 reflectDir = reflect(-lightDir,norm);
	//Calculate the specular light angle using dot product 
	//32 value is the shininess of the highlight (the higher the lower the impact)
	float specular = pow(max(dot(viewdir, reflectDir), 0.0), 32);

	vec3 spec = specular * specularStrength * lightColor;

	

	//Final Result
	//------------
	vec3 result = (ambient + diffuse + spec ) * objectColor;
	FragColor = vec4(result, 1.0);
}