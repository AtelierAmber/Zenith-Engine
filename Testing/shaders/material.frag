#version 400 core
flat in vec4 Color;
flat in vec2 UV;

out vec4 outColor;

uniform sampler2D tex;

void main(){
  outColor = texture(tex, UV) * Color;
}