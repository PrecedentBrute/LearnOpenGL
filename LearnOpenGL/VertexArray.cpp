#include "VertexArray.h"
#include "renderer.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &vArray_id);
	glBindVertexArray(vArray_id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vArray_id);
}

void VertexArray::Bind() const
{
	glBindVertexArray(vArray_id);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const vertexBuffer& vb, const VertexBufferLayout& Layout)
{
	vb.Bind();
	const std::vector<VertexBufferElement>& Elements = Layout.getElements();
	int offset = 0;
	for (unsigned int i = 0; i < Elements.size(); i++)
	{
		const VertexBufferElement& element = Elements[i];
		glVertexAttribPointer(i, element.count, element.type, element.normalized, Layout.getStride(), (const void*)offset);
		glEnableVertexAttribArray(i);
		offset += element.getSizeOfType() * element.count;
	}
}
 