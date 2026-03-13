#include "MtlParser.hpp"

MtlParser::MtlParser(void)
{
	this->countLines = 0;
}

void	MtlParser::NewMaterial(std::istringstream& ss)
{
	std::string materialName = "";
	if (!(ss >> materialName) || materialName == "")
		ThrowError("A name for the material must be provided in `newmtl`", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Materials can only have one name and it cannot contains blanks in `newmtl`", ss, this->countLines, this->fileName);

	this->materials[materialName];
	this->currentMaterial = materialName;
}

void	MtlParser::ParseColor(std::istringstream& ss, std::string statement, ParsedColor& color)
{
	std::string token;
	if (!(ss >> token))
		ThrowError("Not enough arguments in `" + statement + "`", this->countLines, this->fileName);

	if (token == "spectral")
	{
		color.format = ColorFormat::Spectral;
		if (!(ss >> token))
			ThrowError("Not enough arguments in `" + statement + " spectral` (file.rfl, [factor])", this->countLines, this->fileName);
		color.spectralFile = token;
		if (ss >> token)
			color.spectralFactor = StrToFloat(token, statement + " spectral", this->countLines, this->fileName);
	}
	else
	{
		float r, g, b;

		if (token == "xyz")
		{
			if (!(ss >> token))
				ThrowError("Not enough arguments in `" + statement + " xyz` (x, [y, z])", this->countLines, this->fileName);
			color.format = ColorFormat::XYZ;
		}
		else
			color.format = ColorFormat::RGB;

		r = StrToFloat(token, statement, this->countLines, this->fileName);

		ss >> token;
		if (!ss.eof())
			g = StrToFloat(token, statement, this->countLines, this->fileName);
		else
			g = r;

		if (!ss.eof() && ss >> token && !ss.eof())
			b = StrToFloat(token, statement, this->countLines, this->fileName);
		else
			b = r;

		color.rgb = vec3(r, g, b);
	}

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `" + statement + "`", ss, this->countLines, this->fileName);
}

void	MtlParser::SetIllumModel(std::istringstream& ss)
{
	int& illum = this->materials[this->currentMaterial].illuminationModel;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `illum` (number missing)", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `illum`", ss, this->countLines, this->fileName);

	illum = StrToInt(value, "illum", this->countLines, this->fileName);
	if (illum < 0 || illum > 10)
		ThrowError("Invalid value in `illum`, the number should be between 0 and 10", value, this->countLines, this->fileName);
}

void	MtlParser::SetDissolve(std::istringstream& ss, bool needInversion)
{
	Dissolve& dissolve = this->materials[this->currentMaterial].dissolve;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `d` ([-halo] factor)", this->countLines, this->fileName);

	if (value == "-halo")
	{
		dissolve.halo = true;
		if (!(ss >> value))
			ThrowError("Not enough arguments in `d` ([-halo] factor)", this->countLines, this->fileName);
	}

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `d`", ss, this->countLines, this->fileName);

	dissolve.factor = StrToFloat(value, "d", this->countLines, this->fileName);
	if (needInversion)
		dissolve.factor = 1 - dissolve.factor;
}

void	MtlParser::SetShininess(std::istringstream& ss)
{
	float& shininess = this->materials[this->currentMaterial].shininess;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `Ns` (exponent missing)", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `Ns`", ss, this->countLines, this->fileName);

	shininess = StrToFloat(value, "Ns", this->countLines, this->fileName);
}

void	MtlParser::SetSharpness(std::istringstream& ss)
{
	int& sharpness = this->materials[this->currentMaterial].sharpness;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `sharpness` (value missing)", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `sharpness`", ss, this->countLines, this->fileName);

	sharpness = StrToInt(value, "sharpness", this->countLines, this->fileName);
	if (sharpness < 0 || sharpness > 1000)
		ThrowError("Invalid value in `sharpness`, the value should be between 0 and 1000", value, this->countLines, this->fileName);
}

void	MtlParser::SetRefractiveIndex(std::istringstream& ss)
{
	float& refractiveIndex = this->materials[this->currentMaterial].refractiveIndex;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `Ni` (value missing)", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `Ni`", ss, this->countLines, this->fileName);

	refractiveIndex = StrToFloat(value, "Ni", this->countLines, this->fileName);
	if (refractiveIndex < 0.001f || refractiveIndex > 10.0f)
		ThrowError("Invalid value in `Ni`, the value should be between 0.001 and 10.0", value, this->countLines, this->fileName);
}

void	MtlParser::SetRoughness(std::istringstream& ss)
{
	float& roughness = this->materials[this->currentMaterial].roughness;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `Pr` (value missing)", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `Pr`", ss, this->countLines, this->fileName);

	roughness = StrToFloat(value, "Pr", this->countLines, this->fileName);
}

