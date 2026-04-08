#ifndef VEC3_HPP
# define VEC3_HPP

# include <iostream>
# include <exception>
# include "ft_math.hpp"

struct vec2;
struct vec4;

struct vec3 {

	float	x;
	float	y;
	float	z;

	vec3(void);
	vec3(float x, float y, float z);
	vec3(const vec3& vec) = default;
	vec3(const vec2& vec);
	vec3(const vec2& vec, float z);
	vec3(const vec4& vec);

	vec3&	operator=(const vec3& vec) = default;

	bool	operator==(const vec3& vec) const;
	bool	operator!=(const vec3& vec) const;

	vec3	operator+(const vec3& vec) const;
	vec3	operator-(const vec3& vec) const;
	vec3	operator*(const vec3& vec) const;
	vec3	operator/(const vec3& vec) const;
	vec3&	operator+=(const vec3& vec);
	vec3&	operator-=(const vec3& vec);
	vec3&	operator*=(const vec3& vec);
	vec3&	operator/=(const vec3& vec);

	vec3	operator+(const float scalar) const;
	vec3	operator-(const float scalar) const;
	vec3	operator*(const float scalar) const;
	vec3	operator/(const float scalar) const;
	vec3&	operator+=(const float scalar);
	vec3&	operator-=(const float scalar);
	vec3&	operator*=(const float scalar);
	vec3&	operator/=(const float scalar);

	vec3			operator-(void) const;
	float&			operator[](int idx);
	const float&	operator[](int idx) const;
	float*			data(void);
	const float*	data(void) const;

	float	dot(const vec3& vec) const;
	float	lengthSquared(void) const;
	float	length(void) const;
	vec3	cross(const vec3& vec) const;
	vec3&	normalize(void);
	vec3	normalized(void) const;
	bool	equalsEpsilon(const vec3& vec, float epsilon = FT_EPSILON) const;

	static vec3	up(void);
	static vec3	down(void);
	static vec3	right(void);
	static vec3	left(void);
	static vec3	front(void);
	static vec3	back(void);

};

# include "vec2.hpp"
# include "vec4.hpp"

inline vec3::vec3(void)
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

inline vec3::vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

inline vec3::vec3(const vec2& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = 0.0f;
}

inline vec3::vec3(const vec2& vec, float z)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = z;
}

inline vec3::vec3(const vec4& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}

inline bool	vec3::operator==(const vec3& vec) const
{
	return (vec.x == this->x && vec.y == this->y && vec.z == this->z);
}

inline bool	vec3::operator!=(const vec3& vec) const
{
	return (vec.x != this->x || vec.y != this->y || vec.z != this->z);
}

inline vec3	vec3::operator+(const vec3& vec) const
{
	return (vec3(this->x + vec.x, this->y + vec.y, this->z + vec.z));
}

inline vec3	vec3::operator-(const vec3& vec) const
{
	return (vec3(this->x - vec.x, this->y - vec.y, this->z - vec.z));
}

inline vec3	vec3::operator*(const vec3& vec) const
{
	return (vec3(this->x * vec.x, this->y * vec.y, this->z * vec.z));
}

inline vec3	vec3::operator/(const vec3& vec) const
{
	return (vec3(this->x / vec.x, this->y / vec.y, this->z / vec.z));
}

inline vec3&	vec3::operator+=(const vec3& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	return (*this);
}

inline vec3&	vec3::operator-=(const vec3& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	return (*this);
}

inline vec3&	vec3::operator*=(const vec3& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	this->z *= vec.z;
	return (*this);
}

inline vec3&	vec3::operator/=(const vec3& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	this->z /= vec.z;
	return (*this);
}

inline vec3	vec3::operator+(const float scalar) const
{
	return (vec3(this->x + scalar, this->y + scalar, this->z + scalar));
}

inline vec3	vec3::operator-(const float scalar) const
{
	return (vec3(this->x - scalar, this->y - scalar, this->z - scalar));
}

inline vec3	vec3::operator*(const float scalar) const
{
	return (vec3(this->x * scalar, this->y * scalar, this->z * scalar));
}

inline vec3	vec3::operator/(const float scalar) const
{
	return (vec3(this->x / scalar, this->y / scalar, this->z / scalar));
}

inline vec3&	vec3::operator+=(const float scalar)
{
	this->x += scalar;
	this->y += scalar;
	this->z += scalar;
	return (*this);
}

inline vec3&	vec3::operator-=(const float scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	this->z -= scalar;
	return (*this);
}

inline vec3&	vec3::operator*=(const float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	return (*this);
}

inline vec3&	vec3::operator/=(const float scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;
	return (*this);
}

inline vec3	vec3::operator-(void) const
{
	return (vec3(-this->x, -this->y, -this->z));
}

inline float&	vec3::operator[](int idx)
{
	if (idx < 0 || idx > 2)
		throw std::runtime_error("Invalid index: " + std::to_string(idx));
	return (idx == 0 ? this->x : idx == 1 ? this->y : this->z);
}

inline const float&	vec3::operator[](int idx) const
{
	if (idx < 0 || idx > 2)
		throw std::runtime_error("Invalid index: " + std::to_string(idx));
	return (idx == 0 ? this->x : idx == 1 ? this->y : this->z);
}

inline float*	vec3::data(void)
{
	return (&this->x);
}

inline const float*	vec3::data(void) const
{
	return (&this->x);
}

inline float	vec3::dot(const vec3& vec) const
{
	return (this->x * vec.x + this->y * vec.y + this->z * vec.z);
}

inline float	vec3::lengthSquared(void) const
{
	return (this->dot(*this));
}

inline float	vec3::length(void) const
{
	return (std::sqrt(this->lengthSquared()));
}

inline vec3	vec3::cross(const vec3& vec) const
{
	return (vec3(
		this->y * vec.z - this->z * vec.y,
		this->z * vec.x - this->x * vec.z,
		this->x * vec.y - this->y * vec.x
	));
}

inline vec3&	vec3::normalize(void)
{
	float lenSquared = this->lengthSquared();
	if (lenSquared <= FT_EPSILON * FT_EPSILON)
		return (*this);
	*this *= Q_rsqrt(lenSquared);
	return (*this);
}

inline vec3	vec3::normalized(void) const
{
	vec3 out(*this);
	out.normalize();
	return (out);
}

inline bool	vec3::equalsEpsilon(const vec3& vec, float epsilon) const
{
	return (
		std::fabs(this->x - vec.x) <= epsilon
		&& std::fabs(this->y - vec.y) <= epsilon
		&& std::fabs(this->z - vec.z) <= epsilon
	);
}

inline vec3 operator*(const float scalar, const vec3& vec)
{
	return (vec * scalar);
}

inline vec3	vec3::up(void)
{
	return (vec3(0, 1, 0));
}

inline vec3	vec3::down(void)
{
	return (vec3(0, -1, 0));
}

inline vec3	vec3::right(void)
{
	return (vec3(1, 0, 0));
}

inline vec3	vec3::left(void)
{
	return (vec3(-1, 0, 0));
}

inline vec3	vec3::front(void)
{
	return (vec3(0, 0, 1));
}

inline vec3	vec3::back(void)
{
	return (vec3(0, 0, -1));
}

inline std::ostream& operator<<(std::ostream& os, const vec3& v)
{
	os << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}

#endif // !VEC3_HPP
