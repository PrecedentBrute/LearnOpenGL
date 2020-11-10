#pragma once
#include<glad/glad.h>

#define ASSERT(x) if(!(x)) __debugbreak();

#define GLCall(x) GLclearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLclearError();

bool GLLogCall(const char* function, const char* file, int line);

void GLerrorDescription(GLenum error);

static const unsigned int SCR_WIDTH = 800;
static const unsigned int SCR_HEIGHT = 600;

