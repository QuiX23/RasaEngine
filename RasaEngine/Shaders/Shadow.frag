#version 330 core
out vec4 color;

float near = 1.0; 
float far  = 20.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{             
    //float depth = LinearizeDepth(gl_FragCoord.z) ; // divide by far for demonstration
    //gl_FragDepth =1.0;
}