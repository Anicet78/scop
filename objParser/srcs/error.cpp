#include "ObjParser.hpp"

float	StrToFloat(const std::string& str, std::string statement, size_t countLine, std::string& fileName)
{
	float f;

	try {
		f = std::stof(str);
	}
	catch (const std::invalid_argument& e) {
		ThrowError("Invalid argument in `" + statement + "`, '" + str + "' is not a float", countLine, fileName);
	}
	catch (const std::out_of_range& e) {
		ThrowError("Invalid argument in `" + statement + "`, '" + str + "' is out of range", countLine, fileName);
	}
	return (f);
}

int	StrToInt(const std::string& str, std::string statement, size_t countLine, std::string& fileName)
{
	int i;

	try {
		i = std::stoi(str);
	}
	catch (const std::invalid_argument& e) {
		ThrowError("Invalid argument in `" + statement + "`, '" + str + "' is not an integer", countLine, fileName);
	}
	catch (const std::out_of_range& e) {
		ThrowError("Invalid argument in `" + statement + "`, '" + str + "' is out of range", countLine, fileName);
	}
	return (i);
}

[[noreturn]] void	ThrowError(std::string error)
{
	throw std::runtime_error("An error as occured: " + error);
}

[[noreturn]] void	ThrowError(std::string error, std::string& fileName)
{
	throw std::runtime_error("An error as occured from '" + fileName +"': " + error);
}

[[noreturn]] void	ThrowError(std::string error, size_t line, std::string& fileName)
{
	throw std::runtime_error("An error as occured from '" + fileName +":" + std::to_string(line) + "': " + error);
}

[[noreturn]] void	ThrowError(std::string error, std::string& token, size_t line, std::string& fileName)
{
	if (!token.empty() && token.back() == '\r')
		token.pop_back();
	throw std::runtime_error("An error as occured from '" + fileName +":" + std::to_string(line) + "': " + error + " on token '" + token + "'");
}

[[noreturn]] void	ThrowError(std::string error, std::istringstream& ss, size_t line, std::string& fileName)
{
	ss.clear();
	std::string token;
	ss >> token;
	if (!token.empty() && token.back() == '\r')
		token.pop_back();
	throw std::runtime_error("An error as occured from '" + fileName +":" + std::to_string(line) + "': " + error + " on token '" + token + "'");
}
