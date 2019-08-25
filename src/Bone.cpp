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

	initMat = mat4(1.0f);
	initMat = glm::translate(initMat, -initialPosition);
	initMat *= glm::toMat4(quaternion);
	initMat = glm::scale(initMat, vec3(1.0f / initialScale));
	if (parent != nullptr)
	{
		initMat *= parent->initMat;
	}
}

Bone::Bone(Bone *bone, vec3 rotation, float length)
{
	parent = bone;
	initialScale = length;
	quaternion = glm::quat(rotation);
	initialPosition = vec3(0.0f, 0.0f, 1.0f);

	initMat = mat4(1.0f);
	initMat = glm::translate(initMat, -initialPosition);
	initMat *= glm::toMat4(quaternion);
	initMat = glm::scale(initMat, vec3(1.0f / initialScale));
	if (parent != nullptr)
	{
		initMat *= parent->initMat;
	}
}

Bone::~Bone()
{
}

void Bone::Transform(vec3 rotate) 
{
	animeMat = mat4(1.0f);
	animeMat = glm::translate(animeMat, -initialPosition);
	animeMat *= glm::toMat4(glm::quat(rotate));
	animeMat *= glm::toMat4(quaternion);
	animeMat = glm::scale(animeMat, vec3(1.0f / initialScale));
	if (parent != nullptr) 
	{
		animeMat *= parent->animeMat;
	}

	convertMat = glm::inverse(animeMat) * initMat;
}