void	MtlParser::SetMetallic(std::istringstream& ss)
{
	float& metallic = this->materials[this->currentMaterial].metallic;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `Pm` (value missing)", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `Pm`", ss, this->countLines, this->fileName);

	metallic = StrToFloat(value, "Pm", this->countLines, this->fileName);
}

void	MtlParser::SetSheen(std::istringstream& ss)
{
	float& sheen = this->materials[this->currentMaterial].sheen;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `Ps` (value missing)", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `Ps`", ss, this->countLines, this->fileName);

	sheen = StrToFloat(value, "Ps", this->countLines, this->fileName);
}

void	MtlParser::SetClearcoatThickness(std::istringstream& ss)
{
	float& clearcoatThickness = this->materials[this->currentMaterial].clearcoatThickness;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `Pc` (value missing)", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `Pc`", ss, this->countLines, this->fileName);

	clearcoatThickness = StrToFloat(value, "Pc", this->countLines, this->fileName);
}

void	MtlParser::SetClearcoatRoughness(std::istringstream& ss)
{
	float& clearcoatRoughness = this->materials[this->currentMaterial].clearcoatRoughness;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `Pcr` (value missing)", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `Pcr`", ss, this->countLines, this->fileName);

	clearcoatRoughness = StrToFloat(value, "Pcr", this->countLines, this->fileName);
}

void	MtlParser::SetAnisotropy(std::istringstream& ss)
{
	float& anisotropy = this->materials[this->currentMaterial].anisotropy;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `aniso` (value missing)", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `aniso`", ss, this->countLines, this->fileName);

	anisotropy = StrToFloat(value, "aniso", this->countLines, this->fileName);
	if (anisotropy < 0.0 || anisotropy > 1.0f)
		ThrowError("Invalid value in `aniso`, the value should be between 0.0 and 1.0", value, this->countLines, this->fileName);
}

