project("LibVoxelEngine_private")

set(${PROJECT_NAME}_headers
    stdafx.h    
    dll_main.h
    C_Variables.h
    ForwardDeclarations.h
    Logger.h
    IVoxelBuilder_private.h
    shared_structures.h
    SmoothVoxelBuilder.h
    marchingcubes_arrays.h
    VoxelComputeProgram.h
    HeightmapGenerator.h
    ChunkProcessor_private.h
)

set(${PROJECT_NAME}_sources
    dll_main.cpp
    C_Variables.cpp
    Logger.cpp
    IVoxelBuilder_private.cpp
    SmoothVoxelBuilder.cpp
    marchingcubes_arrays.cpp
    VoxelComputeProgram.cpp
    HeightmapGenerator.cpp
    ChunkProcessor_private.cpp
)

#add_subdirectory(utils)

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

target_link_libraries(${PROJECT_NAME} glfw3 Vulkan-1 OpenCL-SDK OpenCLUtils OpenCLUtilsCpp)
