#pragma once

#include"renderer.h"
#include<string>
#include<stb_image.h>

class Texture {
private:
	unsigned int m_texture_id;
	std::string file_path;
	unsigned char* local_buffer;
	int t_width, t_height, t_nrchannels; //this is bytes per pixel, 4 here in RGBA8

public:
	Texture(const std::string& path, unsigned int flip_flag = 1, GLenum param = GL_REPEAT);
	~Texture();
	
	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	void setParam(GLenum param, GLenum value);

	inline int GetWidth() const { return t_width; }
	inline int GetHeight() const { return t_height; }
};
