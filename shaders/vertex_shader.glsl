#version 330 core

layout (location=0) in vec4 position;
layout (location=1) in vec4 color;
layout (location=2) in vec4 ratio;

out vec4 vcolor;

uniform mat4 projectionMatrix;
uniform vec4 pos;

void main(void)
{
vcolor=color;
gl_Position = projectionMatrix * position;

}