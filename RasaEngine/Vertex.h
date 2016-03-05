#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <bitset>

using namespace std;

struct Vertex {
	//Every bit of this byte means how many attribuites vector haves
	//x000000 being the Position, 0x000000 being Normal and so on.
	bitset<3> type;
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};