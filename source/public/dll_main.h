#pragma once

#include "./std_includes.h"
#include "IVoxelBuilder.h"
#include "SmoothVoxelBuilder.h"
#include "C_Variables.h"

struct Out_Poly_Counts {
	int Vertex_Count;
	int BatchNum;
};

struct Out_MeshData {
	void* outVert;
	void* outNorm;
	void* outTris;
	int numVert;
	int numTris;
};

EXPORTED void* IVoxelBuilder_New(int size_x, int size_y, int size_z, int workGroups, int batchesPerGroup, int numBatchGroups);

EXPORTED void IVoxelBuilder_Init(void* handle);

EXPORTED void IVoxelBuilder_Generate(void* handle, glm::ivec3* locations, int numBatches);

EXPORTED void IVoxelBuilder_Render(void* handle, glm::ivec3* locations, int numBatches, glm::dvec4* times);

EXPORTED void IVoxelBuilder_GetSize(void* handle, Out_Poly_Counts* counts);

EXPORTED void IVoxelBuilder_Extract(void* handle, int batchNum, Out_MeshData* data);

EXPORTED void IVoxelBuilder_Dispose(void* handle);