#version 460 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TextPos;

struct Material {
    sampler2D diffuseMAP;
    sampler2D specularMAP;
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

void main() {
    // ambient
    vec3 ambient = u_light.ambientStrength * vec3(texture(u_material.diffuseMAP, TextPos));

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
        vec3 diffuse = u_light.diffuseStrength   * texture(u_material.diffuseMAP, TextPos).rgb;

        // Specular
        vec3 viewDir = normalize(u_camerapos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
        vec3 specular = u_light.specularStrength * (spec * vec3(texture(u_material.specularMAP, TextPos)));

        // Attenuation
        float distance = length(u_viewposition - FragPos);
        float attenuation = 1.0 / (u_PointLight.constant + u_PointLight.linear * distance + u_PointLight.quadratic * (distance * distance));
  
        ambient *= attenuation;
        diffuse *= intensity;
        specular *= intensity;

        FragColor = vec4(ambient + diffuse + specular, 1.0);

}