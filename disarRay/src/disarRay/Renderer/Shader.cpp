#include "drpch.h"
#include "Shader.h"

#include "glad/glad.h"

namespace Dray
{
	// Code taken from khronos.org/opengl/wiki/Shader_Compilation
	Shader::Shader(str8 vertexSrc, str8 pixelSrc)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			DRAY_ENGINE_ERROR("Vertex shader compilation failed: \n{2}", &infoLog[0]);
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)pixelSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			DRAY_ENGINE_ERROR("Pixel shader compilation failed: \n{2}", &infoLog[0]);
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RenderID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RenderID, vertexShader);
		glAttachShader(m_RenderID, fragmentShader);

		// Link our program
		glLinkProgram(m_RenderID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RenderID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RenderID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RenderID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RenderID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			DRAY_ENGINE_ERROR("Shader linking failed: \n{2}", &infoLog[0]);
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RenderID, vertexShader);
		glDetachShader(m_RenderID, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RenderID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RenderID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}
}
