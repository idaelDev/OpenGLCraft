#include "chunk.h"

float NYChunk::_WorldVert[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE*3*6*4];
float NYChunk:: _WorldCols[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE*3*6*4];
float  NYChunk::_WorldNorm[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE*3*6*4];
float  NYChunk::_WorldUV[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE *2*6*4];
	