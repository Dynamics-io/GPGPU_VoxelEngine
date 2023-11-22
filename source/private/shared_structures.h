#pragma once

#include <cstdio>
#include <memory>
#include <mutex>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <utility>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <array>
#include <unordered_map>
#include <optional>
#include <set>
#include <algorithm>
#include <iomanip>

#include <glm/glm.hpp>
#include <glm/vec4.hpp>

struct Block {

};

struct MeshData {
	glm::vec4* Vertex;
	glm::vec4* Normal;
	int* Triangles;

	int NumVertex;
	int NumTriangles;
};

struct Vector3Int {
	int X;
	int Y;
	int Z;

	Vector3Int(int x, int y, int z) {
		X = x;
		Y = y;
		Z = z;
	}
};

struct Settings {
public:

	void setFloat(std::string name, float val) {
		m_float_settings[name] = val;
	}

	void setInt(std::string name, int val) {
		m_int_settings[name] = val;
	}

	void setString(std::string name, std::string val) {
		m_string_settings[name] = val;
	}


	float getFloat(std::string name) {
		return m_float_settings[name];
	}

	int getInt(std::string name) {
		return m_int_settings[name];
	}

	std::string getString(std::string name) {
		return m_string_settings[name];
	}

private:
	std::map<std::string, float> m_float_settings;
	std::map<std::string, int> m_int_settings;
	std::map<std::string, std::string> m_string_settings;
};

struct ChunkSettings {
public:

	Settings* GetSettings() {
		return &m_settings;
	}

	ChunkSettings() {
		m_settings.setInt("WorkGroups", 16);
		m_settings.setInt("TotalBatchGroups", 1);
		m_settings.setInt("BatchesPerGroup", 1);

		m_settings.setInt("chunkMeterSizeX", 32);
		m_settings.setInt("chunkMeterSizeY", 32);
		m_settings.setInt("chunkMeterSizeZ", 32);
		m_settings.setInt("voxelsPerMeter", 1);
	}

private:
	Settings m_settings;
};

struct ChunkGenerationOptions {
	std::vector<glm::ivec3> locations;
	/*int X;
	int Y;
	int Z;*/


	Settings GetSettings() {
		return m_settings;
	}

	ChunkGenerationOptions() {
		//X = 0;
		//Y = 0;
		//Z = 0;
		
	}

private:
	Settings m_settings;
};

struct ChunkRenderOptions {
	std::vector<glm::ivec3> locations;
	/*int X;
	int Y;
	int Z;*/


	Settings GetSettings() {
		return m_settings;
	}

private:
	Settings m_settings;
};