void	MtlParser::SetAnisotropyRotation(std::istringstream& ss)
{
	float& anisotropyRotation = this->materials[this->currentMaterial].anisotropyRotation;

	std::string value;
	if (!(ss >> value))
		ThrowError("Not enough arguments in `anisor` (value missing)", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `anisor`", ss, this->countLines, this->fileName);

	anisotropyRotation = StrToFloat(value, "anisor", this->countLines, this->fileName);
}

void	MtlParser::SetMap(std::istringstream& ss, TextureMap& map, std::string& statement)
{
	if (statement == "decal")
		map.imfchan = ImageChan::M;

	if (statement == "map_Tr")
		map.inverted = true;

	std::string currentArg;
	while (ss >> currentArg)
	{
		if (currentArg[0] == '-')
			ParseMapOptions(currentArg, ss, map, statement);
		else
		{
			map.filename = currentArg;
			break;
		}
	}

	if (map.filename == "")
		ThrowError("Missing argument in `" + statement + "`, map file name must be defined ([-options], filename)", this->countLines, this->fileName);

	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Only one file name can be defined in `" + statement + "`", currentArg, this->countLines, this->fileName);
}

void	MtlParser::SetMapAAT(std::istringstream& ss)
{
	std::string value;
	if (!(ss >> value))
		ThrowError("Missing argument in `map_aat` (on | off)", this->countLines, this->fileName);
	if (value == "on")
		this->materials[this->currentMaterial].mapAAT = true;
	else if (value == "off")
		this->materials[this->currentMaterial].mapAAT = false;
	else
		ThrowError("Invalid argument in `map_aat` (on | off)", this->countLines, this->fileName);
}

ReflectionMap	MtlParser::NewReflMap(std::istringstream& ss, std::string& statement)
{
	ReflectionMap	map;

	std::string value;
	if (!(ss >> value))
		ThrowError("Missing argument in `refl` (-type cube_side | sphere, [-options], filename)", this->countLines, this->fileName);

	if (value != "-type")
		ThrowError("Invalid argument in `refl`, second argument should be -type (-type cube_side | sphere, [-options], filename)", value, this->countLines, this->fileName);

	if (!(ss >> value))
		ThrowError("Missing argument in `refl` (-type cube_side | sphere, [-options], filename)", this->countLines, this->fileName);

	if (value == "sphere")
		map.type = ReflectionMapType::Sphere;
	else if (value == "cube_top")
		map.type = ReflectionMapType::CubeTop;
	else if (value == "cube_bottom")
		map.type = ReflectionMapType::CubeBottom;
	else if (value == "cube_front")
		map.type = ReflectionMapType::CubeFront;
	else if (value == "cube_back")
		map.type = ReflectionMapType::CubeBack;
	else if (value == "cube_left")
		map.type = ReflectionMapType::CubeLeft;
	else if (value == "cube_right")
		map.type = ReflectionMapType::CubeRight;
	else
		ThrowError("Invalid reflection map type argument in `refl` (-type cube_side | sphere, [-options], filename)", this->countLines, this->fileName);

	this->SetMap(ss, map, statement);
	return (map);
}

void	MtlParser::ParseFile(std::ifstream& ifs)
{
	std::string	line;

	while (std::getline(ifs, line)) {
		this->countLines++;

		std::istringstream ss(line);
		std::string prefix;
		if (!(ss >> prefix))
			continue;

		if (prefix == "newmtl")
			this->NewMaterial(ss);
		else if (prefix == "Ka")
			this->ParseColor(ss, prefix, this->materials[this->currentMaterial].ambient);
		else if (prefix == "Kd")
			this->ParseColor(ss, prefix, this->materials[this->currentMaterial].diffuse);
		else if (prefix == "Ks")
			this->ParseColor(ss, prefix, this->materials[this->currentMaterial].specular);
		else if (prefix == "Tf")
			this->ParseColor(ss, prefix, this->materials[this->currentMaterial].transmissionFilter);
		else if (prefix == "illum")
			this->SetIllumModel(ss);
		else if (prefix == "d" || prefix == "Tr")
			this->SetDissolve(ss, prefix == "Tr");
		else if (prefix == "Ns")
			this->SetShininess(ss);
		else if (prefix == "sharpness")
			this->SetSharpness(ss);
		else if (prefix == "Ni")
			this->SetRefractiveIndex(ss);
		else if (prefix == "Pr")
			this->SetRoughness(ss);
		else if (prefix == "Pm")
			this->SetMetallic(ss);
		else if (prefix == "Ps")
			this->SetSheen(ss);
		else if (prefix == "Pc")
			this->SetClearcoatThickness(ss);
		else if (prefix == "Pcr")
			this->SetClearcoatRoughness(ss);
		else if (prefix == "Ke")
			this->ParseColor(ss, prefix, this->materials[this->currentMaterial].emissive);
		else if (prefix == "aniso")
			this->SetAnisotropy(ss);
		else if (prefix == "anisor")
			this->SetAnisotropyRotation(ss);
		else if (prefix == "map_Ka")
			this->SetMap(ss, this->materials[this->currentMaterial].mapAmbient, prefix);
		else if (prefix == "map_Kd")
			this->SetMap(ss, this->materials[this->currentMaterial].mapDiffuse, prefix);
		else if (prefix == "map_Ks")
			this->SetMap(ss, this->materials[this->currentMaterial].mapSpecular, prefix);
		else if (prefix == "map_Ns")
			this->SetMap(ss, this->materials[this->currentMaterial].mapShininess, prefix);
		else if (prefix == "map_d" || prefix == "map_Tr")
			this->SetMap(ss, this->materials[this->currentMaterial].mapDissolve, prefix);
		else if (prefix == "decal")
			this->SetMap(ss, this->materials[this->currentMaterial].mapDecal, prefix);
		else if (prefix == "disp")
			this->SetMap(ss, this->materials[this->currentMaterial].mapDisp, prefix);
		else if (prefix == "bump")
			this->SetMap(ss, this->materials[this->currentMaterial].mapBump, prefix);
		else if (prefix == "map_Pr")
			this->SetMap(ss, this->materials[this->currentMaterial].mapRoughness, prefix);
		else if (prefix == "map_Pm")
			this->SetMap(ss, this->materials[this->currentMaterial].mapMetallic, prefix);
		else if (prefix == "map_Ps")
			this->SetMap(ss, this->materials[this->currentMaterial].mapSheen, prefix);
		else if (prefix == "map_Ke")
			this->SetMap(ss, this->materials[this->currentMaterial].mapEmissive, prefix);
		else if (prefix == "norm")
			this->SetMap(ss, this->materials[this->currentMaterial].mapNormal, prefix);
		else if (prefix == "map_aat")
			this->SetMapAAT(ss);
		else if (prefix == "refl")
			this->materials[currentMaterial].reflectionMaps.emplace_back(this->NewReflMap(ss, prefix));
		else if (prefix == "#")
			continue;
		else // May skip instead later
			ThrowError("Statement not recognized", prefix, this->countLines, this->fileName);
	}
}

MaterialList	MtlParser::ImportMtl(std::string filename)
{
	std::ifstream ifs(filename);
	if (!ifs.is_open())
		ThrowError("Could not open file `" + filename + "`: " + std::strerror(errno));

	MtlParser parser;
	parser.fileName = filename;
	parser.ParseFile(ifs);

	ifs.close();
	return (parser.materials);
}
