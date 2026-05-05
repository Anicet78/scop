#ifndef BMP_PARSER_HPP
# define BMP_PARSER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "types.hpp"

#pragma pack(push, 1)

struct BMPFileHeader {
	u16	bfType;
	u32	bfSize;
	u16	bfReserved1;
	u16	bfReserved2;
	u32	bfOffBits;
};

struct BMPInfoHeader {
	u32	biSize;
	i32	biWidth;
	i32	biHeight;
	u16	biPlanes;
	u16	biBitCount;
	u32	biCompression;
	u32	biSizeImage;
	i32	biXPelsPerMeter;
	i32	biYPelsPerMeter;
	u32	biClrUsed;
	u32	biClrImportant;
};

#pragma pack(pop)

struct BMP {

	BMPFileHeader	fileHeader;
	BMPInfoHeader	infoHeader;
	bool			failed = false;
	std::vector<u8>	data;
	size_t			height;
	size_t			width;

	BMP(std::string_view filename);
};

inline BMP::BMP(std::string_view filename) {
	std::ifstream	file(filename.data(), std::ios::binary);

	file.read(reinterpret_cast<char *>(&this->fileHeader), 14);
	file.read(reinterpret_cast<char *>(&this->infoHeader), 40);
	if (!file.is_open() || file.fail()) { failed = true; return; }

	if (fileHeader.bfType != 0x4D42 || infoHeader.biPlanes != 1 || infoHeader.biBitCount != 24) { failed = true; return; }

	file.seekg(fileHeader.bfOffBits);
	if (file.fail()) { failed = true; return; }

	size_t	width = infoHeader.biWidth;
	size_t	height = abs(infoHeader.biHeight);

	this->width = width;
	this->height = height;

	size_t	row_size = ((infoHeader.biBitCount * width + 31) / 32) * 4;
	bool	top_down = infoHeader.biHeight < 0;
	data.resize(width * height * 3);

	for (size_t y = 0; y < height; y++) {
		std::vector<char> row_data(row_size);
		file.read(row_data.data(), row_size);
		if (file.fail()) { failed = true; return; }

		size_t target_y = top_down ? (height - 1 - y) : y;

		for (size_t x = 0; x < width; x++) {
			size_t pixel_index = (target_y * width + x) * 3;
			data[pixel_index + 0] = static_cast<u8>(row_data[x * 3 + 2]);
			data[pixel_index + 1] = static_cast<u8>(row_data[x * 3 + 1]);
			data[pixel_index + 2] = static_cast<u8>(row_data[x * 3]);
		}
	}

	file.close();
}


#endif // !BMP_PARSER_HPP