project("VoxelEngineLibary")

set(${PROJECT_NAME}_headers
    std_includes.h
    dll_main.h
	UE5_Interface.h
    IVoxelBuilder.h
    ChunkProcessor.h
    AsyncChunkProcessor.h
)

set(${PROJECT_NAME}_sources
    dll_main.cpp
    IVoxelBuilder.cpp
	UE5_Interface.cpp
    ChunkProcessor.cpp
    AsyncChunkProcessor.cpp
)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources})

target_link_libraries(${PROJECT_NAME} Compute_Interface)
target_link_libraries(${PROJECT_NAME} Compute_DirectX)
target_link_libraries(${PROJECT_NAME} Compute_Vulkan)
target_link_libraries(${PROJECT_NAME} Compute_CUDA)
target_link_libraries(${PROJECT_NAME} Compute_OCL_SDK)
target_link_libraries(${PROJECT_NAME} Compute_OCL)
target_link_libraries(${PROJECT_NAME} utils)
target_link_libraries(${PROJECT_NAME} libDynamicCompute)
target_link_libraries(${PROJECT_NAME} DynamicComputeLibrary)

target_link_libraries(${PROJECT_NAME} LibVoxelEngine_private)

target_link_libraries(${PROJECT_NAME} glfw3 Vulkan-1 OpenCL-SDK OpenCLUtils OpenCLUtilsCpp)
