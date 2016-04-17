#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <bitset>

using namespace std;

enum VertexFlag
{
	VertexFlag_POSITION, VertexFlag_NORMAL, VertexFlag_TEXCOORDS, VertexFlag_COLOR
};

struct Vertex {
	//Every bit of this byte means how many attribuites vector haves
	//000x being the Position, 00x0 being Normal and so on.
	bitset<4> Type;
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec4 Color;
};