#pragma once
#include "ConstantBuffer.h"

class ObjectResource {
public:
	ObjectResource() {};
	virtual ~ObjectResource(){};
	virtual void Draw(const ConstantBuffer& transform) = 0;

private:
	

};
