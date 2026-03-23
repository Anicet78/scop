#include "openGL.hpp"

//constructors/destructors---------------------------------

openGL::openGL(void) {}

openGL::~openGL(void) {}

//Member functions-----------------------------------------

u32	openGL::getWidth(void) {
	return _width;
}

u32	openGL::getHeight(void) {
	return _height;
}

void	openGL::setWidth(u32 width) {
	this->_width = width;
}

void	openGL::setHeight(u32 height) {
	this->_height = height;
}

GLFWwindow*	openGL::getWindow(void) {
	return _window;
}

bool	openGL::Init(std::string_view windowName, u32 width, u32 height) {

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

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << COLOR_LIGHT_RED << "Error : could not initialize GLAD" << COLOR_NC << std::endl;
		return false;
	}

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

	this->CreateShaders();

	return true;
}

std::string	openGL::OpenShader(const char* fileName) {
	std::ifstream	ifs;

	ifs.open(fileName);
	if (!ifs.is_open() || !ifs.good())
		throw std::runtime_error("Could not open shader file " + std::string(fileName));

	std::string	content;

	content.assign((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	content.append("\0");

	return content;
}

unsigned int	openGL::CompileShader(std::string_view path, int shaderType, std::string_view shaderName) {
	unsigned int shader;
	shader = glCreateShader(shaderType);

	std::string shaderFile = openGL::OpenShader(path.data());
	const char *shaderSource = shaderFile.c_str();
	GLint length = (GLint)shaderFile.size();
	glShaderSource(shader, 1, &shaderSource, &length);
	glCompileShader(shader);

	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shaderName << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return (shader);
}

void	openGL::CreateShaders(void) {
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	unsigned int vertexShader = openGL::CompileShader("srcs/openGL/VertexShader.glsl", GL_VERTEX_SHADER, "VERTEX");
	unsigned int fragmentShader = openGL::CompileShader("srcs/openGL/FragmentShader.glsl", GL_FRAGMENT_SHADER, "FRAGMENT");

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int  success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	this->_shaderProgram = shaderProgram;
}

void	openGL::LoadScene(std::vector<vec3>& vertices, std::vector<u32>& indices) {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), nullptr);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	this->_VAO = VAO;
}

void processInput(GLFWwindow *window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void openGL::Loop(void) {
	while (!glfwWindowShouldClose(this->_window)) {
		processInput(this->_window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();

		glUseProgram(this->_shaderProgram);
		glBindVertexArray(this->_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(this->_window);
	}

	glfwDestroyWindow(this->_window);
	glfwTerminate();
	printf("✓ Cleaning OK, program stopping\n");
}