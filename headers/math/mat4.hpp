#ifndef MAT4_HPP
# define MAT4_HPP

# include <iostream>
# include <array>
# include "vec4.hpp"
# include "types.hpp"
# include "ft_math.hpp"

template <typename T>
struct mat4 {

	std::array<T, 16> data = {0};

	mat4(void) = default;
	mat4(const mat4& mat) = default;

	mat4&	operator=(const mat4& mat) = default;

	T&	operator[](const int64_t idx);

	bool	operator==(const mat4& mat) const;
	bool	operator!=(const mat4& mat) const;

	mat4	operator+(const mat4& mat) const;
	mat4	operator-(const mat4& mat) const;
	mat4	operator*(const mat4& mat) const;
	// mat4	operator/(const mat4& mat) const;
	mat4&	operator+=(const mat4& mat);
	mat4&	operator-=(const mat4& mat);
	mat4&	operator*=(const mat4& mat);
	// mat4&	operator/=(const mat4& mat);

	vec4	operator*(const vec4& vec) const;
	// vec4	operator/(const vec4& vec) const;
	vec4&	operator*=(const vec4& vec);
	// vec4&	operator/=(const vec4& vec);

	mat4	operator+(const float scalar) const;
	mat4	operator-(const float scalar) const;
	mat4	operator*(const float scalar) const;
	mat4	operator/(const float scalar) const;
	mat4&	operator+=(const float scalar);
	mat4&	operator-=(const float scalar);
	mat4&	operator*=(const float scalar);
	mat4&	operator/=(const float scalar);

};

template <typename T>
inline T&	mat4<T>::operator[](const i64 idx)
{
	if (idx < 0 || idx >= 16)
		throw std::out_of_range("mat4 index must be between 0 and 15");
	return (this->data[idx]);
}

template <typename T>
inline bool	mat4<T>::operator==(const mat4& mat) const {
	return (this->data == mat.data);
}

template <typename T>
inline bool	mat4<T>::operator!=(const mat4& mat) const
{
	return (this->data != mat.data);
}

template <typename T>
inline mat4<T>	mat4<T>::operator+(const mat4& mat) const
{
	mat4	newMat;

	for (u32 i = 0; i < 16; ++i) {
		newMat = this->data[i] + mat.data[i];
	}

	return (newMat);
}

template <typename T>
inline mat4<T>	mat4<T>::operator-(const mat4& mat) const
{
	mat4	newMat;

	for (u32 i = 0; i < 16; ++i) {
		newMat = this->data[i] - mat.data[i];
	}

	return (newMat);
}

template <typename T>
inline mat4<T>	mat4<T>::operator*(const mat4& mat) const
{
	mat4	newMat;

	for (u32 i = 0; i < 16; ++i) {
		u32 j = 0;
		u32 k = i % 4;
		while (j < 4) {
			newMat[i] += this->data[j] * mat.data[k];
			j++;
			k += 4;
		}
	}

	return (newMat);
}

/* template <typename T>
inline mat4<T>	mat4<T>::operator/(const mat4& mat) const
{
	mat4	newMat;

	for (u32 i = 0; i < 16; ++i) {
		u32 j = 0;
		u32 k = i % 4;
		while (j < 4) {
			newMat[i] += this->data[j] / mat.data[k];
			j++;
			k += 4;
		}
	}

	return (newMat);
} */

template <typename T>
inline mat4<T>&	mat4<T>::operator+=(const mat4& mat)
{
	for (int i = 0; i < 16; ++i) {
		this->data[i] += mat.data[i];
	}

	return (*this);
}

template <typename T>
inline mat4<T>&	mat4<T>::operator-=(const mat4& mat)
{
	for (int i = 0; i < 16; ++i) {
		this->data[i] -= mat.data[i];
	}

	return (*this);
}

template <typename T>
inline mat4<T>&	mat4<T>::operator*=(const mat4& mat)
{
	std::array<float, 16> newArr = {0};

	for (u32 i = 0; i < 16; ++i) {
		u32 j = 0;
		u32 k = i % 4;
		while (j < 4) {
			newArr[i] += this->data[j] * mat.data[k];
			j++;
			k += 4;
		}
	}

	this->data = newArr;
	return (*this);
}

/* template <typename T>
inline mat4<T>&	mat4<T>::operator/=(const mat4& mat)
{
	std::array<float, 16> newArr = {0};

	for (u32 i = 0; i < 16; ++i) {
		u32 j = 0;
		u32 k = i % 4;
		while (j < 4) {
			newArr[i] += this->data[j] / mat.data[k];
			j++;
			k += 4;
		}
	}

	this->data = newArr;
	return (*this);
} */

template <typename T>
vec4	mat4<T>::operator*(const vec4& vec) const {
	vec4	newVec;

	for (u32 i = 0; i < 4; ++i) {
		u32 j = 0;
		u32 k = i % 4;
		while (j < 4) {
			newVec[i] += this->data[j] * vec[k];
			j++;
			k += 4;
		}
	}

	return (newVec);
}

/* template <typename T>
vec4	mat4<T>::operator/(const vec4& vec) const {

} */

template <typename T>
vec4&	mat4<T>::operator*=(const vec4& vec) {
	std::array<float, 16> newArr = {0};

	for (u32 i = 0; i < 4; ++i) {
		u32 j = 0;
		u32 k = i % 4;
		while (j < 4) {
			newArr[i] += this->data[j] * vec[k];
			j++;
			k += 4;
		}
	}

	this->data = newArr;
	return (*this);
}

/* template <typename T>
vec4&	mat4<T>::operator/=(const vec4& vec) {

} */

template <typename T>
inline mat4<T>	mat4<T>::operator+(const float scalar) const
{
	mat4	newMat;

	for (u32 i = 0; i < 16; ++i) {
		newMat[i] = this->data[i] + scalar;
	}

	return (newMat);
}

template <typename T>
inline mat4<T>	mat4<T>::operator-(const float scalar) const
{
	mat4	newMat;

	for (u32 i = 0; i < 16; ++i) {
		newMat[i] = this->data[i] - scalar;
	}

	return (newMat);
}

template <typename T>
inline mat4<T>	mat4<T>::operator*(const float scalar) const
{
	mat4	newMat;

	for (u32 i = 0; i < 16; ++i) {
		newMat[i] = this->data[i] * scalar;
	}

	return (newMat);
}

template <typename T>
inline mat4<T>	mat4<T>::operator/(const float scalar) const
{
	mat4	newMat;

	for (u32 i = 0; i < 16; ++i) {
		newMat[i] = this->data[i] * scalar;
	}

	return (newMat);
}

template <typename T>
inline mat4<T>&	mat4<T>::operator+=(const float scalar)
{
	for (u32 i = 0; i < 16; ++i) {
		this->data[i] += scalar;
	}

	return (*this);
}

template <typename T>
inline mat4<T>&	mat4<T>::operator-=(const float scalar)
{
	for (u32 i = 0; i < 16; ++i) {
		this->data[i] -= scalar;
	}

	return (*this);
}

template <typename T>
inline mat4<T>&	mat4<T>::operator*=(const float scalar)
{
	for (u32 i = 0; i < 16; ++i) {
		this->data[i] *= scalar;
	}

	return (*this);
}

template <typename T>
inline mat4<T>&	mat4<T>::operator/=(const float scalar)
{
	for (u32 i = 0; i < 16; ++i) {
		this->data[i] /= scalar;
	}

	return (*this);
}

#endif //!MAT4_HPP