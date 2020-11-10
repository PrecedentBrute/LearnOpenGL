#include<IndexBuffer.h>
#include<renderer.h>

indexBuffer::indexBuffer(const void* data, unsigned int count)
	:i_count(count)
{
	glGenBuffers(1, &iBuffer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer_id);
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

indexBuffer::~indexBuffer()
{
	glDeleteBuffers(1, &iBuffer_id);
}

void indexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer_id);
}

void indexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

inline int indexBuffer::getCount() const { return i_count; }
