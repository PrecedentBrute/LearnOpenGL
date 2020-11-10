#pragma once
#include<glad/glad.h>
#include<string>
#include<sstream>
#include<fstream>

class Shader              //compare with the official one
{

private:
	
	unsigned int program_id;
	char info_log[512] = { 0 };
	
public:
	Shader(std::string vShaderPath, std::string fShaderPath)
	{
		std::ifstream vShaderFile(vShaderPath);
		std::ifstream fShaderFile(fShaderPath);
		std::string vCode;
		std::string fCode;
		
		if ((vShaderFile && fShaderFile))   // checks if the files have opened successfully.
		{
			std::stringstream vShaderStream, fShaderStream;
			std::string line;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vCode = vShaderStream.str();
			fCode = fShaderStream.str();
		}
		else
		{
			std::cout << "Could not open file!" << std::endl;
		}
		
		const char* vShaderSource = vCode.c_str();      
		const char* fShaderSource = fCode.c_str();      // stream.str().c_str() won't work as it won't be properly null terminated.
		
		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vertexShader, 1, &vShaderSource, NULL);
		glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
		glCompileShader(vertexShader);
		glCompileShader(fragmentShader);

		int compile_status;
		
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compile_status);
		if (compile_status == GL_FALSE)
			std::cout << "Vertex shader compilation failed." << std::endl;  //Take proper logs

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compile_status);
		if (compile_status == GL_FALSE)
			std::cout << "Fragment shader compilation failed." << std::endl;

		program_id = glCreateProgram();
		glAttachShader(program_id, vertexShader);
		glAttachShader(program_id, fragmentShader);
		glLinkProgram(program_id);

		glGetProgramiv(program_id, GL_LINK_STATUS, &compile_status);
		if (compile_status == GL_FALSE)
		{
			std::cout << "Program linking failed." << std::endl;
			glGetProgramInfoLog(program_id, 512, NULL, info_log);
			std::cout << info_log << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void use()
	{
		glUseProgram(program_id);
	}

	void setFloat(std::string uniform_name, float f)
	{
		int uniform_location =  glGetUniformLocation(program_id, uniform_name.c_str());
		glUniform1f(uniform_location, f);
	}


	void setInt(std::string uniform_name, int i)
	{
		int uniform_location = glGetUniformLocation(program_id, uniform_name.c_str());
		glUniform1i(uniform_location, i);
	}

	~Shader()
	{
		glDeleteProgram(program_id);
	}

			// Add functions to set uniforms
};



