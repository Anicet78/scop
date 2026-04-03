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

	vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	mat4 trans = mat4::identity();
	// trans = mat4::scale(trans, vec3(0.5, 0.5, 0.5));
	// trans = mat4::translate(trans, vec3(0.5f, 0.5f, 0.0f));
	trans = mat4::rotate(trans, (float)glfwGetTime(), vec3(0.0f, 0.0f, 1.0f));
	vec = trans * vec;
	// std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;

	unsigned int transformLoc = glGetUniformLocation(openGL.getShaderProgram(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_TRUE, &trans.data[0]);

	glBindVertexArray(openGL.getVAO());
	glDrawElements(GL_TRIANGLES, openGL.getIndexCount(), GL_UNSIGNED_INT, nullptr);

	glfwSwapBuffers(openGL.getWindow());
	glfwPollEvents();
}
