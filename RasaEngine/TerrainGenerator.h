#pragma once
#include <GL/glew.h>

class TerrainGenerator
{
public:
	static const int GEOMETRY_RES = 15, LOD_LEVELS=4;
	TerrainGenerator();
	void CreateBlock();
	~TerrainGenerator();
private:
	int blockSize;
	GLuint VAO,EBO, blockBuffer, trimBuffer, gapBuffer;
};

