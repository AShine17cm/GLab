
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "shaderClass.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "ElementBufferObject.h"

const unsigned int width = 800;
const unsigned int height = 800;


GLfloat vertices[] =
{ //pos+color+uv
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	0.5f, 1.0f
};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

int main()
{
	glfwInit();
	//open gl 版本号 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 800, "GL Lab", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "创建 GLFW 窗口失败" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//加载 glad, 配置 Open GL
	gladLoadGL();
	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");

	VertexArrayObject vao1;
	vao1.Bind();

	VertexBufferObject vbo1(vertices, sizeof(vertices));
	ElementBufferObject ebo1(indices, sizeof(indices));
	//vao1.LinkVertexBufferObject(vbo1, 0);
	//顶点布局 坐标+颜色+UV
	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao1.LinkAttrib(vbo1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();
	//获取 shader中一个 uniform 的 ID
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
	std::string texPath = "../Resources/flower.jpg";
	//加载纹理
	Texture flower(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	//绑定到 材质上
	flower.texUnit(shaderProgram, "tex0", 0);

	float rotate = 0.0f;
	double prevTime = glfwGetTime();
	//开启 深度测试
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.1f, 0.13f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		//旋转 模型
		double curTime = glfwGetTime();
		if (curTime - prevTime >= 1 / 60)
		{
			rotate += 0.5f;
			prevTime = curTime;
		}
		glm::mat4 proj = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 model = glm::mat4(1.0f);
		proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 1.0f, 0.0f));

		//目标 shader
		shaderProgram.Activate();
		int projMx = glGetUniformLocation(shaderProgram.ID, "proj");
		int viewMx = glGetUniformLocation(shaderProgram.ID, "view");
		int modelMx = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(projMx, 1, GL_FALSE, glm::value_ptr(proj));
		glUniformMatrix4fv(viewMx, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelMx, 1, GL_FALSE, glm::value_ptr(model));

		glUniform1f(uniID, 0.5f);
		flower.Bind();	//让 GPU 可以使用
		vao1.Bind();	//让 GPU 知道顶点布局

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
	flower.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}