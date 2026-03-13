#ifndef ELEMENTS_HPP
# define ELEMENTS_HPP

# include <vector>
# include "vec3.hpp"
# include "vec4.hpp"

typedef vec4 Vertex;
typedef vec3 UV;
typedef vec3 Normal;
typedef vec3 ParamSpaceVertex;

struct FaceElement {
	uint32_t	vIndex;
	uint32_t	vtIndex;
	uint32_t	vnIndex;

	FaceElement(uint32_t v, uint32_t vt, uint32_t vn) {
		this->vIndex = v; this->vtIndex = vt; this->vnIndex = vn;
	}

	friend std::ostream&	operator<<(std::ostream &stream, const FaceElement& faceElem)
	{
		stream << faceElem.vIndex << ", ";
		stream << faceElem.vtIndex << ", ";
		stream << faceElem.vnIndex;
		return (stream);
	}
};

struct Face {
	std::vector<FaceElement>	elements;
	std::string					materialName;
	int							smoothingGroupIndex;

	friend std::ostream&	operator<<(std::ostream &stream, const Face& face)
	{
		std::cout << "FaceElements: " << std::endl;
		for (std::size_t i = 0; i < face.elements.size(); ++i) {
			std::cout << "index: " << i << ", valeur: " << face.elements[i] << std::endl;
		}
		std::cout << "Material name: " << face.materialName << std::endl;
		std::cout << "SmoothingGroup index: " << face.smoothingGroupIndex << std::endl;
		return (stream);
	}
};

struct LineElement {
	uint32_t	vIndex;
	uint32_t	vtIndex;

	LineElement(uint32_t v, uint32_t vt) {
		this->vIndex = v; this->vtIndex = vt;
	}

	friend std::ostream&	operator<<(std::ostream &stream, const LineElement& lineElem)
	{
		stream << lineElem.vIndex;
		stream << lineElem.vtIndex;
		return (stream);
	}
};

struct Line {
	std::vector<LineElement> elements;
	friend std::ostream&	operator<<(std::ostream &stream, const Line& line)
	{
		std::cout << "LineElements: " << std::endl;
		for (std::size_t i = 0; i < line.elements.size(); ++i) {
			std::cout << "index: " << i << ", valeur: " << line.elements[i] << std::endl;
		}
		return (stream);
	}
};

struct Point {
	std::vector<uint32_t> vertices;
	friend std::ostream&	operator<<(std::ostream &stream, const Point& point)
	{
		std::cout << "PointElements: " << std::endl;
		for (std::size_t i = 0; i < point.vertices.size(); ++i) {
			std::cout << "index: " << i << ", valeur: " << point.vertices[i] << std::endl;
		}
		return (stream);
	}
};

template <typename T>
uint32_t	GetIndex(std::vector<T>& vector, int index)
{
	if (index < 0)
	{
		if (static_cast<int>(vector.size()) < -index)
			return (0);
		return (vector.size() - (-index - 1));
	}
	return (static_cast<int>(vector.size()) < index ? 0 : index);
}

#endif // !ELEMENTS_HPP
