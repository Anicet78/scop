#ifndef SCOP_HPP
# define SCOP_HPP

# include <cstdio>
# include <unordered_map>
# include <algorithm>
# include "openGL/openGL.hpp"
# include "ObjParser.hpp"
# include "vec2.hpp"
# include "vec3.hpp"
# include "vec4.hpp"
# include "mat4.hpp"
# include "Chrono.hpp"

enum render_type {
	COLORED,
	SMOOTH,
	IMAGE
};

extern Chrono	chrono;
extern u8		renderType;
extern float	coloredOpacity;
extern float	smoothOpacity;
extern float	imgOpacity;
extern mat4		modelToPivot;
extern mat4		modelFromPivot;
extern float	rotationSpeed;
extern i8		rotationDirection;

struct Vertex {
	vec3	pos;
	vec3	normal;
	// vec2	uv;
};

struct FaceElementHash {
	size_t operator()(const FaceElement& k) const {
		return std::hash<int>()(k.vIndex) ^ std::hash<int>()(k.vtIndex) << 16 ^ std::hash<int>()(k.vnIndex) << 24;
	}
};

int		parseFile(std::string_view fileName, ObjParser& objParser);
void	loadScene(ObjParser& objParser, openGL& openGL);
void	setup(openGL& openGL, ObjParser& objParser);
void	loop(openGL& openGL);

void	processInput(openGL& openGL);

#endif // !SCOP_HPP