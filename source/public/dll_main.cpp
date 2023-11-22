#include "dll_main.h"

using namespace VoxelEngine;

EXPORTED void* IVoxelBuilder_New(int size_x, int size_y, int size_z, int workGroups, int batchesPerGroup, int numBatchGroups)
{
    ChunkSettings settings;

	settings.GetSettings()->setString("programDir", "C:/Users/Jon/Source/cpp_libs/VoxelEngine/shaders/Vulkan/voxel");
	settings.GetSettings()->setFloat("voxelsPerMeter", 1);
	settings.GetSettings()->setInt("chunkMeterSizeX", size_x);
	settings.GetSettings()->setInt("chunkMeterSizeY", size_y);
	settings.GetSettings()->setInt("chunkMeterSizeZ", size_z);
	settings.GetSettings()->setInt("WorkGroups", workGroups);

	settings.GetSettings()->setInt("TotalBatchGroups", numBatchGroups);
	settings.GetSettings()->setInt("BatchesPerGroup", batchesPerGroup);

	IVoxelBuilder* builder = new SmoothVoxelBuilder();

	builder->Init(settings);

	return builder;

}

EXPORTED void IVoxelBuilder_Init(void* handle)
{
}

EXPORTED void IVoxelBuilder_Generate(void* handle, glm::ivec3* locations, int numBatches)
{
	IVoxelBuilder* builder = (IVoxelBuilder*)handle;
	ChunkGenerationOptions gen_options;

	for (int i = 0; i < numBatches; i++)
		gen_options.locations.push_back(locations[i]);

	builder->Generate(gen_options);
}



EXPORTED void IVoxelBuilder_Render(void* handle, glm::ivec3* locations, int numBatches, glm::dvec4* times)
{
	IVoxelBuilder* builder = (IVoxelBuilder*)handle;
	ChunkRenderOptions options;

	for (int i = 0; i < numBatches; i++)
		options.locations.push_back(locations[i]);

	*times = builder->Render(options);
}

EXPORTED void IVoxelBuilder_GetSize(void* handle, Out_Poly_Counts* counts)
{
	IVoxelBuilder* builder = (IVoxelBuilder*)handle;

	std::vector<glm::ivec4> cts = builder->GetSize();

	for (int i = 0; i < cts.size(); i++) {
		//printf("IVoxelBuilder_GetSize %i, %i");
		counts[i].Vertex_Count = cts[i].x;
		counts[i].BatchNum = cts[i].z;
	}
}

EXPORTED void IVoxelBuilder_Extract(void* handle, int batchNum, Out_MeshData* out_data)
{
	IVoxelBuilder* builder = (IVoxelBuilder*)handle;

	builder->Extract((glm::vec4*)out_data->outVert, (glm::vec4*)out_data->outNorm, (int*)out_data->outTris, glm::ivec4(out_data->numVert, 0, batchNum, 0));

}

EXPORTED void IVoxelBuilder_Dispose(void* handle)
{
	IVoxelBuilder* builder = (IVoxelBuilder*)handle;

	builder->Dispose();
}




