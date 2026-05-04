#include "scop.hpp"

void	loop(openGL& openGL) {
	processInput(openGL);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(openGL.getShaderProgram());

	static double lastTime = 0.0;
	static double accumulatedAngle = 0.0;

	double now = chrono.getElapsedSeconds();
	if (now < lastTime) {
		lastTime = now;
		accumulatedAngle = 0.0;
	}
	const double delta = now - lastTime;
	lastTime = now;
	accumulatedAngle += delta * radians(45.0f * rotationDirection) * rotationSpeed;

	float angle = static_cast<float>(accumulatedAngle);
	mat4 rotation = mat4::identity().rotate(angle, vec3(0, 1, 0));
	mat4 model = modelToPivot * rotation * modelFromPivot;

	mat4 view = openGL.cam.lookAt();

	mat4 projection = mat4::perspective(
		openGL.cam.getRadFOV(),
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

	unsigned int coloredOpacityLoc = glGetUniformLocation(openGL.getShaderProgram(), "coloredOpacity");
	glUniform1f(coloredOpacityLoc, coloredOpacity);

	unsigned int smoothOpacityLoc = glGetUniformLocation(openGL.getShaderProgram(), "smoothOpacity");
	glUniform1f(smoothOpacityLoc, smoothOpacity);

	unsigned int imgOpacityLoc = glGetUniformLocation(openGL.getShaderProgram(), "imgOpacity");
	glUniform1f(imgOpacityLoc, imgOpacity);

	glBindVertexArray(openGL.getVAO());
	glBindTexture(GL_TEXTURE_2D, openGL.getTexture());
	glDrawElements(GL_TRIANGLES, openGL.getIndexCount(), GL_UNSIGNED_INT, nullptr);

	glfwSwapBuffers(openGL.getWindow());
	glfwPollEvents();
}
