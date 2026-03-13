#include "MtlParser.hpp"

Material::Material(void)
{
	this->illuminationModel = 2;
	this->dissolve.factor = 1.0f;
	this->dissolve.halo = false;
	this->shininess = 0.0f;
	this->sharpness = 60;
	this->refractiveIndex = 1.0f;
	this->roughness = 1.0f;
	this->metallic = 0.0f;
	this->sheen = 0.0f;
	this->clearcoatThickness = 0.0f;
	this->clearcoatRoughness = 0.0f;
	this->anisotropy = 0.0f;
	this->anisotropyRotation = 0.0f;
	this->mapAAT = false;
}

Material	Material::BlackMaterial(void)
{
	Material mat;
	mat.ambient.format = ColorFormat::RGB;
	mat.ambient.rgb = vec3(0, 0, 0);
	mat.diffuse.format = ColorFormat::RGB;
	mat.diffuse.rgb = vec3(0, 0, 0);
	mat.specular.format = ColorFormat::RGB;
	mat.specular.rgb = vec3(0, 0, 0);
	mat.transmissionFilter.format = ColorFormat::RGB;
	mat.transmissionFilter.rgb = vec3(0, 0, 0);
	return (mat);
}

Material	Material::WhiteMaterial(void)
{
	Material mat;
	mat.ambient.format = ColorFormat::RGB;
	mat.ambient.rgb = vec3(1, 1, 1);
	mat.diffuse.format = ColorFormat::RGB;
	mat.diffuse.rgb = vec3(1, 1, 1);
	mat.specular.format = ColorFormat::RGB;
	mat.specular.rgb = vec3(1, 1, 1);
	mat.transmissionFilter.format = ColorFormat::RGB;
	mat.transmissionFilter.rgb = vec3(1, 1, 1);
	return (mat);
}

void	Material::Print(void) const
{
	std::cout << "Ambient: " << std::endl << this->ambient << std::endl;
	std::cout << "Diffuse: " << std::endl << this->diffuse << std::endl;
	std::cout << "Specular: " << std::endl << this->specular << std::endl;
	std::cout << "TransmissionFilter: " << std::endl << this->transmissionFilter << std::endl;
	std::cout << "Illumination model: " << this->illuminationModel << std::endl;
	std::cout << "Dissolve factor: " << this->dissolve.factor << std::endl;
	std::cout << "Dissolve halo: " << this->dissolve.halo << std::endl;
	std::cout << "Shininess: " << this->shininess << std::endl;
	std::cout << "Sharpness: " << this->sharpness << std::endl;
	std::cout << "Refractive index: " << this->refractiveIndex << std::endl;
}
