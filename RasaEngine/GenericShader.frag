#version 330 core
out vec4 color;

uniform sampler2D shadowMap;


struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct DirectionalLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};

#define NR_POINT_LIGHTS 1
#define NR_DIRECTIONAL_LIGHTS 1

in VS_OUT {
  vec4 Color;
  vec3 fragPosition;
  vec3 Normal;
  vec4 FragPosLightSpace;
} fs_in;


uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform	DirectionalLight directionalLights[NR_DIRECTIONAL_LIGHTS];

uniform vec3 viewPos;


vec3 CalcPointLight(PointLight light, vec3 color, vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 CalcDircetionalLight(DirectionalLight light, vec3 color, vec3 normal, vec3 fragPos, vec3 viewDir);

float ShadowCalculation(DirectionalLight light,vec3 normal, vec4 fragPosLightSpace);


void main()
{
	vec3 result;
	vec3 viewDir = normalize(viewPos - fs_in.fragPosition);
	vec3 norm = normalize(fs_in.Normal);
	vec3 fragColor= vec3(fs_in.Color.x,fs_in.Color.y,fs_in.Color.z);

////	for (int i = 0; i < NR_POINT_LIGHTS; i++)
//	//	result += CalcPointLight(pointLights[i], material, norm, fragPosition, viewDir);
	for (int i = 0; i < NR_DIRECTIONAL_LIGHTS; i++)
	{
		result += CalcDircetionalLight(directionalLights[i], fragColor, norm, fs_in.fragPosition, viewDir);
		
	}


	color = vec4(result, 1.0f);
}

// Calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 color, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// Diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// Specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0);
	// Attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	// Combine results
	vec3 ambient = light.ambient * color;
	vec3 diffuse = light.diffuse * diff * color;
	vec3 specular = light.specular * spec * color;
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient +( diffuse + specular));
}

vec3 CalcDircetionalLight(DirectionalLight light,vec3 color, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	float shadow = ShadowCalculation(light,normal, fs_in.FragPosLightSpace); 

	vec3 lightDir =normalize(-light.direction);
	// Diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// Specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0);

	// Combine results
	vec3 ambient = light.ambient * color;
	vec3 diffuse = light.diffuse * diff * color;
	vec3 specular = light.specular * spec * color;

	return (ambient +(1.0-shadow)*( diffuse + specular));//(ambient +(1.0-shadow)*( diffuse + specular));
}

float ShadowCalculation(DirectionalLight light,vec3 normal, vec4 fragPosLightSpace)
{
	vec3 lightDir =normalize(-light.direction);
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // Check whether current frag pos is in shadow
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005); 
    float shadow = currentDepth -bias > closestDepth  ? 1.0 : 0.0;  

	//gl_FragDepth =closestDepth;

	if(projCoords.z >= 1.0)
        shadow = 0.0;

    return shadow;
} 

