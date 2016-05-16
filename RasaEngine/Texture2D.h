#pragma once
#include "Texture.h"

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

struct Texture2D : public Texture
{
	int width, height;
	//Defines blend strength and blend operation with other textures
	float blend;
	TextureBlendOperation op;

	Texture2D(int width, int height, TextureType type, std::string path, const unsigned char* const texture, float blend, TextureBlendOperation op);
};