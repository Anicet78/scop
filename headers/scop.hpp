#ifndef SCOP_HPP
# define SCOP_HPP

# include <cstdio>
# include <chrono>
# include "openGL.hpp"
# include "ObjParser.hpp"

int		parseFile(std::string_view fileName, ObjParser& objParser);
void	loadScene(ObjParser& objParser, openGL& openGL);
void	loop(openGL& openGL);

#endif // !SCOP_HPP