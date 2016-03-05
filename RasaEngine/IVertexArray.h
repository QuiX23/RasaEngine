#pragma once
#include "Vertex.h"

class IVertexArray
{
public:


	virtual void setVertexArray(const vector<Vertex> & vertices, const vector<int> & indices) = 0;
};