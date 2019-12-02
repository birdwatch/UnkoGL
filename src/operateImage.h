#pragma once
#include "pch.h"
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>

GLuint readImage(std::string filename);

void saveImage(const unsigned int imageWidth, const unsigned int imageHeight);