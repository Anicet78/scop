#include "scop.hpp"

void*	movement_enabled;

void processInput(openGL& openGL) {
	GLFWwindow*	window = openGL.getWindow();

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float	cameraSpeed = 0.05f;
	vec3	cameraPos = openGL.cam.getPosition();
	vec3	cameraTarget = openGL.cam.getTarget();
	vec3	cameraUp = vec3::up();
	vec3	forward = (cameraTarget - cameraPos).normalized();

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

	openGL.cam.setPosition(cameraPos + delta);
	openGL.cam.setTarget(cameraTarget + delta);
}

void	loop(openGL& openGL) {
	processInput(openGL);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(openGL.getShaderProgram());

	mat4 model = mat4::identity();

	mat4 view = openGL.cam.lookAt();

	mat4 projection = mat4::perspective(
		radians(45.0f),
		static_cast<float>(openGL.getWidth()) / static_cast<float>(openGL.getHeight()),
		0.1f,
		100.0f
	);

	unsigned int modelLoc = glGetUniformLocation(openGL.getShaderProgram(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, &model.data[0]);

	unsigned int viewLoc = glGetUniformLocation(openGL.getShaderProgram(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_TRUE, &view.data[0]);

	unsigned int projectionLoc = glGetUniformLocation(openGL.getShaderProgram(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, &projection.data[0]);

	glBindVertexArray(openGL.getVAO());
	glDrawElements(GL_TRIANGLES, openGL.getIndexCount(), GL_UNSIGNED_INT, nullptr);

	glfwSwapBuffers(openGL.getWindow());
	glfwPollEvents();
}
