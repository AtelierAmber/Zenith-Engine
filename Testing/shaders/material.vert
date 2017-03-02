#version 400 core
in vec3 position;
in vec4 color;
in vec2 uv;
in vec3 normal;

flat out vec4 Color;
flat out vec2 UV;

uniform mat4 transform;
uniform mat4 projection;
uniform vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);

void main(){
    gl_Position = projection * transform * vec4(position, 1.0);
    Color = lightColor * color;
    UV = uv;
}