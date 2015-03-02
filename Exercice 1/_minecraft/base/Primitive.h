#include "external/gl/glew.h"
#include "external/gl/freeglut.h"

#include "engine/utils/types_3d.h"
#include "engine/render/graph/tex_manager.h"

#pragma once
class Primitive
{
public:
	Primitive();
	static void cube(NYVert3Df position, NYVert3Df rotation, NYVert3Df scale);
	static void skybox(NYVert3Df position, NYVert3Df rotation, NYVert3Df scale, NYTexFile* texture);
	static void makeMat(float r, float g, float b);
	~Primitive();
};


