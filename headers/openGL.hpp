#ifndef OPENGL_HPP
# define OPENGL_HPP

# include "color.hpp"
# include "types.hpp"
# include <iostream>
# include <GLFW/glfw3.h>

class openGL {

	private:
		u32 _width;
		u32 _height;

		GLFWwindow* _window;

	public:
		openGL(void);
		~openGL(void);

		u32		getWidth(void);
		u32		getHeight(void);
		void	setWidth(u32 width);
		void	setHeight(u32 height);
		GLFWwindow*	getWindow(void);

		bool	init(std::string_view windowName = "GLFW", u32 width = 1920, u32 height = 1080);
		void	loop(void);

};

#endif
