#ifndef MAT4_HPP
# define MAT4_HPP

# include <iostream>
# include <array>
# include <cmath>
# include <stdexcept>
# include "vec4.hpp"
# include "types.hpp"
# include "ft_math.hpp"

struct mat4 {

	std::array<float, 16> data = {0};

	mat4(void) = default;
	mat4(const mat4& mat) = default;

	mat4&	operator=(const mat4& mat) = default;

	float&			operator[](const i64 idx);
	const float&	operator[](const i64 idx) const;

	bool	operator==(const mat4& mat) const;
	bool	operator!=(const mat4& mat) const;
	bool	equalsEpsilon(const mat4& mat, float epsilon = static_cast<float>(FT_EPSILON)) const;

	mat4	operator+(const mat4& mat) const;
	mat4	operator-(const mat4& mat) const;
	mat4	operator*(const mat4& mat) const;
	mat4	operator/(const mat4& mat) const;
	mat4&	operator+=(const mat4& mat);
	mat4&	operator-=(const mat4& mat);
	mat4&	operator*=(const mat4& mat);
	mat4&	operator/=(const mat4& mat);

	vec4	operator*(const vec4& vec) const;
	mat4&	scaleColumns(const vec4& vec);
	mat4&	divideColumns(const vec4& vec);

	mat4	operator+(const float scalar) const;
	mat4	operator-(const float scalar) const;
	mat4	operator*(const float scalar) const;
	mat4	operator/(const float scalar) const;
	mat4&	operator+=(const float scalar);
	mat4&	operator-=(const float scalar);
	mat4&	operator*=(const float scalar);
	mat4&	operator/=(const float scalar);

	mat4	inverse(void) const;
	mat4&	translate(const vec3& vec);
	mat4&	scale(const vec3& vec);
	mat4&	rotate(float radian, const vec3& vec);

	static mat4	identity(void);
	static mat4	translate(const mat4& mat, const vec3& vec);
	static mat4	scale(const mat4& mat, const vec3& vec);
	static mat4	rotate(const mat4& mat, float radian, const vec3& vec);
	static mat4	perspective(float fov, float aspect, float near, float far);
};

inline float&	mat4::operator[](const i64 idx)
{
	if (idx < 0 || idx >= 16)
		throw std::out_of_range("mat4 index must be between 0 and 15");
	return (this->data[idx]);
}

inline const float&	mat4::operator[](const i64 idx) const
{
	if (idx < 0 || idx >= 16)
		throw std::out_of_range("mat4 index must be between 0 and 15");
	return (this->data[idx]);
}

inline bool	mat4::operator==(const mat4& mat) const {
	return (this->data == mat.data);
}

inline bool	mat4::operator!=(const mat4& mat) const
{
	return (this->data != mat.data);
}

inline bool	mat4::equalsEpsilon(const mat4& mat, float epsilon) const
{
	for (u32 i = 0; i < 16; ++i) {
		if (std::fabs(this->data[i] - mat.data[i]) > epsilon)
			return (false);
	}
	return (true);
}

inline mat4	mat4::operator+(const mat4& mat) const
{
	mat4	newMat;

	for (u32 i = 0; i < 16; ++i) {
		newMat[i] = this->data[i] + mat.data[i];
	}

	return (newMat);
}

inline mat4	mat4::operator-(const mat4& mat) const
{
	mat4	newMat;

	for (u32 i = 0; i < 16; ++i) {
		newMat[i] = this->data[i] - mat.data[i];
	}

	return (newMat);
}

inline mat4	mat4::operator*(const mat4& mat) const
{
	mat4	newMat;

	for (u32 row = 0; row < 4; ++row) {
		for (u32 col = 0; col < 4; ++col) {
			for (u32 k = 0; k < 4; ++k) {
				newMat[row * 4 + col] += this->data[row * 4 + k] * mat.data[k * 4 + col];
			}
		}
	}

	return (newMat);
}

inline mat4	mat4::operator/(const mat4& mat) const
{
	return ((*this) * mat.inverse());
}

inline mat4&	mat4::operator+=(const mat4& mat)
{
	for (int i = 0; i < 16; ++i) {
		this->data[i] += mat.data[i];
	}

	return (*this);
}

inline mat4&	mat4::operator-=(const mat4& mat)
{
	for (int i = 0; i < 16; ++i) {
		this->data[i] -= mat.data[i];
	}

	return (*this);
}

inline mat4&	mat4::operator*=(const mat4& mat)
{
	std::array<float, 16> newArr = {0};

	for (u32 row = 0; row < 4; ++row) {
		for (u32 col = 0; col < 4; ++col) {
			for (u32 k = 0; k < 4; ++k) {
				newArr[row * 4 + col] += this->data[row * 4 + k] * mat.data[k * 4 + col];
			}
		}
	}

	this->data = newArr;
	return (*this);
}

