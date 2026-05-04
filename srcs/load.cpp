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

static vec3 faceNormalFromElements(const std::vector<parser::Vertex>& vertices, const Face& face)
{
	vec3 normal(0, 0, 0);
	const vec3 p0 = vec3(vertices[face.elements[0].vIndex - 1]);

	for (std::size_t i = 1; i + 1 < face.elements.size(); ++i) {
		const vec3 p1 = vec3(vertices[face.elements[i].vIndex - 1]);
		const vec3 p2 = vec3(vertices[face.elements[i + 1].vIndex - 1]);
		normal += (p1 - p0).cross(p2 - p0);
	}

	if (normal.lengthSquared() <= FT_EPSILON)
		return vec3::up();
	return normal.normalize();
}

static void resolveMissingNormals(std::vector<vec3>& normals, const std::vector<parser::Vertex>& vertices, std::vector<parser::Face>& faces) {
	for (Face& face : faces) {
		if (face.elements.size() < 3) continue;

		const bool needsNormal = face.elements[0].vnIndex == 0;
		if (!needsNormal)
			continue;

		const vec3	faceNormal = faceNormalFromElements(vertices, face);
		u32			vnFallback = 0;

		auto findNormal = std::find(normals.begin(), normals.end(), faceNormal);
		if (findNormal == normals.end()) {
			normals.push_back(faceNormal);
			vnFallback = normals.size();
		} else {
			vnFallback = std::distance(normals.begin(), findNormal) + 1;
		}

		for (FaceElement& faceElement : face.elements)
			faceElement.vnIndex = vnFallback;
	}
}

void	loadScene(ObjParser& objParser, openGL& openGL) {
	std::unordered_map<FaceElement, unsigned int, FaceElementHash> vertexMap;
	std::vector<vec3> normals;

	normals.reserve(objParser.raw.normals.size());
	for (parser::Normal& normal : objParser.raw.normals) {
		normals.push_back(normal);
	}

	auto start = std::chrono::steady_clock::now();
	resolveMissingNormals(normals, objParser.raw.vertices, objParser.raw.faces);
	auto end = std::chrono::steady_clock::now();
	std::cout << "Time to resolve missing normals: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl << std::endl;

	std::vector<Vertex> vertices;
	std::vector<u32> indices;

	for (const Face& face: objParser.raw.faces) {
		if (face.elements.size() < 3)
			continue;

		std::vector<u32> faceIndices;
		faceIndices.reserve(face.elements.size());

		for (const FaceElement& faceElement: face.elements) {
			auto it = vertexMap.find(faceElement);
			if (it != vertexMap.end()) {
				faceIndices.push_back(it->second);
			}
			else {
				Vertex v;
				v.pos		= objParser.raw.vertices[faceElement.vIndex - 1];
				v.normal	= normals[faceElement.vnIndex - 1];

				vertices.push_back(v);
				unsigned int newIdx = vertices.size() - 1;
				vertexMap[faceElement] = newIdx;
				faceIndices.push_back(newIdx);
			}
		}

		for (std::size_t i = 1; i + 1 < faceIndices.size(); ++i) {
			indices.push_back(faceIndices[0]);
			indices.push_back(faceIndices[i]);
			indices.push_back(faceIndices[i + 1]);
		}
	}

	std::vector<VertexAttribDesc> attributes = {
		makeAttrib<Vertex>(0, 3, GL_FLOAT, offsetof(Vertex, pos)),
		makeAttrib<Vertex>(1, 3, GL_FLOAT, offsetof(Vertex, normal))
	};

	openGL.LoadScene(
		vertices.data(),
		vertices.size() * sizeof(Vertex),
		indices.data(),
		indices.size() * sizeof(u32),
		attributes,
		GL_STATIC_DRAW
	);
}
