#include "scop.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Invalid amount of parameters" << std::endl;
		return (1);
	}

	ObjParser	objParser;
	try {
		auto start = std::chrono::steady_clock::now();
		objParser.ParseFile(av[1]);
		auto end = std::chrono::steady_clock::now();
		std::cout << "Parsing success (" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms)" << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << COLOR_LIGHT_RED << "Parsing failed\n" << e.what() << COLOR_NC << std::endl;
		return (1);
	}

	openGL openGL;
	if (!openGL.Init("scop"))
		return (1);

	openGL.LoadScene();

	openGL.Loop();

	return (0);
}
