#version 330 core

in vec3 position;
in vec4 color;
in vec4 ratio;

out vec4 pos;
out vec4 scolor;

uniform mat4 aMat;
uniform mat4 bMat;
uniform mat4 cMat;
uniform mat4 dMat;

int main()
{
scolor = color;
pos = (ratio[0]*aMat + ratio[1]*bMat + ratio[2]*cMat + ratio[3]*dMat)*vec4(position, 1.0);
}