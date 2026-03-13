#include "ObjParser.hpp"

ObjParser::ObjParser(void)
{
	this->countLines = 0;
	this->currentObject = &this->objects["default"];
	this->currentObject->activeGroups.emplace_back(&this->currentObject->groups["default"]);
	this->currentSmoothingGroup = 0;
	this->currentMergingGroup = -1;
	this->currentMergingResolution = 0;

	this->materials[""] = Material::WhiteMaterial();
}

void	ObjParser::AddMaterialList(std::istringstream& ss)
{
	std::string mtlFileName;
	while (ss >> mtlFileName)
	{
		MaterialList newMaterialList = MtlParser::ImportMtl(mtlFileName);
		for (const auto& [newKey, newValue] : newMaterialList) {
			this->materials[newKey] = newValue;
		}
	}

	if (this->materials.size() == 0)
		ThrowError("Not enough arguments in `mtllib` ('mtlFileName', [...])", this->fileName);
}

void	ObjParser::SetMaterial(std::istringstream& ss)
{
	if (!(ss >> this->currentMaterial))
		this->currentMaterial = "";

	if (!this->materials.contains(this->currentMaterial))
		ThrowError("This material doesn't exist in `usemtl`", this->currentMaterial, this->countLines, this->fileName);

	else if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many materials given in `usemtl`, only one material can be set at a time", ss, this->countLines, this-> fileName);
}

void	ObjParser::FillRaw(std::ifstream& ifs)
{
	std::string	line;

	while (std::getline(ifs, line)) {
		this->countLines++;

		std::istringstream ss(line);
		std::string prefix;
		if (!(ss >> prefix))
			continue;

		if (prefix == "v")
			this->raw.vertices.emplace_back(NewVertex(ss));
		else if (prefix == "vt")
			this->raw.uvs.emplace_back(NewUV(ss));
		else if (prefix == "vn")
			this->raw.normals.emplace_back(NewNormal(ss));
		else if (prefix == "vp")
			this->raw.paramSpaceVertices.emplace_back(NewParamSpaceVertex(ss));
		else if (prefix == "f")
			this->raw.faces.emplace_back(NewFace(ss));
		else if (prefix == "l")
			this->raw.lines.emplace_back(NewLine(ss));
		else if (prefix == "p")
			this->raw.points.emplace_back(NewPoint(ss));
		else if (prefix == "mtllib")
			this->AddMaterialList(ss);
		else if (prefix == "usemtl")
			this->SetMaterial(ss);
		else if (prefix == "o")
			this->SetObject(ss);
		else if (prefix == "g")
			this->SetGroups(ss);
		else if (prefix == "s")
			this->SetSmoothingGroup(ss);
		else if (prefix == "mg")
			this->SetMergingGroup(ss);
		else if (prefix == "#")
			continue;
		else // May skip instead later
			ThrowError("Element not recognized", prefix, this->countLines, this->fileName);
		this->AddToGroups(prefix);
	}
}

void	ObjParser::ParseFile(std::string filename)
{
	std::ifstream ifs(filename);
	if (!ifs.is_open())
		ThrowError("Could not open file `" + filename + "`: " + std::strerror(ifs.rdstate()));
	this->fileName = filename;

	this->FillRaw(ifs);

	ifs.close();
	this->Print();
}

void	ObjParser::Print(void) const
{
	std::cout << "File name: " << this->fileName << std::endl;

	// Vertex
	std::cout << "Vertices:" << std::endl;
	for (std::size_t i = 0; i < this->raw.vertices.size(); ++i) {
		std::cout << "index: " << i << ", valeur: " << this->raw.vertices[i] << std::endl;
	}

	// UV
	std::cout << "UVS:" << std::endl;
	for (std::size_t i = 0; i < this->raw.uvs.size(); ++i) {
		std::cout << "index: " << i << ", valeur: " << this->raw.uvs[i] << std::endl;
	}

	// Normal
	std::cout << "Normals:" << std::endl;
	for (std::size_t i = 0; i < this->raw.normals.size(); ++i) {
		std::cout << "index: " << i << ", valeur: " << this->raw.normals[i] << std::endl;
	}

	// ParamSpaceVertices
	std::cout << "ParamSpaceVertices:" << std::endl;
	for (std::size_t i = 0; i < this->raw.paramSpaceVertices.size(); ++i) {
		std::cout << "index: " << i << ", valeur: " << this->raw.paramSpaceVertices[i] << std::endl;
	}

	// Faces
	std::cout << "Face:" << std::endl;
	for (std::size_t i = 0; i < this->raw.faces.size(); ++i) {
		std::cout << "index: " << i << ", valeur: " << this->raw.faces[i] << std::endl;
	}

	// Lines
	std::cout << "Lines:" << std::endl;
	for (std::size_t i = 0; i < this->raw.lines.size(); ++i) {
		std::cout << "index: " << i << ", valeur: " << this->raw.lines[i] << std::endl;
	}

	// Points
	std::cout << "Points:" << std::endl;
	for (std::size_t i = 0; i < this->raw.points.size(); ++i) {
		std::cout << "index: " << i << ", valeur: " << this->raw.points[i] << std::endl;
	}

	// Materials
	std::cout << "Materials: " << std::endl;
	for (const auto& [key, value] : this->materials) {
		std::cout << key << ":" << std::endl;
		value.Print();
	}
}