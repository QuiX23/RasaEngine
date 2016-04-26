#version 330 core
out vec4 color;
in vec2 TexCoords;

uniform sampler2D depthMap;

void main()
{             
	
	float x=gl_FragCoord.x/1200.0f;
	float y=gl_FragCoord.y/800.0f;
    float depthValue = texture(depthMap, vec2(x,y)).r;
	//float depthValue = texture(depthMap,TexCoords ).r;
    color = vec4(vec3(depthValue), 1.0);
} 