#include "scop.hpp"

int	parseFile(std::string_view fileName, ObjParser& objParser) {
	try {
		auto start = std::chrono::steady_clock::now();
		objParser.ParseFile(fileName.data());
		auto end = std::chrono::steady_clock::now();
		std::cout << "Parsing success (" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms)" << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << COLOR_LIGHT_RED << "Parsing failed\n" << e.what() << COLOR_NC << std::endl;
		return (0);
	}

	return (1);
}

void	loadScene(ObjParser& objParser, openGL& openGL) {
	std::vector<vec3> vertices;
	std::vector<u32> indices;

	for (Vertex vertex: objParser.raw.vertices) {
		vertices.push_back(vertex.normalize());
	}

	for (Face face: objParser.raw.faces) {
		for (FaceElement faceElem : face.elements)
			indices.push_back(faceElem.vIndex);
	}

	openGL.LoadScene(vertices, indices);
}

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

	openGL.Loop();

	return (0);
}
