project("VoxelEngine_tester")

#set(${PROJECT_NAME}_headers
#)

set(${PROJECT_NAME}_sources
    exe_main.cpp
)

#add_executable(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources}

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

message(${DynamicCompute_Lib})

#find_library(
#    dynamic_comp 
#    NAME DynamicComputeLibrary 
#    PATHS ${DynamicCompute_Lib})

#if(NOT dynamic_comp)
#    message(FATAL_ERROR "DynamicCompute not found")
#endif()

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

target_link_libraries(${PROJECT_NAME} VoxelEngineLibary LibVoxelEngine_private)

#target_link_libraries(${PROJECT_NAME} DynamicComputeLibrary.dll)
#target_link_libraries(${PROJECT_NAME} VoxelEngineLib)
