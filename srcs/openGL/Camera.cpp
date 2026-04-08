#include "Camera.hpp"

Camera::Camera(const vec3& position, const vec3& target):_pos(position), _target(target) {}

Camera::~Camera(void) {}

void	Camera::setPosition(const vec3& position) {
	this->_pos = position;
}

void	Camera::setTarget(const vec3& target) {
	this->_target = target;
}

vec3	Camera::getPosition(void) {
	return (this->_pos);
}

vec3	Camera::getTarget(void) {
	return (this->_target);
}

mat4	Camera::lookAt(const vec3& up) {
	mat4		result;
	const vec3	camDir = vec3(this->_pos - this->_target).normalize();
	const vec3	camRight = up.cross(camDir).normalized();
	const vec3	camUp = camDir.cross(camRight).normalized();

	result[0] = camRight.x;
	result[1] = camRight.y;
	result[2] = camRight.z;
	result[4] = camUp.x;
	result[5] = camUp.y;
	result[6] = camUp.z;
	result[8] = camDir.x;
	result[9] = camDir.y;
	result[10] = camDir.z;
	result[15] = 1;

	return (result * mat4::translate(mat4::identity(), -this->_pos));
}

mat4	Camera::lookAt(const vec3& cameraPos, const vec3& cameraTarget, const vec3& up) {
	mat4		result;
	const vec3	camDir = vec3(cameraPos - cameraTarget).normalize();
	const vec3	camRight = up.cross(camDir).normalized();
	const vec3	camUp = camDir.cross(camRight).normalized();

	result[0] = camRight.x;
	result[1] = camRight.y;
	result[2] = camRight.z;
	result[4] = camUp.x;
	result[5] = camUp.y;
	result[6] = camUp.z;
	result[8] = camDir.x;
	result[9] = camDir.y;
	result[10] = camDir.z;
	result[15] = 1;

	return (result * mat4::translate(mat4::identity(), -cameraPos));
}
