#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &ID);
}
//void VertexArrayObject::LinkVertexBufferObject(VertexBufferObject& bufferObject, GLuint layout)
//{
//	bufferObject.Bind();
//	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//	glEnableVertexAttribArray(layout);
//	bufferObject.Unbind();
//}

void VertexArrayObject::LinkAttrib(VertexBufferObject& bufferObject, GLuint layout,GLuint numComponents,GLenum type,GLsizeiptr stride,void* offset)
{
	bufferObject.Bind();
	glVertexAttribPointer(layout, numComponents, type,GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	bufferObject.Unbind();
}
void VertexArrayObject::Bind()
{
	glBindVertexArray(ID);
}
void VertexArrayObject::Unbind()
{
	glBindVertexArray(0);
}

void VertexArrayObject::Delete()
{
	glDeleteVertexArrays(1, &ID);
}