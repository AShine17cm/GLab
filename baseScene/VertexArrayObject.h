#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VertexBufferObject.h"

class VertexArrayObject
{
public:
	GLuint ID;
	VertexArrayObject();

	//顶点的属性布局 pos+normal+color ...
	void LinkAttrib(VertexBufferObject& bufferObject,GLuint layout,GLuint numComponents,GLenum type,GLsizeiptr stride,void* offset);
	
	//void LinkVertexBufferObject(VertexBufferObject& bufferObject, GLuint layout);

	void Bind();
	void Unbind();
	void Delete();

};

#endif // !VAO_CLASS_H

