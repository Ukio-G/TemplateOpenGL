#ifndef VERTEX_H
#define VERTEX_H

struct alignas(sizeof(float) * 16) Vertex {
	typedef float PositionType;
	typedef float ColorType;
	typedef float UVType;

	PositionType pos[3];
	PositionType normal[3];
	UVType       textureUV[2];
	ColorType    color[3];

};


#endif