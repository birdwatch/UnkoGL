#include "operateImage.h"

GLuint readImage(std::string filename)
{
	// テクスチャIDの生成
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

		// テクスチャの設定
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	// テクスチャのアンバインド
	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

void saveImage(const unsigned int imageWidth, const unsigned int imageHeight)
{
	const unsigned int channelNum = 3; // RGBなら3, RGBAなら4
	void* dataBuffer = NULL;
	dataBuffer = (GLubyte*)malloc(imageWidth * imageHeight * channelNum);

	// 読み取るOpneGLのバッファを指定 GL_FRONT:フロントバッファ　GL_BACK:バックバッファ
	glReadBuffer(GL_BACK);

	// OpenGLで画面に描画されている内容をバッファに格納
	glReadPixels(
		0,                 //読み取る領域の左下隅のx座標
		0,                 //読み取る領域の左下隅のy座標 //0 or getCurrentWidth() - 1
		imageWidth,             //読み取る領域の幅
		imageHeight,            //読み取る領域の高さ
		GL_BGR, //it means GL_BGR,           //取得したい色情報の形式
		GL_UNSIGNED_BYTE,  //読み取ったデータを保存する配列の型
		dataBuffer      //ビットマップのピクセルデータ（実際にはバイト配列）へのポインタ
	);

	GLubyte* p = static_cast<GLubyte*>(dataBuffer);
	std::string fname = "outputImage.jpg";
	cv::Mat outImage = cv::Mat(cv::Size(imageWidth, imageHeight), CV_8UC3, p);
	cv::flip(outImage, outImage, 0);
	cv::imwrite(fname.c_str(), outImage);
}