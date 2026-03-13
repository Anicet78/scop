#include "ObjParser.hpp"

Vertex	ObjParser::NewVertex(std::istringstream& ss)
{
	float x, y, z, w = 1.0f;
	if (!(ss >> x >> y >> z))
	{
		if (ss.eof())
			ThrowError("Not enough arguments in `v` (x, y, z, [w])", this->countLines, this->fileName);
		else
			ThrowError("Invalid coordinate argument in `v`", ss, this->countLines, this->fileName);
	}
	if (!(ss >> w) && !ss.eof())
		ThrowError("Invalid scale argument in `v`", ss, this->countLines, this->fileName);
	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `v`", ss, this->countLines, this->fileName);
	return (Vertex(x, y, z, w));
}

UV	ObjParser::NewUV(std::istringstream& ss)
{
	float u, v = 0.0f, w = 0.0f;
	if (!(ss >> u))
	{
		if (ss.eof())
			ThrowError("Not enough argument in `vt` (u, [v, w])", this->countLines, this->fileName);
		else
			ThrowError("Invalid coordinate argument in `vt`", ss, this->countLines, this->fileName);
	}
	if (!(ss >> v) && !ss.eof())
		ThrowError("Invalid coordinate argument in `vt`", ss, this->countLines, this->fileName);
	if (!ss.eof() && !(ss >> w) && !ss.eof())
		ThrowError("Invalid coordinate argument in `vt`", ss, this->countLines, this->fileName);
	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `vt`", ss, this->countLines, this->fileName);
	if (u < 0 || u > 1)
		ThrowError("Invalid u coordinate in `vt`, every coordinates should be in [0,1]", this->countLines, this->fileName);
	if (v < 0 || v > 1)
		ThrowError("Invalid v coordinate in `vt`, every coordinates should be in [0,1]", this->countLines, this->fileName);
	if (w < 0 || w > 1)
		ThrowError("Invalid w coordinate in `vt`, every coordinates should be in [0,1]", this->countLines, this->fileName);
	return (UV(u, v, w));
}

Normal	ObjParser::NewNormal(std::istringstream& ss)
{
	float x, y, z;
	if (!(ss >> x >> y >> z))
	{
		if (ss.eof())
			ThrowError("Not enough arguments in `vn` (x, y, z)", this->countLines, this->fileName);
		else
			ThrowError("Invalid normal argument in `vn`", ss, this->countLines, this->fileName);
	}
	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `vt`", ss, this->countLines, this->fileName);
	return (Normal(x, y, z).normalize());
}

ParamSpaceVertex	ObjParser::NewParamSpaceVertex(std::istringstream& ss)
{
	float u, v = 0.0f, w = 0.0f;
	if (!(ss >> u))
	{
		if (ss.eof())
			ThrowError("Not enough argument in `vp` (u, [v, w])", this->countLines, this->fileName);
		else
			ThrowError("Invalid point argument in `vp`", ss, this->countLines, this->fileName);
	}
	if (!(ss >> v) && !ss.eof())
		ThrowError("Invalid point argument in `vp`", ss, this->countLines, this->fileName);
	if (!ss.eof() && !(ss >> w) && !ss.eof())
		ThrowError("Invalid point argument in `vp`", ss, this->countLines, this->fileName);
	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `vp`", ss, this->countLines, this->fileName);
	return (ParamSpaceVertex(u, v, w));
}

