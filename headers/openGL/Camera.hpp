#ifndef CAMERA_HPP
# define CAMERA_HPP

#include "vec3.hpp"
#include "mat4.hpp"

class Camera {

	private:
		vec3	_pos;
		vec3	_direction;
		float	_fov;
		float	_speed;
		float	_sensitivity;

	public:
		Camera(const vec3& position = vec3(), const vec3& direction = vec3::front());
		~Camera(void);

		Camera&	operator=(const Camera& cam) = default;

		void	setPosition(const vec3& position);
		void	setDirection(const vec3& direction);
		void	setRadFOV(float fov);
		void	setDegFOV(float fov);
		void	setSpeed(float speed);
		void	setSensitivity(float sensitivity);
		vec3	getPosition(void) const;
		vec3	getDirection(void) const;
		float	getRadFOV(void) const;
		float	getDegFOV(void) const;
		float	getSpeed(void) const;
		float	getSensitivity(void) const;

		mat4	lookAt(const vec3& up = vec3::up());

		static mat4	lookAt(const vec3& cameraPos, const vec3& cameraDirection, const vec3& up = vec3::up());

};

#endif // !CAMERA_HPP