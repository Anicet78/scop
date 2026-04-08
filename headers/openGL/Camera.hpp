#ifndef CAMERA_HPP
# define CAMERA_HPP

#include "vec3.hpp"
#include "mat4.hpp"

class Camera {

	private:
		vec3	_pos;
		vec3	_target;

	public:
		Camera(const vec3& position = vec3(), const vec3& target = vec3());
		~Camera(void);

		Camera&	operator=(const Camera& cam) = default;

		void	setPosition(const vec3& position);
		void	setTarget(const vec3& target);
		vec3	getPosition(void);
		vec3	getTarget(void);

		mat4	lookAt(const vec3& up = vec3::up());

		static mat4	lookAt(const vec3& cameraPos, const vec3& cameraTarget, const vec3& up = vec3::up());

};

#endif // !CAMERA_HPP