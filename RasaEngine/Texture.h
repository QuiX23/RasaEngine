#pragma once

#include "ITextureBuffer.h"
#include <memory>
#include <string>

enum TextureType
{
	TextureType_NONE = 0x0, TextureType_DIFFUSE = 0x1, TextureType_SPECULAR = 0x2, TextureType_AMBIENT = 0x3,
	TextureType_EMISSIVE = 0x4, TextureType_HEIGHT = 0x5, TextureType_NORMALS = 0x6, TextureType_SHININESS = 0x7,
	TextureType_OPACITY = 0x8, TextureType_DISPLACEMENT = 0x9, TextureType_LIGHTMAP = 0xA, TextureType_REFLECTION = 0xB,
	TextureType_UNKNOWN = 0xC, TextureType_BUFFERDEPTH = 0xD
};

enum TextureBlendOperation
{
	/** T = T1 * T2 */
	TextureBlendOperation_MUL = 0x0,
	/** T = T1 + T2 */
	TextureBlendOperation_ADD = 0x1,
	/** T = T1 - T2 */
	TextureBlendOperation_SUB = 0x2,
	/** T = T1 / T2 */
	TextureBlendOperation_DIV = 0x3,
	/** T = (T1 + T2) - (T1 * T2) */
	TextureBlendOperation_SMOOTH_ADD = 0x4,
	/** T = T1 + (T2-0.5) */
	TextureBlendOperation_SIGNED_ADD = 0x5
};

struct Texture {
	int width, height;
	TextureType type;
	std::shared_ptr<ITextureBuffer> texturBuffer;
	std::string path;


	//Defines blend strength and blend operation with other textures
	float blend;
	TextureBlendOperation op;

	Texture(int width, int height, TextureType type, std::string path, const unsigned char* const texture,  float blend, TextureBlendOperation op);
};

