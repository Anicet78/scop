#ifndef OPENGL_HPP
# define OPENGL_HPP

# include "color.hpp"
# include "types.hpp"
# include "vec3.hpp"
# include <iostream>
# include <fstream>
# include <vector>
# include <filesystem>
# include <glad/glad.h>
# include <GLFW/glfw3.h>

class openGL {

	private:
		u32 _width;
		u32 _height;

		GLFWwindow* _window;
		u32			_shaderProgram;
		u32			_VAO;

		static u32			CompileShader(std::string_view path, int shaderType, std::string_view shaderName);
		static std::string	OpenShader(std::string_view fileName);
		void				CreateShaders(void);

	public:
		openGL(void);
		~openGL(void);

		u32			getWidth(void);
		u32			getHeight(void);
		void		setWidth(u32 width);
		void		setHeight(u32 height);
		GLFWwindow*	getWindow(void);

		bool	Init(std::string_view windowName = "GLFW", u32 width = 1920, u32 height = 1080);
		void	LoadScene(std::vector<vec3>& vertices, std::vector<u32>& indices);
		void	Loop(void);

};

#endif
