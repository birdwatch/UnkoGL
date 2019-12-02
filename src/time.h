#pragma once
#include "pch.h"
#include <iostream>
#include <time.h>

struct Time
{
	static unsigned frameCount; //!< フレーム数
	static float time;       //!< ゲーム開始時からの経過時間（秒）
	static float deltaTime;  //!< 直前のフレームからの経過時間（秒）
	static float fps;        //!< FPS

	static void Start();
	static void Update();
};