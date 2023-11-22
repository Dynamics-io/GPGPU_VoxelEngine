#include "../libnoise/libnoise.inc"


struct Settings{
    int ChunkSizeX;
    int ChunkSizeY;
    int ChunkSizeZ;

    float VoxelsPerMeter;
    int quality;
    int seed;
    bool enableCaves;
    float amp;
    float caveDensity;
    float grassOffset;
};

float sphere_sample(float radius, vec3 center, float x, float y, float z){

    return radius - sqrt(pow(x - center.x, 2) + pow(y - center.y, 2) + pow(z - center.z, 2));
}

float TerrainSample(Settings s, float x, float y)
{
    Module perlin_mountains = GetModule(x, 0, y);
    perlin_mountains.m_seed = s.seed;
    perlin_mountains.m_frequency = 0.5;
    perlin_mountains.m_noiseQuality = s.quality;

    Module mountains = GetModule(x, 0, y);
    mountains.m_seed = s.seed;
    mountains.m_frequency = 0.5;
    mountains.m_lacunarity = 2;
    mountains.m_noiseQuality = s.quality;

    perlin_mountains = Perlin_GetValue(perlin_mountains);

    float blendMountains = perlin_mountains.Value;// +mountains.Value;

    return blendMountains;
}

float GetHeight(Settings s, float x, float y)
{
   return TerrainSample(s, (x * (0.003)), (y * (0.003))) * 10 + 16;
}


float Sample_2D(Settings s, float x, float z)
{
    return GetHeight(s, x, z);
}

float Sample_3D(Settings s, float x, float y, float z)
{
    float radius = 10;
    vec3 sphere_center = vec3(16, 16, 16);
    float val = sphere_sample(radius, sphere_center, x, y, z);
    return val;
}

