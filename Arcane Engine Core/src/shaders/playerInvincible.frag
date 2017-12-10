#version 430 core

// Does AMD support sampler2D in a struct?
struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_specular1;
	sampler2D texture_specular2;
	samplerCube skyboxCubemap;
	float shininess;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define NR_POINT_LIGHTS 1

in vec2 aTexCoords;
in vec3 aNormal;
in vec3 aFragPos;

out vec4 color;

uniform Material material;
uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform float time;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 fragToCam);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 fragToCam);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 fragToCam);

void main() {
	float textureAlpha = texture(material.texture_diffuse1, aTexCoords).w;

	vec3 norm = normalize(aNormal);
	vec3 fragToCam = normalize(viewPos - aFragPos);
	
	vec3 result = CalcDirLight(dirLight, norm, fragToCam);
	for(uint i = 0; i < NR_POINT_LIGHTS; ++i) {
		result += CalcPointLight(pointLights[i], norm, aFragPos, fragToCam);
	}
	result += CalcSpotLight(spotLight, norm, aFragPos, fragToCam);
	
	// Use the environment map (skybox) to add some detail to the body of the player
	vec3 refractVec = refract(-fragToCam, norm, 1.0 / 1.33); // Refractive index when going from air to water
	vec3 refractCol = texture(material.skyboxCubemap, refractVec).rgb;

	// Result
	color = vec4(refractCol, 1.0); // Use the diffuse texture for transparency
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 fragToCam) {
	vec3 lightDirection = normalize(-light.direction);

	float diff = max(dot(lightDirection, normal), 0.0);

	vec3 halfwayDir = normalize(fragToCam + lightDirection);
	float spec = pow(max(dot(halfwayDir, normal), 0.0), material.shininess);

	vec3 ambient = light.ambient * texture(material.texture_diffuse1, aTexCoords).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse1, aTexCoords).rgb;
	vec3 specular = light.specular * spec * texture(material.texture_specular1, aTexCoords).rgb;
	//vec3 emission = texture(material.emission, aTexCoords).rgb * clamp((sin(time) * 2) - 1, 0, 1);
	
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 fragToCam) {
	vec3 lightDirection = normalize(light.position - fragPos);

	float diff = max(dot(lightDirection, normal), 0.0);

	vec3 halfwayDir = normalize(lightDirection + fragToCam);
	float spec = pow(max(dot(halfwayDir, normal), 0.0), material.shininess);

	// Attenuation calculation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	vec3 ambient = light.ambient * texture(material.texture_diffuse1, aTexCoords).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse1, aTexCoords).rgb;
	vec3 specular = light.specular * spec * texture(material.texture_specular1, aTexCoords).rgb;
	//vec3 emission = texture(material.emission, aTexCoords).rgb * clamp((sin(time) * 2) - 1, 0, 1);

	// Apply attenuation
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 fragToCam) {
	vec3 fragToLight = normalize(light.position - fragPos);

	float diff = max(dot(fragToLight, normal), 0.0);

	vec3 halfwayDir = normalize(fragToLight + fragToCam);
	float spec = pow(max(dot(halfwayDir, normal), 0.0), material.shininess);

	// Attenuation calculation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	// Check if it is in the spotlight's circle
	float theta = dot(normalize(light.direction), -fragToCam);
	float difference = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / difference, 0.0, 1.0);

	vec3 ambient = light.ambient * texture(material.texture_diffuse1, aTexCoords).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse1, aTexCoords).rgb;
	vec3 specular = light.specular * spec * texture(material.texture_specular1, aTexCoords).rgb;
	//vec3 emission = texture(material.emission, aTexCoords).rgb * clamp((sin(time) * 2) - 1, 0, 1);

	// Apply attenuation
	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	return (ambient + diffuse + specular);
}