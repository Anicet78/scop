#include "ObjParser.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Invalid amount of parameters" << std::endl;
		return (1);
	}

	ObjParser	objParser;
	try {
		objParser.ParseFile(av[1]);
	}
	catch (std::exception& e) {
		std::cerr << COLOR_LIGHT_RED << e.what() << COLOR_NC << std::endl;
	}

	return (0);
}
