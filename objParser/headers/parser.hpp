#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <exception>
# include <unordered_map>
# include "color.hpp"

float	StrToFloat(const std::string& str, std::string statement, size_t countLine, std::string& fileName);
int		StrToInt(const std::string& str, std::string statement, size_t countLine, std::string& fileName);

[[noreturn]] void	ThrowError(std::string error);
[[noreturn]] void	ThrowError(std::string error,  std::string& fileName);
[[noreturn]] void	ThrowError(std::string error, size_t line, std::string& fileName);
[[noreturn]] void	ThrowError(std::string error, std::string& token, size_t line, std::string& fileName);
[[noreturn]] void	ThrowError(std::string error, std::istringstream& ss, size_t line, std::string& fileName);

#endif // !PARSER_HPP
