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
		vertices.push_back(vec3(vertex));
	}

	for (Face face: objParser.raw.faces) {
		if (face.elements.size() < 3)
			continue;

		for (std::size_t i = 1; i + 1 < face.elements.size(); ++i) {
			indices.push_back(face.elements[0].vIndex - 1);
			indices.push_back(face.elements[i].vIndex - 1);
			indices.push_back(face.elements[i + 1].vIndex - 1);
		}
	}

	const std::vector<VertexAttribDesc> attributes = {
		makeAttrib<vec3>(0, 3, GL_FLOAT, offsetof(vec3, x))
	};

	openGL.LoadScene(
		vertices.data(),
		vertices.size() * sizeof(vec3),
		indices.data(),
		indices.size() * sizeof(u32),
		attributes,
		GL_STATIC_DRAW
	);
}