#version 400 core
in vec3 position;
in vec4 color;
in vec3 normal;

out vec3 Normal;
out vec3 LightVector;
out vec4 Color;

uniform mat4 transform;
uniform mat4 projection;
uniform vec3 lightPos;

void main(){
  vec4 worldPosition = transform * vec4(position, 1.0f);

  gl_Position = projection * worldPosition;
  Color = color;
  Normal = (transform * vec4(normal, 1.0f)).xyz;
  LightVector = lightPos - worldPosition.xyz;
}