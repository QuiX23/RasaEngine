#pragma once
#include "OGLRenderer.h"
#include "OGLVertexArray.h"
#include <memory>

class Context
{
public:
	//Singleton pattern methods
	static Context& getInstance();
	Context(Context const&) = delete;
	void operator=(Context const&) = delete;
	~Context();
	
	unique_ptr < IRenderer > renderer;
	shared_ptr<IVertexArray> CreateVertexArray(const vector<Vertex> & vertices, const vector<int> & indices);
	void createOGLContext();

private:
	Context(){};

};