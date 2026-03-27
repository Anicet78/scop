#include "scop.hpp"

void processInput(GLFWwindow *window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void	loop(openGL& openGL) {
	processInput(openGL.getWindow());

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(openGL.getShaderProgram());

	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(openGL.getShaderProgram(), "ourColor");
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	glBindVertexArray(openGL.getVAO());
	glDrawElements(GL_TRIANGLES, openGL.getIndexCount(), GL_UNSIGNED_INT, nullptr);

	glfwSwapBuffers(openGL.getWindow());
	glfwPollEvents();
}
