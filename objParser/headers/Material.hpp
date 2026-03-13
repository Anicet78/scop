#ifndef MATERIAL_HPP
# define MATERIAL_HPP

# include "vec3.hpp"
# include "vec4.hpp"
# include <vector>

enum class ColorFormat { RGB, XYZ, Spectral, None };

struct ParsedColor {
	ColorFormat	format;
	vec3		rgb;
	std::string	spectralFile;
	float		spectralFactor;

	ParsedColor(void) {
		this->format = ColorFormat::None, this->spectralFactor = 1.0;
	}

	friend std::ostream&	operator<<(std::ostream &stream, const ParsedColor& color)
	{
		if (color.format == ColorFormat::Spectral)
		{
			std::cout << "Format: Spectral" << std::endl;
			std::cout << "Spectral file: " << color.spectralFile << std::endl;
			std::cout << "Spectral factor: " << color.spectralFactor << std::endl;
			return (stream);
		}
		else if (color.format == ColorFormat::XYZ)
			std::cout << "Format: XYZ" << std::endl << "xyz: ";
		else
			std::cout << "Format: RGB" << std::endl << "rgb: ";
		std::cout << color.rgb << std::endl;
		return (stream);
	}
};

typedef ParsedColor Ambient;
typedef ParsedColor Diffuse;
typedef ParsedColor Specular;
typedef ParsedColor TransmissionFilter;
typedef ParsedColor Emissive;

struct Dissolve {
	float	factor;
	bool	halo;
};

enum class ImageChan { R, G, B, M, L, Z };

struct TextureMap {
	std::string	filename;
	bool		blendu = true;
	bool		blendv = true;
	bool		cc = false;
	bool		clamp = false;
	float		base = 0.0f;
	float		gain = 1.0f;
	vec3		offset = vec3(0, 0, 0);
	vec3		scale = vec3(1, 1, 1);
	vec3		turbulence = vec3(0, 0, 0);
	float		resolution = 0;
	float		bumpMultiplier = 1.0f;
	float		boost = 0.0f;
	ImageChan	imfchan = ImageChan::L;
	float		inverted = false;
};

enum class ReflectionMapType { None, Sphere, CubeTop, CubeBottom, CubeFront, CubeBack, CubeLeft, CubeRight };

struct ReflectionMap: public TextureMap {
	ReflectionMapType	type = ReflectionMapType::None;
};

struct Material {

	Material(void);
	Material(const Material& mat) = default;
	Material&	operator=(const Material& Material) = default;

	Ambient				ambient;			// Ka
	Diffuse				diffuse;			// Kd
	Specular			specular;			// Ks
	TransmissionFilter	transmissionFilter;	// Tf
	int					illuminationModel;	// illum
	Dissolve			dissolve;			// d
	float				shininess;			// Ns
	int					sharpness;			// sharpness
	float				refractiveIndex;	// Ni
	float				roughness;			// Pr
	float				metallic;			// Pm
	float				sheen;				// Ps
	float				clearcoatThickness;	// Pc
	float				clearcoatRoughness;	// Pcr
	Emissive			emissive;			// Ke
	float				anisotropy;			// aniso
	float				anisotropyRotation;	// anisor

	TextureMap	mapAmbient;		// map_Ka
	TextureMap	mapDiffuse;		// map_Kd
	TextureMap	mapSpecular;	// map_Ks
	TextureMap	mapShininess;	// map_Ns
	TextureMap	mapDissolve;	// map_d
	TextureMap	mapDecal;		// decal
	TextureMap	mapDisp;		// disp
	TextureMap	mapBump;		// bump
	TextureMap	mapRoughness;	// map_Pr
	TextureMap	mapMetallic;	// map_Pm
	TextureMap	mapSheen;		// map_Ps
	TextureMap	mapEmissive;	// map_Ke
	TextureMap	mapNormal;		// norm
	bool		mapAAT;			// map_aat

	std::vector<ReflectionMap> reflectionMaps;

	static Material	BlackMaterial(void);
	static Material	WhiteMaterial(void);

	void	Print(void) const;

};

#endif // !MATERIAL_HPP
