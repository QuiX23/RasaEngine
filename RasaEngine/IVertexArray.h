#pragma once
#include "Vertex.h"

class IVertexArray
{
public:
	unsigned int VAO;
	int indiciesNum;

	virtual void setVertexArray(const vector<Vertex> & vertices, const vector<int> & indices) = 0;
};