inline mat4&	mat4::operator/=(const mat4& mat)
{
	(*this) *= mat.inverse();
	return (*this);
}

inline vec4	mat4::operator*(const vec4& vec) const {
	vec4	newVec;

	for (u32 row = 0; row < 4; ++row) {
		for (u32 col = 0; col < 4; ++col) {
			newVec[row] += this->data[row * 4 + col] * vec[col];
		}
	}

	return (newVec);
}

inline mat4	mat4::inverse(void) const
{
	double aug[4][8] = {
		{static_cast<double>(this->data[0]), static_cast<double>(this->data[1]), static_cast<double>(this->data[2]), static_cast<double>(this->data[3]), 1.0, 0.0, 0.0, 0.0},
		{static_cast<double>(this->data[4]), static_cast<double>(this->data[5]), static_cast<double>(this->data[6]), static_cast<double>(this->data[7]), 0.0, 1.0, 0.0, 0.0},
		{static_cast<double>(this->data[8]), static_cast<double>(this->data[9]), static_cast<double>(this->data[10]), static_cast<double>(this->data[11]), 0.0, 0.0, 1.0, 0.0},
		{static_cast<double>(this->data[12]), static_cast<double>(this->data[13]), static_cast<double>(this->data[14]), static_cast<double>(this->data[15]), 0.0, 0.0, 0.0, 1.0}
	};

	for (u32 col = 0; col < 4; ++col) {
		u32 pivot = col;
		double maxAbs = std::fabs(aug[pivot][col]);
		for (u32 row = col + 1; row < 4; ++row) {
			double currentAbs = std::fabs(aug[row][col]);
			if (currentAbs > maxAbs) {
				maxAbs = currentAbs;
				pivot = row;
			}
		}
		if (maxAbs <= static_cast<double>(FT_EPSILON))
			throw std::runtime_error("mat4 inverse: singular matrix");

		if (pivot != col) {
			for (u32 k = 0; k < 8; ++k) {
				double tmp = aug[col][k];
				aug[col][k] = aug[pivot][k];
				aug[pivot][k] = tmp;
			}
		}

		double pivotVal = aug[col][col];
		for (u32 k = 0; k < 8; ++k)
			aug[col][k] /= pivotVal;

		for (u32 row = 0; row < 4; ++row) {
			if (row == col)
				continue ;
			double factor = aug[row][col];
			for (u32 k = 0; k < 8; ++k)
				aug[row][k] -= factor * aug[col][k];
		}
	}

	mat4 out;
	for (u32 row = 0; row < 4; ++row) {
		for (u32 col = 0; col < 4; ++col)
			out[row * 4 + col] = static_cast<float>(aug[row][4 + col]);
	}
	return (out);
}

inline mat4&	mat4::scaleColumns(const vec4& vec) {
	std::array<float, 16> newArr;

	for (u32 row = 0; row < 4; ++row) {
		for (u32 col = 0; col < 4; ++col) {
			newArr[row * 4 + col] = this->data[row * 4 + col] * vec[col];
		}
	}

	this->data = newArr;
	return (*this);
}

inline mat4&	mat4::divideColumns(const vec4& vec) {
	for (u32 row = 0; row < 4; ++row) {
		for (u32 col = 0; col < 4; ++col) {
			this->data[row * 4 + col] /= vec[col];
		}
	}

	return (*this);
}

inline mat4	mat4::operator+(const float scalar) const
{
	mat4	newMat;

	for (u32 i = 0; i < 16; ++i) {
		newMat[i] = this->data[i] + scalar;
	}

	return (newMat);
}

inline mat4	mat4::operator-(const float scalar) const
{
	mat4	newMat;

	for (u32 i = 0; i < 16; ++i) {
		newMat[i] = this->data[i] - scalar;
	}

	return (newMat);
}

inline mat4	mat4::operator*(const float scalar) const
{
	mat4	newMat;

	for (u32 i = 0; i < 16; ++i) {
		newMat[i] = this->data[i] * scalar;
	}

	return (newMat);
}

inline mat4	mat4::operator/(const float scalar) const
{
	mat4	newMat;

	for (u32 i = 0; i < 16; ++i) {
		newMat[i] = this->data[i] / scalar;
	}

	return (newMat);
}

inline mat4&	mat4::operator+=(const float scalar)
{
	for (u32 i = 0; i < 16; ++i) {
		this->data[i] += scalar;
	}

	return (*this);
}

inline mat4&	mat4::operator-=(const float scalar)
{
	for (u32 i = 0; i < 16; ++i) {
		this->data[i] -= scalar;
	}

	return (*this);
}

