#include "scop.hpp"

int	main(int ac, char **av)
{
	if (ac != 2) {
		std::cout << "Invalid amount of parameters" << std::endl;
		return (1);
	}

	ObjParser objParser;
	if (!parseFile(av[1], objParser))
		return (1);

	openGL openGL;
	if (!openGL.Init("scop"))
		return (1);

	loadScene(objParser, openGL);

	openGL.Loop(&loop);

	return (0);
}
