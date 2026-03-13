#include "MtlParser.hpp"

bool	MtlParser::ParseOnOff(std::istringstream& ss, std::string& option, std::string& statement)
{
	if (option == "cc" && statement != "map_Ka" && statement != "map_Kd" && statement != "map_Ks" && statement != "map_Ke" && statement != "norm" && statement != "refl")
		ThrowError("This option isn't available in `" + statement + "`", option, this->countLines, this->fileName);

	std::string value;
	if (!(ss >> value))
		ThrowError("Missing argument for option '" + option + "' in `" + statement + "` (on | off)", this->countLines, this->fileName);
	if (value == "on")
		return (true);
	else if (value == "off")
		return (false);
	else
		ThrowError("Invalid argument for option '" + option + "' in `" + statement + "` (on | off)", this->countLines, this->fileName);
}

void	MtlParser::SetBumpMultiplier(std::istringstream& ss, TextureMap& map, std::string& option, std::string& statement)
{
	if (statement != "bump")
		ThrowError("This option isn't available in `" + statement + "`", option, this->countLines, this->fileName);

	std::string value;
	if (!(ss >> value))
		ThrowError("Missing argument for option '" + option + "' in `" + statement + "` (mult)", this->countLines, this->fileName);
	map.resolution = StrToFloat(value, statement, this->countLines, this->fileName);
}

void	MtlParser::SetBoost(std::istringstream& ss, TextureMap& map, std::string& option, std::string& statement)
{
	std::string value;
	if (!(ss >> value))
		ThrowError("Missing argument for option '" + option + "' in `" + statement + "` (value)", this->countLines, this->fileName);
	map.boost = StrToFloat(value, statement, this->countLines, this->fileName);
}

void	MtlParser::SetImageChan(std::istringstream& ss, TextureMap& map, std::string& option, std::string& statement)
{
	if (statement == "map_Ka" || statement == "map_Kd" || statement == "map_Ks" || statement == "map_Ke" || statement == "norm" || statement == "refl")
		ThrowError("This option isn't available in `" + statement + "`", option, this->countLines, this->fileName);

	std::string value;
	if (!(ss >> value))
		ThrowError("Missing argument for option '" + option + "' in `" + statement + "` (r | g | b | m | l | z)", this->countLines, this->fileName);
	else if (value == "r")
		map.imfchan = ImageChan::R;
	else if (value == "g")
		map.imfchan = ImageChan::G;
	else if (value == "b")
		map.imfchan = ImageChan::B;
	else if (value == "m")
		map.imfchan = ImageChan::M;
	else if (value == "l")
		map.imfchan = ImageChan::L;
	else if (value == "z")
		map.imfchan = ImageChan::Z;
	else
		ThrowError("Invalid argument for option '" + option + "' in `" + statement + "` (r | g | b | m | l | z)", this->countLines, this->fileName);
}

void	MtlParser::SetMapModifiers(std::istringstream& ss, TextureMap& map, std::string& option, std::string& statement)
{
	std::string value;
	if (!(ss >> value))
		ThrowError("Missing argument for option '" + option + "' in `" + statement + "` (base, gain)", this->countLines, this->fileName);
	map.base = StrToFloat(value, statement, this->countLines, this->fileName);
	if (!(ss >> value))
		ThrowError("Missing argument for option '" + option + "' in `" + statement + "` (base, gain)", this->countLines, this->fileName);
	map.gain = StrToFloat(value, statement, this->countLines, this->fileName);
}

void	MtlParser::ParseOST(std::istringstream& ss, vec3& vec, std::string& option, std::string& statement)
{
	std::string value;
	if (!(ss >> value))
		ThrowError("Missing argument for option '" + option + "' in `" + statement + "` (u, [v, w])", this->countLines, this->fileName);
	vec.x = StrToFloat(value, statement, this->countLines, this->fileName);
	if (!ss.eof() && ss >> value)
		vec.y = StrToFloat(value, statement, this->countLines, this->fileName);
	if (!ss.eof() && ss >> value)
		vec.z = StrToFloat(value, statement, this->countLines, this->fileName);
}

void	MtlParser::SetResolution(std::istringstream& ss, TextureMap& map, std::string& option, std::string& statement)
{
	std::string value;
	if (!(ss >> value))
		ThrowError("Missing argument for option '" + option + "' in `" + statement + "` (resolution)", this->countLines, this->fileName);
	map.resolution = StrToInt(value, statement, this->countLines, this->fileName);
}

void	MtlParser::ParseMapOptions(std::string& option, std::istringstream& ss, TextureMap& map, std::string& statement)
{
	if (option == "-blendu")
		map.blendu = this->ParseOnOff(ss, option, statement);
	else if (option == "-blendv")
		map.blendv = this->ParseOnOff(ss, option, statement);
	else if (option == "-bm")
		this->SetBumpMultiplier(ss, map, option, statement);
	else if (option == "-boost")
		this->SetBoost(ss, map, option, statement);
	else if (option == "-cc")
		map.cc = this->ParseOnOff(ss, option, statement);
	else if (option == "-clamp")
		map.clamp = this->ParseOnOff(ss, option, statement);
	else if (option == "-imfchan")
		this->SetImageChan(ss, map, option, statement);
	else if (option == "-mm")
		this->SetMapModifiers(ss, map, option, statement);
	else if (option == "-o")
		this->ParseOST(ss, map.offset, option, statement);
	else if (option == "-s")
		this->ParseOST(ss, map.scale, option, statement);
	else if (option == "-t")
		this->ParseOST(ss, map.turbulence, option, statement);
	else if (option == "-texres")
		this->SetResolution(ss, map, option, statement);
	else
		ThrowError("Option not recognized in `" + statement + "`", option, this->countLines, this->fileName);
}
