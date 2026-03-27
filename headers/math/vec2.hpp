#ifndef VEC2_HPP
# define VEC2_HPP

# include <iostream>
# include <exception>
# include "ft_math.hpp"

struct vec3;
struct vec4;

struct vec2 {

	float	x;
	float	y;

	vec2(void);
	vec2(float x, float y);
	vec2(const vec2& vec) = default;
	vec2(const vec3& vec);
	vec2(const vec4& vec);

	vec2&	operator=(const vec2& vec) = default;

	bool	operator==(const vec2& vec) const;
	bool	operator!=(const vec2& vec) const;

	vec2	operator+(const vec2& vec) const;
	vec2	operator-(const vec2& vec) const;
	vec2	operator*(const vec2& vec) const;
	vec2	operator/(const vec2& vec) const;
	vec2&	operator+=(const vec2& vec);
	vec2&	operator-=(const vec2& vec);
	vec2&	operator*=(const vec2& vec);
	vec2&	operator/=(const vec2& vec);

	vec2	operator+(const float scalar) const;
	vec2	operator-(const float scalar) const;
	vec2	operator*(const float scalar) const;
	vec2	operator/(const float scalar) const;
	vec2&	operator+=(const float scalar);
	vec2&	operator-=(const float scalar);
	vec2&	operator*=(const float scalar);
	vec2&	operator/=(const float scalar);

	vec2			operator-(void) const;
	float&			operator[](int idx);
	const float&	operator[](int idx) const;
	float*			data(void);
	const float*	data(void) const;

	float	dot(const vec2& vec) const;
	float	lengthSquared(void) const;
	float	length(void) const;
	vec2&	normalize(void);
	vec2	normalized(void) const;
	bool	equalsEpsilon(const vec2& vec, float epsilon = FT_EPSILON) const;

};

# include "vec3.hpp"
# include "vec4.hpp"

inline vec2::vec2(void)
{
	this->x = 0.0f;
	this->y = 0.0f;
}

inline vec2::vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

inline vec2::vec2(const vec3& vec)
{
	this->x = vec.x;
	this->y = vec.y;
}

inline vec2::vec2(const vec4& vec)
{
	this->x = vec.x;
	this->y = vec.y;
}

inline bool	vec2::operator==(const vec2& vec) const
{
	return (vec.x == this->x && vec.y == this->y);
}

inline bool	vec2::operator!=(const vec2& vec) const
{
	return (vec.x != this->x || vec.y != this->y);
}

inline vec2	vec2::operator+(const vec2& vec) const
{
	return (vec2(this->x + vec.x, this->y + vec.y));
}

inline vec2	vec2::operator-(const vec2& vec) const
{
	return (vec2(this->x - vec.x, this->y - vec.y));
}

inline vec2	vec2::operator*(const vec2& vec) const
{
	return (vec2(this->x * vec.x, this->y * vec.y));
}

inline vec2	vec2::operator/(const vec2& vec) const
{
	return (vec2(this->x / vec.x, this->y / vec.y));
}

inline vec2&	vec2::operator+=(const vec2& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return (*this);
}

inline vec2&	vec2::operator-=(const vec2& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return (*this);
}

inline vec2&	vec2::operator*=(const vec2& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return (*this);
}

inline vec2&	vec2::operator/=(const vec2& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	return (*this);
}

inline vec2	vec2::operator+(const float scalar) const
{
	return (vec2(this->x + scalar, this->y + scalar));
}

inline vec2	vec2::operator-(const float scalar) const
{
	return (vec2(this->x - scalar, this->y - scalar));
}

inline vec2	vec2::operator*(const float scalar) const
{
	return (vec2(this->x * scalar, this->y * scalar));
}

inline vec2	vec2::operator/(const float scalar) const
{
	return (vec2(this->x / scalar, this->y / scalar));
}

inline vec2&	vec2::operator+=(const float scalar)
{
	this->x += scalar;
	this->y += scalar;
	return (*this);
}

inline vec2&	vec2::operator-=(const float scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	return (*this);
}

inline vec2&	vec2::operator*=(const float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	return (*this);
}

inline vec2&	vec2::operator/=(const float scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	return (*this);
}

inline vec2	vec2::operator-(void) const
{
	return (vec2(-this->x, -this->y));
}

inline float&	vec2::operator[](int idx)
{
	if (idx != 0 && idx != 1)
		throw std::runtime_error("Invalid index: " + std::to_string(idx));
	return (idx == 0 ? this->x : this->y);
}

inline const float&	vec2::operator[](int idx) const
{
	if (idx != 0 && idx != 1)
		throw std::runtime_error("Invalid index: " + std::to_string(idx));
	return (idx == 0 ? this->x : this->y);
}

inline float*	vec2::data(void)
{
	return (&this->x);
}

inline const float*	vec2::data(void) const
{
	return (&this->x);
}

inline float	vec2::dot(const vec2& vec) const
{
	return (this->x * vec.x + this->y * vec.y);
}

inline float	vec2::lengthSquared(void) const
{
	return (this->dot(*this));
}

inline float	vec2::length(void) const
{
	return (std::sqrt(this->lengthSquared()));
}

inline vec2&	vec2::normalize(void)
{
	float lenSquared = this->lengthSquared();
	if (lenSquared <= FT_EPSILON)
		return (*this);
	*this *= Q_rsqrt(lenSquared);
	return (*this);
}

inline vec2	vec2::normalized(void) const
{
	vec2 out(*this);
	out.normalize();
	return (out);
}

inline bool	vec2::equalsEpsilon(const vec2& vec, float epsilon) const
{
	return (
		std::fabs(this->x - vec.x) <= epsilon
		&& std::fabs(this->y - vec.y) <= epsilon
	);
}

inline vec2 operator*(const float scalar, const vec2& vec)
{
	return (vec * scalar);
}

inline std::ostream& operator<<(std::ostream& os, const vec2& v)
{
	os << "vec2(" << v.x << ", " << v.y << ")";
	return os;
}

#endif // !VEC2_HPP
