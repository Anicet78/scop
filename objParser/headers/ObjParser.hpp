#ifndef OBJ_PARSER_HPP
# define OBJ_PARSER_HPP

# include <algorithm>
# include <variant>
# include "parser.hpp"
# include "Elements.hpp"
# include "MtlParser.hpp"

// Raw Object File
struct OBJRaw {
	std::vector<Vertex>				vertices;
	std::vector<UV>					uvs;
	std::vector<Normal>				normals;
	std::vector<ParamSpaceVertex>	paramSpaceVertices;
	std::vector<Face>				faces;
	std::vector<Line>				lines;
	std::vector<Point>				points;
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

typedef std::unordered_map<std::string, Group>	GroupList;
struct Object {
	GroupList			groups;
	std::vector<Group*>	activeGroups;
};

typedef std::unordered_map<uint32_t, SmoothingGroup> SmoothingGroupList;
typedef std::unordered_map<std::string, Object>	ObjectList;

/* struct MeshGPU {
	std::vector<Vertex>		vertices;
	std::vector<uint32_t>	indices;
}; */

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

		Vertex				NewVertex(std::istringstream& ss);
		UV					NewUV(std::istringstream& ss);
		Normal				NewNormal(std::istringstream& ss);
		ParamSpaceVertex	NewParamSpaceVertex(std::istringstream& ss);
		Face				NewFace(std::istringstream& ss);
		Line				NewLine(std::istringstream& ss);
		Point				NewPoint(std::istringstream& ss);

		void	FillRaw(std::ifstream& ifs);

	public:
		OBJRaw				raw;
		ObjectList			objects;
		SmoothingGroupList	smoothingGroups;
		MaterialList		materials;

		ObjParser(void);
		void	ParseFile(std::string filename);
		void	Print(void) const;

};

#endif // !OBJ_PARSER_HPP
