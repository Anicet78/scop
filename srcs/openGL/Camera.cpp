#include "Camera.hpp"

Camera::Camera(const vec3& position, const vec3& direction):_pos(position), _direction(direction.normalized()) {
	if (this->_direction.lengthSquared() <= FT_EPSILON * FT_EPSILON)
		this->_direction = vec3::front();
}

Camera::~Camera(void) {}

void	Camera::setPosition(const vec3& position) {
	this->_pos = position;
}

void	Camera::setDirection(const vec3& direction) {
	this->_direction = direction.normalized();
	if (this->_direction.lengthSquared() <= FT_EPSILON * FT_EPSILON)
		this->_direction = vec3::front();
}

void	Camera::setRadFOV(float fov) {
	this->_fov = fov;
}

void	Camera::setDegFOV(float fov) {
	this->_fov = radians(fov);
}

void	Camera::setSpeed(float speed) {
	this->_speed = speed;
}

void	Camera::setSensitivity(float sensitivity) {
	this->_sensitivity = sensitivity;
}

vec3	Camera::getPosition(void) const {
	return (this->_pos);
}

vec3	Camera::getDirection(void) const {
	return (this->_direction);
}

float	Camera::getRadFOV(void) const {
	return (this->_fov);
}

float	Camera::getDegFOV(void) const {
	return (degrees(this->_fov));
}

float	Camera::getSpeed(void) const {
	return (this->_speed);
}

float	Camera::getSensitivity(void) const {
	return (this->_sensitivity);
}

mat4	Camera::lookAt(const vec3& up) {
	mat4		result;
	vec3		direction = this->_direction;
	if (direction.lengthSquared() <= FT_EPSILON * FT_EPSILON)
		direction = vec3::front();
	const vec3	cameraTarget = this->_pos + direction;
	const vec3	camDir = vec3(this->_pos - cameraTarget).normalize();
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

mat4	Camera::lookAt(const vec3& cameraPos, const vec3& cameraDirection, const vec3& up) {
	mat4		result;
	vec3		direction = cameraDirection;
	if (direction.lengthSquared() <= FT_EPSILON * FT_EPSILON)
		direction = vec3::front();
	const vec3	cameraTarget = cameraPos + direction;
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
