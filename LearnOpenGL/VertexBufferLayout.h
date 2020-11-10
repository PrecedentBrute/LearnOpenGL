#pragma once

#include<vector>
#include<glad/glad.h>
#include<renderer.h>

struct VertexBufferElement
{
    int count;
	bool normalized;
	GLenum type;

    size_t getSizeOfType() const
	{
		switch (type)
		{
			case GL_FLOAT :           return 4;
			case GL_INT :             return 4;
			case GL_UNSIGNED_BYTE :   return 1;
			default : ASSERT(false);
		}
	}
};

class VertexBufferLayout
{
	std::vector<VertexBufferElement> m_Layout_elements;
	GLsizei m_stride;
public:
	VertexBufferLayout()
		:m_stride(0)
	{}

	template<typename t>
	void Push(int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(int count)
	{
		m_Layout_elements.push_back({ count, GL_FALSE, GL_FLOAT });
		m_stride += 4 * count;
	}

	template<>
	void Push<int>(int count)
	{
		m_Layout_elements.push_back({ count, GL_FALSE, GL_INT });
		m_stride += 4 * count;
	}

	template<>
	void Push<char>(int count)
	{
		m_Layout_elements.push_back({ count, GL_TRUE, GL_UNSIGNED_BYTE });
		m_stride += 1 * count;
	}

	inline const std::vector<VertexBufferElement>& getElements() const { return m_Layout_elements; }
	inline GLsizei getStride() const { return m_stride; }
};
