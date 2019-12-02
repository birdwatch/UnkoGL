#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 ratio;

out vec4 animated_position;

uniform mat4 aMat;
uniform mat4 bMat;
uniform mat4 cMat;
uniform mat4 dMat;

void main(void)
{
	animated_position = (ratio[0] * aMat + ratio[1] * bMat + ratio[2] * cMat + ratio[3] * dMat) * vec4(position,1.0);
}