#version 460 core

struct Material
{
    vec3 diffuse;
    vec3 specular;

    float shininess;
    float ambient_strength;
};

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
uniform Material material;
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
    vec3 ambient = material.ambient_strength * light.ambient * material.diffuse;

    // diffuse light
    float diffuseIntensity = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diffuseIntensity * light.diffuse * material.diffuse;

    // specular light
    float spec = pow(max(dot(norm, halfwayDir), 0.0f), material.shininess);
    vec3 specular = spec * light.specular * material.specular;

    if (light.direction.w > 0.0f)
    {
        if (light.cut_off > 0.0f)
        {
            // spotlight settings
            float theta = dot(lightDir, normalize(-light.direction.xyz));
            float epsilon = (light.cut_off - light.outer_cut_off);
            float intensity = smoothstep(0.0, 1.0, (theta - light.outer_cut_off) / epsilon);
            diffuse  *= intensity;
            specular *= intensity;
        }

        // attenuation settings
        float distance = length(light.position - FragPos);
        float attenuation = 1.0f / (
            light.attenuation_coeffs.x +
            light.attenuation_coeffs.y * distance +
            light.attenuation_coeffs.z * distance * distance
        );

        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;
    }

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0f);
}
