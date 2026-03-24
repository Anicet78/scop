#ifndef VEC4_HPP
# define VEC4_HPP

# include <iostream>
# include <exception>
# include "ft_math.hpp"

struct vec2;
struct vec3;

struct vec4 {

	float	x;
	float	y;
	float	z;
	float	w;

	vec4(void);
	vec4(float x, float y, float z, float w);
	vec4(const vec4& vec) = default;
	vec4(const vec2& vec);
	vec4(const vec2& vec, float z, float w);
	vec4(const vec3& vec);
	vec4(const vec3& vec, float w);

	vec4&	operator=(const vec4& vec) = default;

	bool	operator==(const vec4& vec) const;
	bool	operator!=(const vec4& vec) const;

	vec4	operator+(const vec4& vec) const;
	vec4	operator-(const vec4& vec) const;
	vec4	operator*(const vec4& vec) const;
	vec4	operator/(const vec4& vec) const;
	vec4&	operator+=(const vec4& vec);
	vec4&	operator-=(const vec4& vec);
	vec4&	operator*=(const vec4& vec);
	vec4&	operator/=(const vec4& vec);

	vec4	operator+(float value) const;
	vec4	operator-(float value) const;
	vec4	operator*(float value) const;
	vec4	operator/(float value) const;
	vec4&	operator+=(float value);
	vec4&	operator-=(float value);
	vec4&	operator*=(float value);
	vec4&	operator/=(float value);

	vec4			operator-(void) const;
	float&			operator[](int idx);
	const float&	operator[](int idx) const;
	float*			data(void);
	const float*	data(void) const;

	float	dot(const vec4& vec) const;
	float	lengthSquared(void) const;
	float	length(void) const;
	vec4&	normalize(void);
	vec4	normalized(void) const;
	bool	equalsEpsilon(const vec4& vec, float epsilon = FT_EPSILON) const;

};

# include "vec2.hpp"
# include "vec3.hpp"

inline vec4::vec4(void)
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 0.0f;
}

inline vec4::vec4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

inline vec4::vec4(const vec2& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = 0.0f;
	this->w = 0.0f;
}

inline vec4::vec4(const vec2& vec, float z, float w)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = z;
	this->w = w;
}

inline vec4::vec4(const vec3& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = 0.0f;
}

inline vec4::vec4(const vec3& vec, float w)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = w;
}

inline bool	vec4::operator==(const vec4& vec) const
{
	return (vec.x == this->x && vec.y == this->y && vec.z == this->z && vec.w == this->w);
}

inline bool	vec4::operator!=(const vec4& vec) const
{
	return (vec.x != this->x || vec.y != this->y || vec.z != this->z || vec.w != this->w);
}

inline vec4	vec4::operator+(const vec4& vec) const
{
	return (vec4(this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w));
}

inline vec4	vec4::operator-(const vec4& vec) const
{
	return (vec4(this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w));
}

inline vec4	vec4::operator*(const vec4& vec) const
{
	return (vec4(this->x * vec.x, this->y * vec.y, this->z * vec.z, this->w * vec.w));
}

inline vec4	vec4::operator/(const vec4& vec) const
{
	return (vec4(this->x / vec.x, this->y / vec.y, this->z / vec.z, this->w / vec.w));
}

inline vec4&	vec4::operator+=(const vec4& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	this->w += vec.w;
	return (*this);
}

inline vec4&	vec4::operator-=(const vec4& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	this->w -= vec.w;
	return (*this);
}

inline vec4&	vec4::operator*=(const vec4& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	this->z *= vec.z;
	this->w *= vec.w;
	return (*this);
}

inline vec4&	vec4::operator/=(const vec4& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	this->z /= vec.z;
	this->w /= vec.w;
	return (*this);
}

inline vec4	vec4::operator+(float value) const
{
	return (vec4(this->x + value, this->y + value, this->z + value, this->w + value));
}

inline vec4	vec4::operator-(float value) const
{
	return (vec4(this->x - value, this->y - value, this->z - value, this->w - value));
}

inline vec4	vec4::operator*(float value) const
{
	return (vec4(this->x * value, this->y * value, this->z * value, this->w * value));
}

inline vec4	vec4::operator/(float value) const
{
	return (vec4(this->x / value, this->y / value, this->z / value, this->w / value));
}

inline vec4&	vec4::operator+=(float value)
{
	this->x += value;
	this->y += value;
	this->z += value;
	this->w += value;
	return (*this);
}

inline vec4&	vec4::operator-=(float value)
{
	this->x -= value;
	this->y -= value;
	this->z -= value;
	this->w -= value;
	return (*this);
}

inline vec4&	vec4::operator*=(float value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	this->w *= value;
	return (*this);
}

inline vec4&	vec4::operator/=(float value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;
	this->w /= value;
	return (*this);
}

inline vec4	vec4::operator-(void) const
{
	return (vec4(-this->x, -this->y, -this->z, -this->w));
}

inline float&	vec4::operator[](int idx)
{
	if (idx < 0 || idx > 3)
		throw std::runtime_error("Invalid index: " + std::to_string(idx));
	return (idx == 0 ? this->x : idx == 1 ? this->y : idx == 2 ? this->z : this->w);
}

inline const float&	vec4::operator[](int idx) const
{
	if (idx < 0 || idx > 3)
		throw std::runtime_error("Invalid index: " + std::to_string(idx));
	return (idx == 0 ? this->x : idx == 1 ? this->y : idx == 2 ? this->z : this->w);
}

inline float*	vec4::data(void)
{
	return (&this->x);
}

inline const float*	vec4::data(void) const
{
	return (&this->x);
}

inline float	vec4::dot(const vec4& vec) const
{
	return (this->x * vec.x + this->y * vec.y + this->z * vec.z + this->w * vec.w);
}

inline float	vec4::lengthSquared(void) const
{
	return (this->dot(*this));
}

inline float	vec4::length(void) const
{
	return (std::sqrt(this->lengthSquared()));
}

inline vec4&	vec4::normalize(void)
{
	float lenSquared = this->lengthSquared();
	if (lenSquared <= FT_EPSILON)
		return (*this);
	*this *= Q_rsqrt(lenSquared);
	return (*this);
}

inline vec4	vec4::normalized(void) const
{
	vec4 out(*this);
	out.normalize();
	return (out);
}

inline bool	vec4::equalsEpsilon(const vec4& vec, float epsilon) const
{
	return (
		std::fabs(this->x - vec.x) <= epsilon
		&& std::fabs(this->y - vec.y) <= epsilon
		&& std::fabs(this->z - vec.z) <= epsilon
		&& std::fabs(this->w - vec.w) <= epsilon
	);
}

inline vec4 operator*(float value, const vec4& vec)
{
	return (vec * value);
}

inline std::ostream& operator<<(std::ostream& os, const vec4& v)
{
	os << "vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return os;
}

#endif // !VEC4_HPP
