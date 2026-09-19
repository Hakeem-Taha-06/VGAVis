#pragma once
#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class Shader {
public:
	Shader(const char* vsrc, const char* fsrc) {
		unsigned int vshader, fshader;
		_createShader(&vshader, vsrc, GL_VERTEX_SHADER);
		_createShader(&fshader, fsrc, GL_FRAGMENT_SHADER);

		m_ID = glCreateProgram();

		glAttachShader(m_ID, vshader);
		glAttachShader(m_ID, fshader);
		glLinkProgram(m_ID);

		int linkStatus;
		glGetProgramiv(m_ID, GL_COMPILE_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE) {
			char infoLog[512];
			glGetProgramInfoLog(m_ID, 512, nullptr, infoLog);
			std::cout << "shader program linking error: " << infoLog << std::endl;
		}

		std::cout << "Shader Created Succesfully" << '\n';

		glDeleteShader(vshader);
		glDeleteShader(fshader);
	};

	~Shader() {
		glDeleteProgram(m_ID);
	}

	void use() {
		glUseProgram(m_ID);
	}

private:

	void _createShader(unsigned int* shader, const char* src, GLenum type) {
		*shader = glCreateShader(type);
		glShaderSource(*shader, 1, &src, nullptr);

		glCompileShader(*shader);

		int compileStatus;
		glGetShaderiv(*shader, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus == GL_FALSE) {
			char infoLog[512];
			glGetShaderInfoLog(*shader, 512, nullptr, infoLog);
			std::cout << "shader compilation error: " << infoLog << std::endl;
		}
	}

	std::string _readFileContents(const char* path) {
		std::ifstream file;
		std::stringstream contents;

		file.exceptions(std::fstream::badbit);
		try {
			file.open(path);
			if (!file.is_open()) {
				std::cerr << "Error opening file: " << path << std::endl;
				exit(EXIT_FAILURE);
			}
			contents << file.rdbuf();
			file.close();
		}
		catch (std::exception e) {
			std::cerr << "error loading file: (" << e.what() << ")" << std::endl;
			exit(EXIT_FAILURE);
		}
		return contents.str();
	}

	unsigned int m_ID;
};