Face	ObjParser::NewFace(std::istringstream& ss)
{
	Face		face;
	std::string	currentFace;
	while (ss >> currentFace)
	{
		std::string part;
		std::stringstream tokenSS(currentFace);
		uint32_t v_index, vt_index = 0, vn_index = 0;
		if (std::getline(tokenSS, currentFace, '/'))
		{
			if (currentFace.empty())
				ThrowError("No vertex index defined in `f`", this->countLines, this->fileName);
			int v = StrToInt(currentFace, "f", this->countLines, this->fileName);
			if (v == 0)
				ThrowError("Vertex index must be referenced by its relative position (1-based) and thus cannot be '0' in `f`", currentFace, this->countLines, this->fileName);
			v_index = GetIndex(this->raw.vertices, v);
			if (v_index == 0)
				ThrowError("Vertex index " + currentFace + " not found in the vertices list in `f`, the vertices used must be declared before the face declaration", this->countLines, this->fileName);
		}
		if (std::getline(tokenSS, currentFace, '/') && !currentFace.empty())
		{
			int vt = StrToInt(currentFace, "f", this->countLines, this->fileName);
			if (vt == 0)
				ThrowError("Texture index must be referenced by its relative position (1-based) and thus cannot be '0' in `f`", currentFace, this->countLines, this->fileName);
			vt_index = GetIndex(this->raw.uvs, vt);
			if (vt_index == 0)
				ThrowError("Texture index " + currentFace + " not found in the uvs list in `f`, the uvs used must be declared before the face declaration", this->countLines, this->fileName);
		}
		if (std::getline(tokenSS, currentFace, '/') && !currentFace.empty())
		{
			int vn = StrToInt(currentFace, "f", this->countLines, this->fileName);
			if (vn == 0)
				ThrowError("Normal index must be referenced by its relative position (1-based) and thus cannot be '0' in `f`", currentFace, this->countLines, this->fileName);
			vn_index = GetIndex(this->raw.normals, vn);
			if (vn_index == 0)
				ThrowError("Normal index " + currentFace + " not found in the normals list in `f`, the normals used must be declared before the face declaration", this->countLines, this->fileName);
		}
		face.elements.emplace_back(FaceElement(v_index, vt_index, vn_index));
	}
	if (face.elements.size() < 3)
		ThrowError("Not enough arguments in `f`, not enough vertices given (should be at least 3)", this->countLines, this->fileName);
	face.smoothingGroupIndex = this->currentSmoothingGroup;
	face.materialName = this->currentMaterial;
	return (face);
}

Line	ObjParser::NewLine(std::istringstream& ss)
{
	Line		line;
	std::string	currentLine;
	while (ss >> currentLine)
	{
		std::string part;
		std::stringstream tokenSS(currentLine);
		uint32_t v_index, vt_index = 0;
		if (std::getline(tokenSS, currentLine, '/'))
		{
			if (currentLine.empty())
				ThrowError("No vertex index defined in `l`", this->countLines, this->fileName);
			int v = StrToInt(currentLine, "l", this->countLines, this->fileName);
			if (v == 0)
				ThrowError("Vertex index must be referenced by its relative position (1-based) and thus cannot be '0' in `l`", currentLine, this->countLines, this->fileName);
			v_index = GetIndex(this->raw.vertices, v);
			if (v_index == 0)
				ThrowError("Vertex index " + currentLine + " not found in the vertices list in `l`, the vertices used must be declared before the line declaration", this->countLines, this->fileName);
		}
		if (std::getline(tokenSS, currentLine, '/') && !currentLine.empty())
		{
			int vt = StrToInt(currentLine, "l", this->countLines, this->fileName);
			if (vt == 0)
				ThrowError("Texture index must be referenced by its relative position (1-based) and thus cannot be '0' in `l`", currentLine, this->countLines, this->fileName);
			vt_index = GetIndex(this->raw.uvs, vt);
			if (vt_index == 0)
				ThrowError("Texture index " + currentLine + " not found in the uvs list in `l`, the uvs used must be declared before the line declaration", this->countLines, this->fileName);
		}
		line.elements.emplace_back(LineElement(v_index, vt_index));
	}
	if (line.elements.size() < 1)
		ThrowError("Not enough arguments in `l`, not enough vertices given (should be at least 1)", this->countLines, this->fileName);
	return (line);
}

Point	ObjParser::NewPoint(std::istringstream& ss)
{
	Point		point;
	std::string	currentPoint;
	while (ss >> currentPoint)
	{
		uint32_t v_index;
		int v = StrToInt(currentPoint, "p", this->countLines, this->fileName);
		if (v == 0)
			ThrowError("Vertex index must be referenced by its relative position (1-based) and thus cannot be '0' in `p`", currentPoint, this->countLines, this->fileName);
		v_index = GetIndex(this->raw.vertices, v);
		if (v_index == 0)
			ThrowError("Vertex index " + currentPoint + " not found in the vertices list in `p`, the vertices used must be declared before the point declaration", this->countLines, this->fileName);
		point.vertices.emplace_back(v_index);
	}
	if (point.vertices.size() < 1)
		ThrowError("Not enough arguments in `p`, not enough vertices given (should be at least 1)", this->countLines, this->fileName);
	return (point);
}
