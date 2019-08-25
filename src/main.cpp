#include "pch.h"
#include "Bone.h"
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>
#include <glm/glm.hpp>

using namespace std;
using glm::vec3;
using glm::vec4;
using glm::mat4;

static const float pi = 3.141592653589793f;

const int g_width = 640;
const int g_height = 480;

int readShaderSource(GLuint shaderObj, string fileName);

GLuint crateShader();

int main()
{
	if (!glfwInit()) {
		cout << "Can't initilize GLFW" << endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(g_width, g_height, "UnkoGL", NULL, NULL);

	if (!window)
	{
		cout << "Can't create GLFW window." << endl;
		
		glfwTerminate();
		return -1;
	}

	// モニタとの同期
	glfwMakeContextCurrent(window);
	glewInit();

	glfwSwapInterval(1);

	GLuint programId = crateShader();

	Bone a = Bone(vec3(0.0f, 0.0f, 1.0f), vec3(), 1.0f);
	Bone b = Bone(&a, vec3(0.0f), 1.0f);
	Bone c = Bone(&b, vec3(0.0f), 1.0f);
	Bone d = Bone(&c, vec3(0.0f), 1.0f);

	mat4 modelMat, viewMat, projectionMat, mvpMat;

	// View Matrix
	viewMat = glm::lookAt(
		vec3(5.0, 6.0, 0.0), // ワールド空間でのカメラの座標
		vec3(-1.0, 0.0, 1.0), // 見ている位置の座標
		vec3(0.0, 0.0, 1.0)  // 上方向を示す。(0,1.0,0)に設定するとy軸が上になります
	);

	// Projection Matrix
	projectionMat = glm::perspective(
		glm::radians(45.0f), // ズームの度合い(通常90～30)
		4.0f / 3.0f,		// アスペクト比
		0.1f,		// 近くのクリッピング平面
		100.0f		// 遠くのクリッピング平面
	);

	// Model Matrix
	modelMat = mat4(1.0f);

	mvpMat = projectionMat * viewMat * modelMat;

	// 座標
	float points[] =
	{
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,

		0.5f, 0.5f, 1.0f,
		0.5f, -0.5f, 1.0f,
		-0.5f, -0.5f, 1.0f,
		-0.5f, 0.5f, 1.0f,

		0.5f, 0.5f, 2.0f,
		0.5f, -0.5f, 2.0f,
		-0.5f, -0.5f, 2.0f,
		-0.5f, 0.5f, 2.0f,

		0.5f, 0.5f, 3.0f,
		0.5f, -0.5f, 3.0f,
		-0.5f, -0.5f, 3.0f,
		-0.5f, 0.5f, 3.0f,

		0.5f, 0.5f, 4.0f,
		0.5f, -0.5f, 4.0f,
		-0.5f, -0.5f, 4.0f,
		- 0.5f, 0.5f, 4.0f
	};

	// 各頂点の色
	float colors[] =
	{
		1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};

	// boneから影響を受ける割合
	float ratios[]
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f,

		0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 0.0f,

		0.0f, 0.5f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.5f, 0.0f,

		0.0f, 0.0f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.5f, 0.5f,

		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	//頂点番号
	GLuint index[] =
	{
	0,1,2,3,

	1,5,6,2,
	4,0,3,7,
	4,5,1,0,
	3,2,6,7,

	5,9,10,6,
	8,4,7,11,
	8,9,5,4,
	7,6,10,11,

	9,13,14,10,
	12,8,11,15,
	12,13,9,8,
	11,10,14,15,

	13,17,18,14,
	16,12,15,19,
	16,17,13,12,
	15,14,18,19,

	16,17,18,19

	}; 

	/* VBO(Vertex Buffer Object)の生成
	    実際に情報を格納するGPU側のbuffer */
	GLuint vbo[4];
	glGenBuffers(4, vbo);

	/* bufferをbind
	有効化した変数に、頂点属性番号、頂点情報の要素数、データ型などを渡す */
	// 頂点をbufferに転送
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	// 色をbufferに転送
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	// 割合をbufferに転送
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ratios), ratios, GL_STATIC_DRAW);

	glBindBuffer(GL_DYNAMIC_COPY, vbo[3]);

	// IBO(Index Buffer Object)の生成
	GLuint ibo;
	glGenBuffers(1, &ibo);

	// indexをbufferに転送
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	// unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* VAO(Vertex Array Object)の生成
	   VAOでVBOをまとめる　
	   glVertexAttribPointerの設定を保存 */
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	/* attributeを有効にする
	(= bindしたbufferのindexを有効化) */
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	// unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// unbind vao
	glBindVertexArray(0);

	int t = 0;

	// ゲームループ
	while (!glfwWindowShouldClose(window)) {

		// 画面の初期化
		glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearDepth(1.0);
		glEnable(GL_DEPTH_TEST);

		a.Transform(vec3(0.000002f*t, 0.0003f*t, 0.00004f*t));
		b.Transform(vec3(0.0001f*t, 0.001f*t, 0.0003f*t));
		c.Transform(vec3(0.00008f*t, 0.0001f*t, 0.0005f*t));
		d.Transform(vec3(0.0004f*t, 0.0006f*t, 0.0006f*t));

		// uniform 変数 projectionMatrix に行列を設定する 
		glUniformMatrix4fv(glGetUniformLocation(programId, "projectionMatrix"), 1, GL_FALSE, &mvpMat[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(programId, "aMat"), 1, GL_FALSE, &a.convertMat[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(programId, "bMat"), 1, GL_FALSE, &b.convertMat[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(programId, "cMat"), 1, GL_FALSE, &c.convertMat[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(programId, "dMat"), 1, GL_FALSE, &d.convertMat[0][0]);

		glBindVertexArray(vao);

		// モデルの描画
		glDrawElements(GL_QUADS, 72, GL_UNSIGNED_INT, 0);

		// swap buffer
		glfwSwapBuffers(window);

		glBindVertexArray(0);

		t++;

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

int readShaderSource(GLuint shaderObj, string fileName)
{
	//ファイルの読み込み
	ifstream ifs(fileName);
	if (!ifs)
	{
		cout << fileName + "is not found." << endl;
		return -1;
	}

	string source;
	string line;
	while (getline(ifs, line))
	{
		source += line + "\n";
	}

	// シェーダのソースプログラムをシェーダオブジェクトへ読み込む
	const GLchar *sourcePtr = (const GLchar *)source.c_str();
	GLint length = source.length();
	glShaderSource(shaderObj, 1, &sourcePtr, &length);

	return 0;
}

GLuint crateShader()
{
	GLint compileId, linked;

	//バーテックスシェーダとフラグメントシェーダのシェーダオブジェクトを作成
	//作成したそれぞれのシェーダオブジェクトに対してソースプログラムを読み込み
	//読み込んだソースプログラムをコンパイル
	//vertex shaderのコンパイル
	GLuint vShaderId = glCreateShader(GL_VERTEX_SHADER);

	if (readShaderSource(vShaderId, "shaders/vertex_shader.glsl")) return -1;

	cout << "Now conpiling vertex shader." << endl;

	glCompileShader(vShaderId);
	glGetShaderiv(vShaderId, GL_COMPILE_STATUS, &compileId);

	//check for errors
	if (!compileId)
	{
		// ログを取得
		if (compileId == GL_FALSE) {
			printf("Compile error in vertex shader.\n");
			exit(1);
			abort();
		}

		glDeleteShader(vShaderId);
		return false;
	}

	cout << "OK" << endl;

	//fragment shaderのコンパイル
	GLuint fShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	if (readShaderSource(fShaderId, "shaders/fragment_shader.glsl")) return -1;

	cout << "Now conpiling fragment shader." << endl;

	glCompileShader(fShaderId);
	glGetShaderiv(fShaderId, GL_COMPILE_STATUS, &compileId);

	//check for errors
	if (!compileId)
	{
		// ログを取得
		if (compileId == GL_FALSE) {
			printf("Compile error in vertex shader.\n");
			exit(1);
			abort();
		}

		glDeleteShader(fShaderId);
		return false;
	}

	cout << "OK" << endl;

	//プログラムオブジェクトの作成
	GLuint programId = glCreateProgram();
	//プログラムオブジェクトに対してシェーダオブジェクトを登録
	glAttachShader(programId, vShaderId);
	glAttachShader(programId, fShaderId);

	// リンク
	// シェーダプログラムをリンク
	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE)
	{
		int info_log_length = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &info_log_length);
		glDeleteProgram(programId);
		return 0;
	}

	// シェーダプログラムを適用
	glUseProgram(programId);

	return programId;
}