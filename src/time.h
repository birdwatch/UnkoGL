#pragma once
#include "pch.h"
#include <iostream>
#include <time.h>

struct Time
{
	static unsigned frameCount; //!< �t���[����
	static float time;       //!< �Q�[���J�n������̌o�ߎ��ԁi�b�j
	static float deltaTime;  //!< ���O�̃t���[������̌o�ߎ��ԁi�b�j
	static float fps;        //!< FPS

	static void Start();
	static void Update();
};