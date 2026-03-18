#include "openGL.hpp"

//constructors/destructors---------------------------------

openGL::openGL(void) {}

openGL::~openGL(void) {}

//Member functions-----------------------------------------

u32	openGL::getWidth(void)
{
	return _width;
}

u32	openGL::getHeight(void)
{
	return _height;
}

void	openGL::setWidth(u32 width) {
	this->_width = width;
}

void	openGL::setHeight(u32 height) {
	this->_height = height;
}

GLFWwindow*	openGL::getWindow(void)
{
	return _window;
}

bool	openGL::init(std::string_view windowName, u32 width, u32 height) {

	if (!glfwInit()) {
		std::cerr << COLOR_LIGHT_RED << "Error : could not initialize GLFW" << COLOR_NC << std::endl;
		return false;
	}
	std::cout << "✓ GLFW initialized (version " << glfwGetVersionString() << ")" << std::endl;

	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Core profile (remove deprecated functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window size
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	// Antialiasing (MSAA)
	// glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(width, height, windowName.data(), NULL, NULL);
	if (!window) {
		std::cerr << COLOR_LIGHT_RED << "Error : could not create window" << COLOR_NC << std::endl;
		glfwTerminate();
		return false;
	}
	this->_window = window;

	glfwSetWindowUserPointer(window, this);

	int winWidth, winHeight;
	glfwGetFramebufferSize(window, &winWidth, &winHeight);
	glViewport(0, 0, winWidth, winHeight);
	this->_width = winWidth;
	this->_height = winHeight;

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int w, int h) {
		auto app = static_cast<openGL*>(glfwGetWindowUserPointer(win));
		app->_width = w;
		app->_height = h;
		// std::cout << app->_width << "x" << app->_height << std::endl;
		glViewport(0, 0, w, h);
	});

	std::cout << "✓ Window created successfully\n" << std::endl;

	glfwMakeContextCurrent(window);;

	return true;
}

void openGL::loop(void) {
	while (!glfwWindowShouldClose(this->_window)) {
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(this->_window);
		glfwPollEvents();

		if (glfwGetKey(this->_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(this->_window, 1);
	}

	glfwDestroyWindow(this->_window);
	glfwTerminate();
	printf("✓ Cleaning OK, program stopping\n");
}