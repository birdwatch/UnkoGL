#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

class Bone
{
public:
	// Parent Bone
	// position local���W�ɂ�����bottom�̍��W
	// rotate tip�̌���
	// length joint���W�n��bone���W�n�ɂ�����P�ʕϊ�
	Bone(vec3 position, vec3 rotation, float length);

	// Child Bone
	// rotate tip�̌���
	// length joint���W�n��bone���W�n�ɂ�����P�ʕϊ�
	Bone(Bone *bone, vec3 rotation, float length);

	// animation�s��̐���
	void Transform(vec3 rotate, float scale);

	// �ϊ��s��
	mat4 convertMat;

	~Bone();

private:
	// initial�s�� �����ʒu�ɂ�����bone���W�n��joint���W�n�̐�ΓI�ȕϊ�
	mat4 getInitial();
	// animation�s�� ����t�ɂ�����bone���W�n��joint���W�n�̐�ΓI�ȕϊ�
	mat4 animation;

	// ����Bone�N���X�̐e
	Bone *parent;

	// ������Ԃł�bone���W�n��joint���W�n�̒P�ʕϊ��Ajoint���W�n�ɂ�������W�A��]
	float initialScale;
	vec3 initialPosition;
	glm::quat quaternion;
};