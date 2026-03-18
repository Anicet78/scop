#ifndef FT_MATH_HPP
# define FT_MATH_HPP

# include <cstring>
# include <cstdint>

inline float Q_rsqrt(float number)
{
	float x2 = number * 0.5F, y = number;
	std::uint32_t i;
	std::memcpy(&i, &y, sizeof(float));
	i  = 0x5f3759df - ( i >> 1 );
	std::memcpy(&y, &i, sizeof(float));
	return y * ( 1.5F - ( x2 * y * y ) );
}

#endif // !FT_MATH_HPP