inline mat4&	mat4::operator*=(const float scalar)
{
	for (u32 i = 0; i < 16; ++i) {
		this->data[i] *= scalar;
	}

	return (*this);
}

inline mat4&	mat4::operator/=(const float scalar)
{
	for (u32 i = 0; i < 16; ++i) {
		this->data[i] /= scalar;
	}

	return (*this);
}

inline mat4&	mat4::translate(const vec3& vec) {
	this->data[3] += vec.x;
	this->data[7] += vec.y;
	this->data[11] += vec.z;
	return (*this);
}

inline mat4&	mat4::scale(const vec3& vec) {
	this->data[0] *= vec.x;
	this->data[5] *= vec.y;
	this->data[10] *= vec.z;
	return (*this);
}

inline mat4&	mat4::rotate(float radian, const vec3& vec) {
	if (vec.lengthSquared() <= FT_EPSILON * FT_EPSILON)
		return (*this);

	const vec3 axis = vec.normalized();
	const float cosA = cosf(radian);
	const float sinA = sinf(radian);
	const float oneMinusCos = 1.0f - cosA;

	mat4 rot = mat4::identity();
	rot[0] = cosA + axis.x * axis.x * oneMinusCos;
	rot[1] = axis.x * axis.y * oneMinusCos - axis.z * sinA;
	rot[2] = axis.x * axis.z * oneMinusCos + axis.y * sinA;
	rot[4] = axis.y * axis.x * oneMinusCos + axis.z * sinA;
	rot[5] = cosA + axis.y * axis.y * oneMinusCos;
	rot[6] = axis.y * axis.z * oneMinusCos - axis.x * sinA;
	rot[8] = axis.z * axis.x * oneMinusCos - axis.y * sinA;
	rot[9] = axis.z * axis.y * oneMinusCos + axis.x * sinA;
	rot[10] = cosA + axis.z * axis.z * oneMinusCos;

	(*this) *= rot;
	return (*this);
}

inline mat4 mat4::identity(void) {
	mat4 mat;
	mat.data = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

	return (mat);
}

inline mat4	mat4::translate(const mat4& mat, const vec3& vec) {
	mat4 newMat = mat;

	newMat[3] += vec.x;
	newMat[7] += vec.y;
	newMat[11] += vec.z;
	return (newMat);
}

inline mat4	mat4::scale(const mat4& mat, const vec3& vec) {
	mat4 newMat = mat;

	newMat[0] *= vec.x;
	newMat[5] *= vec.y;
	newMat[10] *= vec.z;
	return (newMat);
}

inline mat4	mat4::rotate(const mat4& mat, float radian, const vec3& vec) {
	if (vec.lengthSquared() <= FT_EPSILON * FT_EPSILON)
		return (mat);

	const vec3 axis = vec.normalized();
	const float cosA = cosf(radian);
	const float sinA = sinf(radian);
	const float oneMinusCos = 1.0f - cosA;

	mat4 rot = mat4::identity();
	rot[0] = cosA + axis.x * axis.x * oneMinusCos;
	rot[1] = axis.x * axis.y * oneMinusCos - axis.z * sinA;
	rot[2] = axis.x * axis.z * oneMinusCos + axis.y * sinA;
	rot[4] = axis.y * axis.x * oneMinusCos + axis.z * sinA;
	rot[5] = cosA + axis.y * axis.y * oneMinusCos;
	rot[6] = axis.y * axis.z * oneMinusCos - axis.x * sinA;
	rot[8] = axis.z * axis.x * oneMinusCos - axis.y * sinA;
	rot[9] = axis.z * axis.y * oneMinusCos + axis.x * sinA;
	rot[10] = cosA + axis.z * axis.z * oneMinusCos;

	return (mat * rot);
}

inline mat4 mat4::perspective(float fov, float aspect, float near, float far)
{
	mat4 result;
	const float tanHalfFov = tan(fov / 2.0f);

	result[0] = 1.0f / (aspect * tanHalfFov);
	result[5] = 1.0f / tanHalfFov;
	result[10] = (far + near) / (near - far);
	result[11] = (2.0f * far * near) / (near - far);
	result[14] = -1.0f;

	return result;
}

inline std::ostream& operator<<(std::ostream& os, const mat4& m)
{
	os << "mat4(";
	for (u32 row = 0; row < 4; ++row) {
		os << "[";
		for (u32 col = 0; col < 4; ++col) {
			os << m.data[row * 4 + col];
			if (col < 3)
				os << ", ";
		}
		os << "]";
		if (row < 3)
			os << ", ";
	}
	os << ")";
	return (os);
}

#endif //!MAT4_HPP
