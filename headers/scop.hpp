#ifndef SCOP_HPP
# define SCOP_HPP

# include <cstdio>
# include <chrono>
# include "openGL/openGL.hpp"
# include "ObjParser.hpp"
# include "vec2.hpp"
# include "vec3.hpp"
# include "vec4.hpp"
# include "mat4.hpp"

enum render_type {
	COLORED,
	SMOOTH,
	IMAGE
};

extern u8 renderType;

int		parseFile(std::string_view fileName, ObjParser& objParser);
void	loadScene(ObjParser& objParser, openGL& openGL);
void	setup(openGL& openGL);
void	loop(openGL& openGL);

void	processInput(openGL& openGL);

#endif // !SCOP_HPP