#pragma once
#include "OGLRenderer.h"
#include "OGLVertexArray.h"
#include <memory>

class Context
{
public:
	//Singleton pattern methods
	static Context& getInstance();
	void operator=(Context const&) = delete;
	Context(Context const&) = delete;
	~Context();

	void setOGLContext();
	unique_ptr < IRenderer > renderer;
	shared_ptr<IVertexArray> CreateVertexArray(const vector<Vertex> & vertices, const vector<int> & indices) const;

private:
	Context(){};

};