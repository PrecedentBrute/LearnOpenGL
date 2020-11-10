#include "Texture.h"

Texture::Texture(const std::string& path, unsigned int flip_flag, GLenum param)
	: m_texture_id(0), file_path(path), local_buffer(NULL), t_width(0), t_height(0), t_nrchannels(0)
{
	stbi_set_flip_vertically_on_load(flip_flag);
	local_buffer = stbi_load(path.c_str(), &t_width, &t_height, &t_nrchannels, 4);
	
	GLCall(glGenTextures(1, &m_texture_id));
	
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texture_id));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param));


	if (local_buffer)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8/*Internal format, next one is for local_buffer*/, t_width, t_height, 0/*Border is zero*/, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer));
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		ASSERT(false);
	}
	

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (local_buffer) 
		stbi_image_free(local_buffer);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_texture_id));
}

void Texture::setParam(GLenum param, GLenum value)
{
	this->Bind();
	GLCall(glTexParameteri(GL_TEXTURE_2D, param, value));
	this->UnBind();
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texture_id));
}

void Texture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
