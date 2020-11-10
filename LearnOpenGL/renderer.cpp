#include<renderer.h>
#include<iostream>

void GLclearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)     
{
    bool flag = true;
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL error] : " << std::hex << "0x" << error << std::dec << "\nFunction : " << function << "\nFile : " << file << "\nLine : " << line << std::endl;
        GLerrorDescription(error);
        flag = false;
    }
    return flag;
}

void GLerrorDescription(GLenum error)
{
    std::cout << "Description : ";
    switch (error)
    {
    case GL_INVALID_ENUM :
        std::cout << "Given when an enumeration parameter is not a legal enumeration for that function. This is given only for local problems; if the spec allows the enumeration in certain circumstances, where other parameters or state dictate those circumstances, then GL_INVALID_OPERATION is the result instead." << std::endl;
        break;
    case GL_INVALID_VALUE : 
        std::cout << "Given when a value parameter is not a legal value for that function.This is only given for local problems; if the spec allows the value in certain circumstances, where other parameters or state dictate those circumstances, then GL_INVALID_OPERATION is the result instead." << std::endl;
        break;
    case GL_INVALID_OPERATION :
        std::cout << "Given when the set of state for a command is not legal for the parameters given to that command. It is also given for commands where combinations of parameters define what the legal parameters are." << std::endl;
        break;
    case GL_STACK_OVERFLOW :
        std::cout << "Given when a stack pushing operation cannot be done because it would overflow the limit of that stack's size." << std::endl;
        break;
    case GL_STACK_UNDERFLOW : 
        std::cout << "Given when a stack popping operation cannot be done because the stack is already at its lowest point." << std::endl;
        break;
    case GL_OUT_OF_MEMORY :
        std::cout << "Given when performing an operation that can allocate memory, and the memory cannot be allocated.The results of OpenGL functions that return this error are undefined; it is allowable for partial execution of an operation to happen in this circumstance." << std::endl;
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION :
        std::cout << "Given when doing anything that would attempt to read from or write/render to a framebuffer that is not complete." << std::endl;
        break;
    default :
        std::cout << "Unknown error. Search for the code." << std::endl;
    }
}