C:/VulkanSDK/1.3.268.0/Bin/glslc.exe shader.comp -o compute.spv

C:/VulkanSDK/1.3.268.0/Bin/glslc.exe heightmap.comp -o voxel/heightmap.spv
C:/VulkanSDK/1.3.268.0/Bin/glslc.exe iso_field.comp -o voxel/iso_field.spv
C:/VulkanSDK/1.3.268.0/Bin/glslc.exe material_field.comp -o voxel/material_field.spv
C:/VulkanSDK/1.3.268.0/Bin/glslc.exe unify_fields.comp -o voxel/unify_fields.spv

C:/VulkanSDK/1.3.268.0/Bin/glslc.exe smoothrender_createmesh.comp -o voxel/smoothrender_createmesh.spv
C:/VulkanSDK/1.3.268.0/Bin/glslc.exe smoothrender_createvertlist.comp -o voxel/smoothrender_createvertlist.spv

C:/VulkanSDK/1.3.268.0/Bin/glslc.exe smoothrender_construct.comp -o voxel/smoothrender_construct.spv
C:/VulkanSDK/1.3.268.0/Bin/glslc.exe smoothrender_mark.comp -o voxel/smoothrender_mark.spv
C:/VulkanSDK/1.3.268.0/Bin/glslc.exe smoothrender_stitch.comp -o voxel/smoothrender_stitch.spv
C:/VulkanSDK/1.3.268.0/Bin/glslc.exe smoothrender_stitch_async.comp -o voxel/smoothrender_stitch_async.spv

pause