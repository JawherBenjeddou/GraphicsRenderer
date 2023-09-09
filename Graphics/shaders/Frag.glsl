#version 460 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TextPos;

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

struct Light {
    vec3 direction;
    vec3 ambientStrength;
    vec3 diffuseStrength;
    vec3 specularStrength;
};

struct PointLights {
    vec3 position;
    float constant;
    float linear;
    float quadratic;
};


uniform vec3 u_viewdirection;
uniform vec3 u_viewposition;
uniform PointLights u_PointLight;
uniform vec3 u_camerapos;
uniform Light u_light;
uniform Material u_material;

vec3 CalcSpotLight()
{
    // ambient
    vec3 ambient = u_light.ambientStrength * vec3(texture(u_material.texture_diffuse1, TextPos));
      // Spotlight calculations
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_viewposition - FragPos);
    float cosTheta = dot(lightDir, normalize(-u_viewdirection));
    float cutoff = cos(radians(12.5f)); // Spotlight cutoff angle in radians
    float outercutoff = cos(radians(17.5f));
    float epsilon = cutoff - outercutoff;
    float intensity = clamp((cosTheta - outercutoff) / epsilon, 0.0, 1.0);
  
 
    // Diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_light.diffuseStrength   * texture(u_material.texture_diffuse1, TextPos).rgb;

    // Specular
    vec3 viewDir = normalize(u_camerapos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = u_light.specularStrength * (spec * vec3(texture(u_material.texture_specular1, TextPos)));

    // Attenuation
    float distance = length(u_viewposition - FragPos);
    float attenuation = 1.0 / (u_PointLight.constant + u_PointLight.linear * distance + u_PointLight.quadratic * (distance * distance));
     diffuse *= intensity;
    specular *= intensity;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
   

   return vec3(ambient + diffuse + specular);
}

vec3 CalcDirLight()
{
      // Spotlight calculations
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-u_light.direction);
    // Diffuse
    float diff = max(dot(lightDir, norm ), 0.0);
    vec3 diffuse = u_light.diffuseStrength   *diff*  texture(u_material.texture_diffuse1, TextPos).rgb;

    // Specular
    vec3 viewDir = normalize(u_camerapos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = u_light.specularStrength * (spec * vec3(texture(u_material.texture_specular1, TextPos)));


   return vec3( diffuse + specular);
}
vec3 CalcPointLight()
{
      // Spotlight calculations
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_PointLight.position - FragPos);

    // Diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_light.diffuseStrength  *diff * texture(u_material.texture_diffuse1, TextPos).rgb;

    // Specular
    vec3 viewDir = normalize(u_camerapos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = u_light.specularStrength * (spec * vec3(texture(u_material.texture_specular1, TextPos)));

    // Attenuation
    float distance = length(u_PointLight.position - FragPos);
    float attenuation = 1.0 / (u_PointLight.constant + u_PointLight.linear * distance + u_PointLight.quadratic * (distance * distance));
    diffuse *= attenuation;
    specular *= attenuation;
   

   return vec3( diffuse + specular);
}


void main() {

    vec3 Output = vec3(0.0f);
    //DIRECTIONAL LIGHT(SUN)
    Output += CalcDirLight();
    //SPOT LIGHT (TORCH)
    Output += CalcSpotLight();
    //POINT LIGHT (LIGHT)
    //Output += CalcPointLight();
    



    FragColor = vec4(Output, 1.0);

}