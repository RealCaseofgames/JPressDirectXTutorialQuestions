#pragma once
#include <DirectXMath.h>

using namespace DirectX;

struct Vertex {
	Vertex() {}
	Vertex(float x, float y) :
		pos(x, y) {}

	XMFLOAT2 pos;
};