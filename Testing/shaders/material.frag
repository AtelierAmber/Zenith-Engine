#version 400 core
in vec4 Color;
in vec2 UV;

out vec4 outColor;

uniform sampler2D tex;

void main(){
  outColor = texture(tex, UV) * Color;
}