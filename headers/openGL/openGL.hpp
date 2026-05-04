#ifndef OPENGL_HPP
# define OPENGL_HPP

# include "color.hpp"
# include "types.hpp"
# include "vec3.hpp"
# include "Camera.hpp"
# include <iostream>
# include <fstream>
# include <vector>
# include <filesystem>
# include <cmath>
# include <cstddef>
# include "glad/glad.h"
# include <GLFW/glfw3.h>

struct VertexAttribDesc {
	u32			index;
	GLint		size;
	GLenum		type;
	bool		normalized;
	GLsizei		stride;
	std::size_t	offset;
};

template <typename VertexType>
inline VertexAttribDesc	makeAttrib(u32 index, GLint size, GLenum type, std::size_t offset, bool normalized = false) {
	return VertexAttribDesc{
		index,
		size,
		type,
		normalized,
		static_cast<GLsizei>(sizeof(VertexType)),
		offset
	};
}

class openGL {

	private:
		u32	_width;
		u32	_height;

		GLFWwindow*	_window;
		u32			_shaderProgram;
		u32			_VAO;
		u32			_texture;
		u32			_indexCount;

		static u32			CompileShader(std::string_view path, int shaderType, std::string_view shaderName);
		static std::string	OpenShader(std::string_view fileName);
		void				CreateShaders(void);

	public:
		openGL(void);
		~openGL(void);

		Camera	cam;

		void		setWidth(u32 width);
		void		setHeight(u32 height);
		u32			getWidth(void);
		u32			getHeight(void);
		GLFWwindow*	getWindow(void);
		u32			getShaderProgram(void);
		u32			getVAO(void);
		u32			getTexture(void);
		u32			getIndexCount(void);

		bool	Init(std::string_view windowName = "GLFW", u32 width = 1920, u32 height = 1080);
		void	LoadScene(
			const void* vertexData,
			std::size_t vertexBufferSize,
			const void* indexData,
			std::size_t indexBufferSize,
			const std::vector<VertexAttribDesc>& attributes,
			GLenum usage = GL_STATIC_DRAW
		);
		void	LoadImage(std::string imagePath);
		void	Loop(void (*loop)(openGL&));

};

#endif
