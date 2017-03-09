#version 400 core
in vec3 position;
in vec4 color;
in vec3 normal;

flat out vec4 Color;

uniform mat4 transform;
uniform mat4 projection;

void main(){
    gl_Position = projection * transform * vec4(position, 1.0);
    Color = color;
}