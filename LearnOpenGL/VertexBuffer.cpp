#include<VertexBuffer.h>
#include<renderer.h>

vertexBuffer::vertexBuffer(const void* data, int size)
{
	glGenBuffers(1, &vBuffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer_id);
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

vertexBuffer::~vertexBuffer()
{
	glDeleteBuffers(1, &vBuffer_id);
}

void vertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer_id);
}

void vertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
