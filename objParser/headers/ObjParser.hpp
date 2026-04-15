#ifndef OBJ_PARSER_HPP
# define OBJ_PARSER_HPP

# include <algorithm>
# include <variant>
# include "parser.hpp"
# include "Elements.hpp"
# include "MtlParser.hpp"

using parser::Face;
using parser::FaceElement;
using parser::GetIndex;
using parser::Line;
using parser::LineElement;
using parser::Material;
using parser::MaterialList;
using parser::MtlParser;
using parser::Normal;
using parser::ParamSpaceVertex;
using parser::Point;
using parser::StrToInt;
using parser::ThrowError;
using parser::UV;

// Raw Object File
struct OBJRaw {
	std::vector<parser::Vertex>				vertices;
	std::vector<parser::UV>					uvs;
	std::vector<parser::Normal>				normals;
	std::vector<parser::ParamSpaceVertex>	paramSpaceVertices;
	std::vector<parser::Face>				faces;
	std::vector<parser::Line>				lines;
	std::vector<parser::Point>				points;
};

// Groups
struct Group {
	std::vector<uint32_t>	faceIndices;
	std::vector<uint32_t>	lineIndices;
	std::vector<uint32_t>	pointIndices;
};

struct SmoothingGroup {
	std::vector<uint32_t>	faceIndices;
};

struct MergingGroup {
	int		id;
	float	resolution;
};

using GroupList = std::unordered_map<std::string, Group>;
struct Object {
	GroupList			groups;
	std::vector<Group*>	activeGroups;
};

using SmoothingGroupList	= std::unordered_map<uint32_t, SmoothingGroup>;
using ObjectList			= std::unordered_map<std::string, Object>;

// Main class
class ObjParser {

	private:
		std::string	fileName;
		size_t		countLines;

		std::string	currentMaterial;

		void	AddMaterialList(std::istringstream& ss);
		void	SetMaterial(std::istringstream& ss);

		Object*	currentObject;
		int		currentSmoothingGroup;
		int		currentMergingGroup;
		float	currentMergingResolution;

		void	SetObject(std::istringstream& ss);
		void	SetGroups(std::istringstream& ss);
		void	SetSmoothingGroup(std::istringstream& ss);
		void	SetMergingGroup(std::istringstream& ss);
		void	AddToGroups(std::string& prefix);

		parser::Vertex				NewVertex(std::istringstream& ss);
		parser::UV					NewUV(std::istringstream& ss);
		parser::Normal				NewNormal(std::istringstream& ss);
		parser::ParamSpaceVertex	NewParamSpaceVertex(std::istringstream& ss);
		parser::Face				NewFace(std::istringstream& ss);
		parser::Line				NewLine(std::istringstream& ss);
		parser::Point				NewPoint(std::istringstream& ss);

		void	FillRaw(std::ifstream& ifs);

	public:
		OBJRaw				raw;
		ObjectList			objects;
		SmoothingGroupList	smoothingGroups;
		parser::MaterialList		materials;

		ObjParser(void);
		void	ParseFile(std::string filename);
		void	Print(void) const;

};

#endif // !OBJ_PARSER_HPP
