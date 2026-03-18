#ifndef VEC2_HPP
# define VEC2_HPP

# include <iostream>
# include <exception>
# include "ft_math.hpp"

struct vec2 {

	float	x;
	float	y;

	vec2(void);
	vec2(float x, float y);
	vec2(const vec2& vec) = default;

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

	vec2	operator+(float value) const;
	vec2	operator-(float value) const;
	vec2	operator*(float value) const;
	vec2	operator/(float value) const;
	vec2&	operator+=(float value);
	vec2&	operator-=(float value);
	vec2&	operator*=(float value);
	vec2&	operator/=(float value);

	vec2			operator-(void) const;
	float&			operator[](int idx);
	const float&	operator[](int idx) const;

	float	dot(const vec2& vec) const;
	vec2&	normalize(void);

};

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

inline vec2	vec2::operator+(float value) const
{
	return (vec2(this->x + value, this->y + value));
}

inline vec2	vec2::operator-(float value) const
{
	return (vec2(this->x - value, this->y - value));
}

inline vec2	vec2::operator*(float value) const
{
	return (vec2(this->x * value, this->y * value));
}

inline vec2	vec2::operator/(float value) const
{
	return (vec2(this->x / value, this->y / value));
}

inline vec2&	vec2::operator+=(float value)
{
	this->x += value;
	this->y += value;
	return (*this);
}

inline vec2&	vec2::operator-=(float value)
{
	this->x -= value;
	this->y -= value;
	return (*this);
}

inline vec2&	vec2::operator*=(float value)
{
	this->x *= value;
	this->y *= value;
	return (*this);
}

inline vec2&	vec2::operator/=(float value)
{
	this->x /= value;
	this->y /= value;
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

inline float	vec2::dot(const vec2& vec) const
{
	return (this->x * vec.x + this->y * vec.y);
}

inline vec2&	vec2::normalize(void)
{
	*this * Q_rsqrt(this->dot(*this));
	return (*this);
}

inline std::ostream& operator<<(std::ostream& os, const vec2& v)
{
	os << "vec4(" << v.x << ", " << v.y << ")";
	return os;
}

#endif // !VEC2_HPP
