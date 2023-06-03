#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
class ElementBufferObject
{
public:
	GLuint ID;
	//构造并初始化 三角面
	ElementBufferObject(GLuint* indices,GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif
