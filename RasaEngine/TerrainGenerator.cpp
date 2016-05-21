#include "TerrainGenerator.h"
#include <glm/detail/type_vec2.hpp>
#include <vector>


TerrainGenerator::TerrainGenerator()
{

	CreateBlock();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2),
		(GLvoid*)0);



}

void TerrainGenerator::CreateBlock()
{
	blockSize = GEOMETRY_RES + 1 / 4;

	std::vector <glm::vec2> boxMesh(blockSize*blockSize);
	
	std::vector <int> indices= std::vector <int>();
	
	
	for (auto i = 0; i < blockSize*blockSize; i++)
	{
		auto row = i / blockSize;
		auto colum = i % blockSize;
		boxMesh.push_back(glm::vec2(row, colum));

		//Lower right triangle per cell, relative to vertex
		if (row < GEOMETRY_RES - 1 && colum < GEOMETRY_RES - 1)
		{
			indices[row*colum + colum] = row*colum + colum;
			//Right one
			indices[row*colum + colum + 1];
			//Down one
			indices[(row + 1)*colum + colum];
		}

		//Upper left triangle per cell, relative to vertex
		if (row > 0 && colum > 0)
		{
			indices[row*colum + colum] = row*colum + colum;
			//Left one
			indices[row*colum + colum - 1];
			//Up one
			indices[(row - 1)*colum + colum];
		}
	}

	int lastIndice=2, currentIndice = 1;
	
	//http://www.learnopengles.com/tag/triangle-strips/
	//Connect the strip
	while (currentIndice!= blockSize*blockSize)
	{
		lastIndice = currentIndice;
		if (lastIndice>=currentIndice)
		{
			//Jump to next row
			currentIndice += blockSize;
		}
		//If we are at the right edge
		else if (lastIndice<currentIndice&& (currentIndice%blockSize) == 0)
		{
			//Jump to row beginning
			currentIndice -= (blockSize-1);
			if ((currentIndice%blockSize) == 0)
				indices.push_back(currentIndice);
		}

		indices.push_back(currentIndice);

	}




	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->blockBuffer);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->blockBuffer);
	glBufferData(GL_ARRAY_BUFFER, GEOMETRY_RES * GEOMETRY_RES* sizeof(glm::vec2),
		&boxMesh, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GEOMETRY_RES*GEOMETRY_RES * sizeof(GLuint),
		&indices[0], GL_STATIC_DRAW);

}
/*
void TerrainGenerator::DrawTerrain()
{
	
}
*/


TerrainGenerator::~TerrainGenerator()
{
}
