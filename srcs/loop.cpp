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

	// float timeValue = glfwGetTime();
	// float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	// int vertexColorLocation = glGetUniformLocation(openGL.getShaderProgram(), "ourColor");
	// glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	mat4 model = mat4::identity();
	model = mat4::rotate(model, (float)glfwGetTime() * radians(50.0f), vec3(0.5f, 1.0f, 0.0f));

	mat4 view = mat4::identity();
	view = mat4::translate(view, vec3(0.0f, 0.0f, -5.0f));

	mat4 projection;
	projection = mat4::perspective(
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
