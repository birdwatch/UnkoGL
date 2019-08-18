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
	// position local座標におけるbottomの座標
	// rotate tipの向き
	// length joint座標系とbone座標系における単位変換
	Bone(vec3 position, vec3 rotation, float length);

	// Child Bone
	// rotate tipの向き
	// length joint座標系とbone座標系における単位変換
	Bone(Bone *bone, vec3 rotation, float length);

	// animation行列の生成
	void Transform(vec3 rotate, float scale);

	// 変換行列
	mat4 convertMat;

	~Bone();

private:
	// initial行列 初期位置におけるbone座標系とjoint座標系の絶対的な変換
	mat4 getInitial();
	// animation行列 時刻tにおけるbone座標系とjoint座標系の絶対的な変換
	mat4 animation;

	// このBoneクラスの親
	Bone *parent;

	// 初期状態でのbone座標系とjoint座標系の単位変換、joint座標系における座標、回転
	float initialScale;
	vec3 initialPosition;
	glm::quat quaternion;
};