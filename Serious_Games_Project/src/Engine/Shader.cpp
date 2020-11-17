#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION // for stb_image uses (load different kind of files for texture)
#include "stb_image.h"

namespace Engine {
	Shader::Shader(const char* vertSrcFile, const char* fragSrcFile) {
		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		GLint vlen;
		GLint flen;
		char* source = loadFile(vertSrcFile, vlen);
		char* fragment = loadFile(fragSrcFile, flen);

		glShaderSource(vertShader, 1, &source, &vlen);
		glShaderSource(fragShader, 1, &fragment, &flen);

		GLint compiled = 0;
		glCompileShader(vertShader);
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLint maxLength = 0;
			glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertShader);

			Logger::GetSystemLogger()->error("Vertex shader compilation error");
			Logger::GetSystemLogger()->error("{}", infoLog.data());

			return;
		}

		glCompileShader(fragShader);
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLint maxLength = 0;
			glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragShader);

			Logger::GetSystemLogger()->error("Fragment shader compilation error");
			Logger::GetSystemLogger()->error("{}", infoLog.data());

			return;
		}

		m_Prog = glCreateProgram();

		glAttachShader(m_Prog, vertShader);
		glAttachShader(m_Prog, fragShader);

		glLinkProgram(m_Prog);
		GLint isLinked = 0;
		glGetProgramiv(m_Prog, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_Prog, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_Prog, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_Prog);
			// Don't leak shaders either.
			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			Logger::GetSystemLogger()->error("Program link error");
			Logger::GetSystemLogger()->error("{}", infoLog.data());
			return;
		}

		glDetachShader(m_Prog, vertShader);
		glDetachShader(m_Prog, fragShader);
	}

	Shader::Shader(const char* vertSrcFile, const char* fragSrcFile, const char* texSrcFile) {
		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		GLint vlen;
		GLint flen;
		char* source = loadFile(vertSrcFile, vlen);
		char* fragment = loadFile(fragSrcFile, flen);

		glShaderSource(vertShader, 1, &source, &vlen);
		glShaderSource(fragShader, 1, &fragment, &flen);

		GLint compiled = 0;
		glCompileShader(vertShader);
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLint maxLength = 0;
			glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertShader);

			Logger::GetSystemLogger()->error("Vertex shader compilation error");
			Logger::GetSystemLogger()->error("{}", infoLog.data());

			return;
		}

		glCompileShader(fragShader);
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLint maxLength = 0;
			glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragShader);

			Logger::GetSystemLogger()->error("Fragment shader compilation error");
			Logger::GetSystemLogger()->error("{}", infoLog.data());

			return;
		}

		m_Prog = glCreateProgram();

		glAttachShader(m_Prog, vertShader);
		glAttachShader(m_Prog, fragShader);

		glLinkProgram(m_Prog);
		GLint isLinked = 0;
		glGetProgramiv(m_Prog, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_Prog, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_Prog, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_Prog);
			// Don't leak shaders either.
			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			Logger::GetSystemLogger()->error("Program link error");
			Logger::GetSystemLogger()->error("{}", infoLog.data());
			return;
		}

		glDetachShader(m_Prog, vertShader);
		glDetachShader(m_Prog, fragShader);

		glGenTextures(1, &m_TexID); // generate texture ID

		glBindTexture(GL_TEXTURE_2D, m_TexID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		LoadTexture(texSrcFile);
	}

	Shader::~Shader(){
		glDeleteProgram(m_Prog);
	}

	void Shader::Bind() const{
		glUseProgram(m_Prog);
		glBindTexture(GL_TEXTURE_2D, m_TexID);
	}

	void Shader::Unbind() const{
		glUseProgram(0);
	}

	void Shader::LoadTexture(const char* texSrcFile) const {
		int width, height, nrChannels;
		unsigned char* data = stbi_load(texSrcFile, &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			Logger::GetSystemLogger()->error("Failed to load textures");
		}
		stbi_image_free(data);
	}

	// function to load shaders files. Comes from Advanced Graphics Programming module of last year
	char* Shader::loadFile(const char* fname, GLint& fSize) {
		int size;
		char* memblock;

		// file read based on example in cplusplus.com tutorial
		// ios::ate opens file at the end
		std::ifstream file(fname, std::ios::in | std::ios::binary | std::ios::ate);
		if (file.is_open()) {
			size = (int)file.tellg(); // get location of file pointer i.e. file size
			fSize = (GLint)size;
			memblock = new char[size];
			file.seekg(0, std::ios::beg);
			file.read(memblock, size);
			file.close();
			Logger::GetSystemLogger()->info("File {} has been loaded", fname);
		}
		else {
			Logger::GetSystemLogger()->error("Unable to open file {}", fname);
			fSize = 0;
			// should ideally set a flag or use exception handling
			// so that calling function can decide what to do now
			return nullptr;
		}
		return memblock;
	}
}
