#pragma once

class vertexBuffer
{
	unsigned int vBuffer_id;

public:
	
	vertexBuffer(const void* data, int size);
	~vertexBuffer();
	void Bind() const;
	void UnBind() const;
};
