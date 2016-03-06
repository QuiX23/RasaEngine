#pragma once
#include <vector>
using namespace std;

class ITextureBuffer
{
public:
	virtual void setTextureBuffer(const unsigned char* const texture,const int & width, const int & height) = 0;
};