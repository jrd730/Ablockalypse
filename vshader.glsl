#version 150

in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;

uniform vec3 xlate;

void main() 
{
    color = vColor;
    gl_Position = vec4(vPosition.x+xlate[0], vPosition.y+xlate[1], vPosition.zw);
} 