#include "operateImage.h"

GLuint readImage(std::string filename)
{
	// �e�N�X�`��ID�̐���
	GLuint texID;
	glGenTextures(1, &texID);

	cv::Mat image = cv::imread(filename);
	if (image.empty()) {
		std::cout << "image empty" << std::endl;
	}
	else {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, image.cols, image.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data);

		// �e�N�X�`���̐ݒ�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	// �e�N�X�`���̃A���o�C���h
	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

void saveImage(const unsigned int imageWidth, const unsigned int imageHeight)
{
	const unsigned int channelNum = 3; // RGB�Ȃ�3, RGBA�Ȃ�4
	void* dataBuffer = NULL;
	dataBuffer = (GLubyte*)malloc(imageWidth * imageHeight * channelNum);

	// �ǂݎ��OpneGL�̃o�b�t�@���w�� GL_FRONT:�t�����g�o�b�t�@�@GL_BACK:�o�b�N�o�b�t�@
	glReadBuffer(GL_BACK);

	// OpenGL�ŉ�ʂɕ`�悳��Ă�����e���o�b�t�@�Ɋi�[
	glReadPixels(
		0,                 //�ǂݎ��̈�̍�������x���W
		0,                 //�ǂݎ��̈�̍�������y���W //0 or getCurrentWidth() - 1
		imageWidth,             //�ǂݎ��̈�̕�
		imageHeight,            //�ǂݎ��̈�̍���
		GL_BGR, //it means GL_BGR,           //�擾�������F���̌`��
		GL_UNSIGNED_BYTE,  //�ǂݎ�����f�[�^��ۑ�����z��̌^
		dataBuffer      //�r�b�g�}�b�v�̃s�N�Z���f�[�^�i���ۂɂ̓o�C�g�z��j�ւ̃|�C���^
	);

	GLubyte* p = static_cast<GLubyte*>(dataBuffer);
	std::string fname = "outputImage.jpg";
	cv::Mat outImage = cv::Mat(cv::Size(imageWidth, imageHeight), CV_8UC3, p);
	cv::flip(outImage, outImage, 0);
	cv::imwrite(fname.c_str(), outImage);
}