#include "pch.h"
#include "Bone.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

Bone::Bone(vec3 position, vec3 rotation, float scale)
{
	parent = NULL;
	initialScale = scale;
	quaternion = glm::quat(position);
	initialPosition = position;
}

Bone::Bone(Bone *bone, vec3 rotation, float length)
{
	parent = bone;
	initialScale = length;
	quaternion = glm::quat(rotation);
	initialPosition = vec3(0.0f, 0.0f, 1.0f);
}

Bone::~Bone()
{
}

void Bone::Transform(vec3 rotate, float scale) 
{
	animation = mat4(1.0f);
	animation = glm::translate(animation, -initialPosition);
	animation *= glm::toMat4(glm::quat(rotate));
	animation *= glm::toMat4(quaternion);
	animation = glm::scale(animation, vec3(1.0f / (scale * initialScale)));
	if (parent != nullptr) 
	{
		animation *= parent->animation;
	}

	convertMat = glm::inverse(animation) * getInitial();
}

mat4 Bone::getInitial() 
{
	mat4 initial = mat4(1.0f);
	initial = glm::translate(initial, -initialPosition);
	initial *= glm::toMat4(quaternion);
	initial = glm::scale(initial, vec3(1.0f / initialScale));
	if (parent != nullptr)
	{
		initial *= parent->getInitial();
	}

	return initial;
}