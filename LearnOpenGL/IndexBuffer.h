#pragma once

class indexBuffer
{
	unsigned int iBuffer_id;
	int i_count;

public:

	indexBuffer(const void* data, unsigned int count);
	~indexBuffer();
	void Bind() const;
	void UnBind() const;
	int getCount() const;
};

