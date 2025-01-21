#version 460 core

struct Light
{
    vec3 position;
    vec4 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 attenuation_coeffs;
    float cut_off;
    float outer_cut_off;
};

in vec3 Norm;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 cameraPos;
uniform Light light;

void main()
{
    // common
    vec3 norm = normalize(Norm);
    vec3 lightDir = light.direction.w > 0.0f ?
        normalize(light.position.xyz - FragPos) :
        normalize(-light.direction.xyz);
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    // ambient light
    vec3 ambient = 0.05 * light.ambient;

    // diffuse light
    float diffuseIntensity = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = light.diffuse;

    // specular light
    float spec = pow(max(dot(norm, halfwayDir), 0.0f), 512.0f);
    vec3 specular = spec * light.specular;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0f);
}
