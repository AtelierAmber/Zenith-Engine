#version 400 core
smooth in vec4 Color;

out vec4 outColor;

uniform vec4 lightColor;

void main(){
  outColor = lightColor * Color;
}