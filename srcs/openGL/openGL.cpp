#include "openGL.hpp"

//constructors/destructors---------------------------------

openGL::openGL(void) : _width(0), _height(0), _window(nullptr), _shaderProgram(0), _VAO(0), _indexCount(0) {}

openGL::~openGL(void) {}

//Member functions-----------------------------------------

u32	openGL::getWidth(void) {
	return this->_width;
}

u32	openGL::getHeight(void) {
	return this->_height;
}

void	openGL::setWidth(u32 width) {
	this->_width = width;
}

void	openGL::setHeight(u32 height) {
	this->_height = height;
}

GLFWwindow*	openGL::getWindow(void) {
	return this->_window;
}

u32	openGL::getShaderProgram(void) {
	return this->_shaderProgram;
}

u32	openGL::getVAO(void) {
	return this->_VAO;
}

u32	openGL::getIndexCount(void) {
	return this->_indexCount;
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
	glfwWindowHint(GLFW_SAMPLES, 4);

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

	glEnable(GL_DEPTH_TEST);

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

std::string	openGL::OpenShader(std::string_view fileName) {
	std::filesystem::path shaderPath(fileName);
	std::ifstream	ifs;

	ifs.open(shaderPath);
	if (!ifs.is_open() && shaderPath.is_relative()) {
		std::error_code ec;
		const std::filesystem::path exePath = std::filesystem::read_symlink("/proc/self/exe", ec);
		if (!ec) {
			shaderPath = exePath.parent_path() / shaderPath;
			ifs.open(shaderPath);
		}
	}

	if (!ifs.is_open() || !ifs.good())
		throw std::runtime_error("Could not open shader file " + std::string(fileName) + " (resolved: " + shaderPath.string() + ")");

	std::string	content;

	content.assign((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

	return content;
}

unsigned int	openGL::CompileShader(std::string_view path, int shaderType, std::string_view shaderName) {
	unsigned int shader;
	shader = glCreateShader(shaderType);

	std::string shaderFile = openGL::OpenShader(path);
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

void	openGL::LoadScene(
	const void* vertexData,
	std::size_t vertexBufferSize,
	const void* indexData,
	std::size_t indexBufferSize,
	const std::vector<VertexAttribDesc>& attributes,
	GLenum usage
) {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, vertexData, usage);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indexData, usage);

	for (const VertexAttribDesc& attr : attributes) {
		glVertexAttribPointer(
			attr.index,
			attr.size,
			attr.type,
			attr.normalized ? GL_TRUE : GL_FALSE,
			attr.stride,
			reinterpret_cast<const void*>(attr.offset)
		);
		glEnableVertexAttribArray(attr.index);
	}

	glBindVertexArray(0);
	this->_VAO = VAO;
	this->_indexCount = static_cast<u32>(indexBufferSize / sizeof(u32));
}

void openGL::Loop(void (*loop)(openGL&)) {
	while (!glfwWindowShouldClose(this->_window)) {
		loop(*this);
	}

	glfwDestroyWindow(this->_window);
	glfwTerminate();
	printf("✓ Cleaning OK, program stopping\n");
}