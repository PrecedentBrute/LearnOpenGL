

#pragma once
#include<glad/glad.h>
#include<VertexBufferLayout.h>
#include<VertexBuffer.h>

class VertexArray
{
	unsigned int vArray_id;

public:
	
	VertexArray();
	~VertexArray();
	void Bind() const;
	void UnBind() const;
	void AddBuffer(const vertexBuffer& vb, const  VertexBufferLayout& Layout);
};

