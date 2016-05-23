#pragma once
#include "Vertex.h"

class IVertexArray
{
public:
	virtual ~IVertexArray(){}

	virtual void setVertexArray(const vector<Vertex> & vertices, const vector<int> & indices) = 0;
};