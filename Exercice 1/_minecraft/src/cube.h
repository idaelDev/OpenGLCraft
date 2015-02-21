#pragma once

#include <stdio.h>
#include "../base/Primitive.h"

enum NYCubeType
{
	CUBE_HERBE,
	CUBE_EAU,
	CUBE_TERRE,
	CUBE_AIR,
	CUBE_BOIS,
	CUBE_FEUILLE
};

class NYCube
{
	public :
		bool _Draw;
		NYCubeType _Type;
		static const int CUBE_SIZE = 10;

		NYCube()
		{
			_Draw = true;
			_Type = CUBE_AIR;
		}

		bool isSolid(void)
		{
			return (_Type != CUBE_AIR);
		}

		void saveToFile(FILE * fs)
		{
			fputc(_Draw ? 1 : 0,fs);
			fputc(_Type,fs);
		}

		void loadFromFile(FILE * fe)
		{
			_Draw = fgetc(fe) ? true : false;
			_Type = (NYCubeType)fgetc(fe);
		}

		static NYVert3Df makeMaterial(enum NYCubeType type)
		{
			NYVert3Df col(0, 0, 0);
			switch (type)
			{
			case CUBE_HERBE:
				col.X = (float)11 / 255;
				col.Y = (float)119 / 255;
				col.Z = (float)22 / 255;
				break;
			case CUBE_EAU:
				col.X = 0;
				col.Y = 0;
				col.Z = (float)255 / 255;
				break;
			case CUBE_TERRE:
				col.X = (float)117 / 255;
				col.Y = (float)80 / 255;
				col.Z = (float)17 / 255;
				break;
			case CUBE_AIR:
				col.X = 1;
				col.Y = 1;
				col.Z = 1;
				break;
			default:
				break;
			}
			Primitive::makeMat(col.X, col.Y, col.Z);
			return col;
		}
};