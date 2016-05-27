#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 color;

out VS_OUT {
  vec4 Color;
  vec3 fragPosition;
  vec3 Normal;
  vec4 FragPosLightSpace;
} vs_out;

uniform mat4 model;

uniform mat4 lightSpaceMatrix;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};



void main()
{
	gl_Position = projection*view * model * vec4(position, 1.0f);
	vs_out.fragPosition = vec3(model * vec4(position, 1.0f));
	vs_out.Normal = mat3(transpose(inverse(model))) * normal;
	vs_out.Color = color;

	vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.fragPosition, 1.0);
}