#pragma once

#include <string>
#include <fstream>
#include "GL/glew.h"

#include "Logger.h"

// Shader class create with the help of the kronos wiki on Shader compilation: https://www.khronos.org/opengl/wiki/Shader_Compilation
namespace Engine {
	class Shader
	{
	public:
		Shader(const char* vertSrcFile, const char* fragSrcFile);
		Shader(const char* vertSrcFile, const char* fragSrcFile, const char* texSrcFile);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		GLuint m_Prog;
		GLuint m_TexID;

		void LoadTexture(const char* texSrcFile) const;
		char* loadFile(const char* fname, GLint& fSize);
	};
}

