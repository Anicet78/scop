#include "scop.hpp"

static openGL* openGL_ptr = NULL;
Chrono chrono;
u8 renderType = render_type::COLORED;
float coloredOpacity = 1.0f;
float smoothOpacity = 0.0f;
float imgOpacity = 0.0f;
mat4 modelToPivot = mat4::identity();
mat4 modelFromPivot = mat4::identity();
float rotationSpeed = 0.9f;
i8 rotationDirection = 1;

static void processMovement(openGL& openGL) {
	GLFWwindow*	window = openGL.getWindow();
	static int	prevCtrlState = GLFW_RELEASE;

	float	cameraSpeed = openGL.cam.getSpeed();
	vec3	cameraPos = openGL.cam.getPosition();
	vec3	cameraDirection = openGL.cam.getDirection();
	vec3	cameraUp = vec3::up();
	vec3	forward = cameraDirection.normalized();

	if (forward.lengthSquared() <= FT_EPSILON * FT_EPSILON)
		forward = vec3::front();

	vec3	right = -cameraUp.cross(forward).normalized();
	vec3	up = right.cross(forward).normalized();
	vec3	delta;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		delta += cameraSpeed * forward;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		delta -= cameraSpeed * forward;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		delta -= right * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		delta += right * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		delta += up * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		delta -= up * cameraSpeed;

	int ctrlState = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL);
	if (ctrlState == GLFW_PRESS && prevCtrlState == GLFW_RELEASE)
		openGL.cam.setSpeed(0.09);
	else if (ctrlState == GLFW_RELEASE && prevCtrlState == GLFW_PRESS)
		openGL.cam.setSpeed(0.05);
	prevCtrlState = ctrlState;

	openGL.cam.setPosition(cameraPos + delta);
}

static void processOpacity(openGL& openGL) {
	GLFWwindow*	window = openGL.getWindow();
	static int	prevTabState = GLFW_RELEASE;

	int tabState = glfwGetKey(window, GLFW_KEY_TAB);
	if (tabState == GLFW_RELEASE && prevTabState == GLFW_PRESS) {
		if (++renderType > render_type::IMAGE)
			renderType = render_type::COLORED;
	}
	prevTabState = tabState;

	if (renderType == render_type::COLORED) {
		if (coloredOpacity < 1.0f)
			coloredOpacity += 0.05f;

		if (imgOpacity > 0.0f)
			imgOpacity -= 0.05f;
		if (smoothOpacity > 0.0f)
			smoothOpacity -= 0.05f;
	}
	else if (renderType == render_type::SMOOTH) {
		if (smoothOpacity < 1.0f)
			smoothOpacity += 0.05f;

		if (coloredOpacity > 0.0f)
			coloredOpacity -= 0.05f;
		if (imgOpacity > 0.0f)
			imgOpacity -= 0.05f;
	}
	else if (renderType == render_type::IMAGE) {
		if (imgOpacity < 1.0f)
			imgOpacity += 0.05f;

		if (coloredOpacity > 0.0f)
			coloredOpacity -= 0.05f;
		if (smoothOpacity > 0.0f)
			smoothOpacity -= 0.05f;
	}

	if (coloredOpacity < 0.0f)
		coloredOpacity = 0.0f;
	if (smoothOpacity < 0.0f)
		smoothOpacity = 0.0f;
	if (imgOpacity < 0.0f)
		imgOpacity = 0.0f;
}

static void processRotation(openGL& openGL) {
	GLFWwindow*	window = openGL.getWindow();
	static bool	rotating = true;
	static int	prevAltState = GLFW_RELEASE;

	int altState = glfwGetKey(window, GLFW_KEY_LEFT_ALT);
	if (altState == GLFW_RELEASE && prevAltState == GLFW_PRESS) {
		rotating = !rotating;
		if (!rotating)
			chrono.Stop();
		else
			chrono.Resume();
	}
	prevAltState = altState;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		if (rotationSpeed < 10.0)
			rotationSpeed += 0.05;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if (rotationSpeed > 0.4)
			rotationSpeed -= 0.05;
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		rotationDirection = 1;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		rotationDirection = -1;
	}
}

void processInput(openGL& openGL) {
	GLFWwindow*	window = openGL.getWindow();

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	processMovement(openGL);
	processOpacity(openGL);
	processRotation(openGL);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	(void)window;
	if (!openGL_ptr)
		return ;

	static bool		initialized = false;
	static float	lastX = 0.0f;
	static float	lastY = 0.0f;
	static float	yaw = 0.0f;
	static float	pitch = 0.0f;

	if (!initialized) {
		lastX = static_cast<float>(xpos);
		lastY = static_cast<float>(ypos);

		vec3 currentDir = openGL_ptr->cam.getDirection().normalized();
		if (currentDir.lengthSquared() <= FT_EPSILON * FT_EPSILON)
			currentDir = vec3::front();

		yaw = degrees(atan2f(currentDir.z, currentDir.x));
		pitch = degrees(asinf(currentDir.y));
		initialized = true;
		return ;
	}

	float xoffset = static_cast<float>(xpos) - lastX;
	float yoffset = lastY - static_cast<float>(ypos);
	lastX = static_cast<float>(xpos);
	lastY = static_cast<float>(ypos);

	float sensitivity = openGL_ptr->cam.getSensitivity();
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;

	vec3 front;
	front.x = cosf(radians(yaw)) * cosf(radians(pitch));
	front.y = sinf(radians(pitch));
	front.z = sinf(radians(yaw)) * cosf(radians(pitch));
	openGL_ptr->cam.setDirection(front.normalized());
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	(void)window;
	(void)xoffset;
	if (!openGL_ptr)
		return ;

	float fov = openGL_ptr->cam.getDegFOV();

	if((fov >= 1.0f && yoffset > 0) || (fov <= 45.0f && yoffset < 0))
		fov -= yoffset;

	if(fov < 1.0f)
		fov = 1.0f;
	else if(fov > 45.0f)
		fov = 45.0f;

	openGL_ptr->cam.setDegFOV(fov);
}

vec3	findModelCenter(ObjParser& objParser) {
	float	x = 0;
	float	y = 0;
	float	z = 0;
	float	lenInv = 1.0f / static_cast<float>(objParser.raw.vertices.size());

	for (parser::Vertex vertex: objParser.raw.vertices) {
		x += vertex.x * lenInv;
		y += vertex.y * lenInv;
		z += vertex.z * lenInv;
	}

	return vec3(x, y, z);
}

void	setup(openGL& openGL, ObjParser& objParser) {
	openGL_ptr = &openGL;
	chrono.Start();

	openGL.cam.setPosition(vec3(0.0f, 0.0f, -5.0f));
	openGL.cam.setDirection(vec3::front());
	openGL.cam.setDegFOV(45.0f);
	openGL.cam.setSensitivity(0.05f);
	openGL.cam.setSpeed(0.06f);

	glfwSetInputMode(openGL.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(openGL.getWindow(), &mouseCallback);
	glfwSetScrollCallback(openGL.getWindow(), &scrollCallback);

	vec3 pivot = findModelCenter(objParser);
	modelToPivot.translate(pivot);
	modelFromPivot.translate(-pivot);
}
