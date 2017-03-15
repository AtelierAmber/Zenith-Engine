#version 400 core
in vec4 Color;
in vec3 Normal;
in vec3 LightVector;

out vec4 outColor;

uniform vec3 lightColor;

void main(){
  vec3 unitNormal = normalize(Normal);
  vec3 unitLight = normalize(LightVector);
  
  float nDot1 = dot(unitNormal, unitLight);
  float brightness = max(nDot1, 0.0f);
  vec3 diffuse = brightness * lightColor;
  
  outColor = vec4(diffuse, 1.0f);
}