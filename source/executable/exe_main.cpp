//#include "dll_main.h"
#include "dynamic_compute.h"
#include "SmoothVoxelBuilder.h"

#include <time.h>
#include <chrono>


#define DATA_SIZE 32


using namespace DynamicCompute::Compute;
using namespace VoxelEngine;
//using namespace Dynamics_IO_Testbench::Util;

int Vulkan_test();
int OpenCL_test();
int DirectX_test();
int VoxelTest();

int test_timer() {
	// Start measuring time
	auto start = std::chrono::high_resolution_clock::now();

	// Simulate some work (e.g., a function call or a code block)
	std::this_thread::sleep_for(std::chrono::microseconds(10));  // Simulates a 100ms task

	// Stop measuring time
	auto end = std::chrono::high_resolution_clock::now();

	// Calculate the elapsed time and convert it to double representing seconds
	auto micro_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	auto second_duration = std::chrono::duration<double>(end - start).count();

	// Output the elapsed time in micro
	std::cout << "Time taken: "
		<< micro_duration.count()
		<< " microseconds" << std::endl;

	// Output the elapsed time in seconds
	std::cout << "Time taken: "
		<< second_duration
		<< " seconds" << std::endl;

	return 0;
}

float dist(glm::vec4 a, glm::vec4 b) {
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;
	return std::sqrt(dx * dx + dy * dy + dz * dz);
}

glm::ivec3 _1D_to_3D(int i, int width, int height) {
	int z = i / (width * height);
	int y = (i % (width * height)) / width;
	int x = i % width;

	return glm::ivec3(x, y, z);
}

int _3D_to_1D(int x, int y, int z, int width, int height) {
	return z* width* height + y * width + x;
}

class testClass {
public:
	testClass() {
		printf("testClass constructor.\n");
	}
	~testClass() {
		printf("testClass destructor.\n");
	}
};


int main()
{
	//test_timer();

	VoxelTest();
	//Vulkan_test();
	//DirectX_test();
	//OpenCL_test();

	return 0;
}

void testConstructor_insert(std::map<std::string, testClass>& test_map) {
	//test_map.insert("test", test_map);
}

void testConstructor() {
	std::map<std::string, testClass> test_map;
	testConstructor_insert(test_map);
}

#define TEST_SIZE 1000 * 8000

float result[TEST_SIZE];

void quadratic_tests() {
	/*
	static auto startTime = std::chrono::high_resolution_clock::now();

	float neg = 1;
	for (int i = 0; i < TEST_SIZE; i++)
	{

		result[i] = QuadraticSolvers::QuadraticArcLength(1 + (i / TEST_SIZE / 100.0f) * neg, (i / TEST_SIZE / 100.0f), (i / TEST_SIZE / 100.0f), 0, 1);
		neg = -neg;
	}

	auto currentTime = std::chrono::high_resolution_clock::now();

	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
	std::cout << "Test time: " << std::to_string(time) << "\n";


	//printf("Arc Length Integral: %f\n", arcLengh);
	*/
	return;
}

int DirectX_test() {

	//ComputeInterface::ControllerInfo test_controllerInfo;
	//ComputeInterface::GetComputeController(ComputeInterface::DIRECTX, test_controllerInfo);


	std::vector<DirectX_Device_Info> devices = ComputeInterface::GetSupportedDevices_DirectX();

	printf("DirectX Devices: %u\n", (uint32_t)devices.size());
	for (DirectX_Device_Info info : devices) {
		//DirectX_Device_Info info = dev.DirectX_Info;

		printf("\t %s (%s): %i\n", info.Name, info.GetTypeName().c_str(), info.Device_ID);
	}

	DirectX_Device_Info device = devices[0];

	ComputeInterface::ControllerInfo controllerInfo{};
	controllerInfo.device = &device;
	controllerInfo.SetProgramDir("C:/Users/jdrurka1/source/repos/Dynamics-io/Dynamics.io-Testbench/CPP_Bench/shaders/DirectX");
	IComputeController* controller = ComputeInterface::GetComputeController(ComputeInterface::DIRECTX, controllerInfo);

	std::string kernel_name = "CSMain";

	IComputeProgram::ProgramInfo p_info("Test", IComputeProgram::FileType::Binary);
	p_info.AddKernel(kernel_name);

	IComputeProgram* program = controller->AddProgram(p_info);

	program->Build();

	float Data[DATA_SIZE] = { 0 };
	for (int i = 0; i < DATA_SIZE; i++)
		Data[i] = i + 1;

	IComputeBuffer* in_Buffer = controller->NewReadBuffer(DATA_SIZE, sizeof(float));
	IComputeBuffer* out_Buffer = controller->NewWriteBuffer(DATA_SIZE, sizeof(float));

	IComputeProgram::BindIndex ind{};

	ind.RegisterIndex = 0;
	program->KernelSetBuffer(kernel_name, in_Buffer, ind);

	ind.RegisterIndex = 0;
	program->KernelSetBuffer(kernel_name, out_Buffer, ind);

	program->FinishBuild();

	in_Buffer->SetData(Data);

	program->RunKernel(kernel_name, DATA_SIZE, 0, 0);

	out_Buffer->GetData(Data);

	for (int i = 0; i < DATA_SIZE; i++)
	{
		printf("res '%i': %f\n", i, Data[i]);
	}

	ComputeInterface::DisposePlatform(ComputeInterface::DIRECTX);
	printf("DirectX Disposed.");

	return 0;
}

int VoxelTest()
{
	/*int x = 5;
	int y = 11;
	int z = 2;

	int width = 32;
	int height = 32;
	int depth = 32;

	int i = _3D_to_1D(x, y, z, width, height);
	glm::ivec3 res = _1D_to_3D(i, width, height);

	printf("%i, %i, %i, %i \n", res.x, res.y, res.z, i);*/


	ChunkSettings settings;
	ChunkGenerationOptions gen_options;
	ChunkRenderOptions render_options;

	int size = 8;
	int batchesPerGroup = 2;
	int numGroups = 1;

	settings.GetSettings()->setString("programDir", "C:/Users/Jon/Source/cpp_libs/VoxelEngine/shaders/Vulkan/voxel");
	settings.GetSettings()->setFloat("voxelsPerMeter", 1);
	settings.GetSettings()->setInt("chunkMeterSizeX", size);
	settings.GetSettings()->setInt("chunkMeterSizeY", size);
	settings.GetSettings()->setInt("chunkMeterSizeZ", size);
	settings.GetSettings()->setInt("TotalBatchGroups", batchesPerGroup);
	settings.GetSettings()->setInt("BatchesPerGroup", numGroups);
	

	int compare_1 = 0;
	int cmpare_2 = 1;//batchesPerGroup * numGroups - 1;

	std::vector<MeshData*> data;

	for (int i = 0; i < batchesPerGroup * numGroups; i++) {
		gen_options.locations.push_back(glm::ivec3(0, 0, 0));
		render_options.locations.push_back(glm::ivec3(0, 0, 0));
		data.push_back(new MeshData());
	}

	IVoxelBuilder* builder = new SmoothVoxelBuilder();

	auto start = std::chrono::high_resolution_clock::now();
	builder->Init(settings);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration<double>(end - start).count();
	double init_t = duration;

	auto start_total = std::chrono::high_resolution_clock::now();


	start = std::chrono::high_resolution_clock::now();
	glm::dvec4 gen_times = builder->Generate(gen_options);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration<double>(end - start).count();
	double generate_t = duration;

	start = std::chrono::high_resolution_clock::now();
	glm::dvec4 render_times = builder->Render(render_options);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration<double>(end - start).count();
	double render_t = duration;

	start = std::chrono::high_resolution_clock::now();
	std::vector<glm::ivec4> counts = builder->GetSize();
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration<double>(end - start).count();
	double getsize_t = duration;



	start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < batchesPerGroup * numGroups; i++) {
		data[i]->Vertex = new glm::vec4[counts[i].x];
		data[i]->Normal = new glm::vec4[counts[i].x];
		data[i]->Triangles = new int[counts[i].x];
		builder->Extract(data[i]->Vertex, data[i]->Normal, data[i]->Triangles, counts[i]);
	}

	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration<double>(end - start).count();
	double extract_t = duration;

	auto end_total = std::chrono::high_resolution_clock::now();
	double duration_total = std::chrono::duration<double>(end - start).count();


	builder->Dispose();


	printf("init_t: %f\n", init_t);
	printf("generate_t: %f, (%f, %f, %f, %f) = %f\n", generate_t, gen_times.x, gen_times.y, gen_times.z, gen_times.w, gen_times.x + gen_times.y + gen_times.z + gen_times.w);
	printf("render_t: %f, (%f, %f, %f, %f) = %f\n", render_t, render_times.x, render_times.y, render_times.z, render_times.w, render_times.x + render_times.y + render_times.z + render_times.w);
	printf("getsize_t: %f\n", getsize_t);
	printf("extract_t: %f\n", extract_t);
	printf("Total_added: %f\n", generate_t + render_t + getsize_t + extract_t);
	printf("Total: %f (%f / second)\n", duration_total, 1 / (duration_total / (batchesPerGroup * numGroups)));

	printf("%i = %i, %i = %i\n", counts[compare_1].y, counts[compare_1].x, counts[cmpare_2].y, counts[cmpare_2].x);

	for (int i = 0; i < counts.size(); i++) {
		printf("chunk %i start: %i\n", i, counts[i].y);
	}

	if (counts[compare_1].x == counts[cmpare_2].x) {
		bool doesMatch = true;
		for (int i = 0; i < counts[compare_1].x; i++) {
			//continue;

			if (dist(data[compare_1]->Vertex[i], data[cmpare_2]->Vertex[i]) > 0.0001f ||
				dist(data[compare_1]->Normal[i], data[cmpare_2]->Normal[i]) > 0.0001f ||
				data[compare_1]->Triangles[i] != data[cmpare_2]->Triangles[i]) {
				doesMatch = false;
				//printf("Batches do not match! %i (%f, %f, %f) != (%f, %f, %f)\n", i,
				//	data[compare_1]->Vertex[i].x, data[compare_1]->Vertex[i].y, data[compare_1]->Vertex[i].z,
				//	data[cmpare_2]->Vertex[i].x, data[cmpare_2]->Vertex[i].y, data[cmpare_2]->Vertex[i].z);
				//break;
			}

			
			printf("%i (%f, %f, %f, %i) == (%f, %f, %f, %i)\n", i,
				data[compare_1]->Vertex[i].x, data[compare_1]->Vertex[i].y, data[compare_1]->Vertex[i].z, data[compare_1]->Triangles[i],
				data[cmpare_2]->Vertex[i].x, data[cmpare_2]->Vertex[i].y, data[cmpare_2]->Vertex[i].z, data[cmpare_2]->Triangles[i]);
		}
		if (doesMatch) {
			printf("Batch created successfully!\n");
		}
	}
	else {
		printf("Sizes are different: %i != %i \n", counts[compare_1].x, counts[cmpare_2].x);
	}

	

	printf("Vertex: %i, Triangle: %i\n", counts[0].x, counts[0].x);

	//delete data;

	return 0;
}

int Vulkan_test()
{
	//ComputeInterface::ControllerInfo test_controllerInfo;
	//ComputeInterface::GetComputeController(ComputeInterface::VULKAN, test_controllerInfo);

	//return 0;
	//testConstructor();


	std::vector<Vulkan_Device_Info> devices = ComputeInterface::GetSupportedDevices_Vulkan();

	printf("Vulkan Devices: %u\n", (uint32_t)devices.size());
	for (Vulkan_Device_Info info : devices) {
		//Vulkan_Device_Info info = dev.Vulkan_Info;

		printf("\t %s (%s): %i, %s\n", info.Name, info.GetTypeName().c_str(), info.Device_ID, info.GetUUID().c_str());
	}

	//return 0;

	Vulkan_Device_Info device = devices[0];

	ComputeInterface::ControllerInfo controllerInfo{};
	controllerInfo.device = &device;
	controllerInfo.SetProgramDir("C:/Users/Jon/Source/cpp_libs/VoxelEngine/shaders/Vulkan/test");
	IComputeController* controller = ComputeInterface::GetComputeController(ComputeInterface::VULKAN, controllerInfo);

	std::string kernel_name1 = "main";
	//std::string kernel_name1 = "work";
	//std::string kernel_name2 = "work2";

	IComputeProgram::ProgramInfo p_info("compute", IComputeProgram::FileType::Binary);
	p_info.AddKernel(kernel_name1);
	//p_info.AddKernel(kernel_name2);

	IComputeProgram* program = controller->AddProgram(p_info);

	program->Build();

	float Data[DATA_SIZE] = { 0 };
	for (int i = 0; i < DATA_SIZE; i++)
		Data[i] = i + 1;

	IComputeBuffer* in_Buffer = controller->NewReadBuffer(DATA_SIZE, sizeof(float));
	IComputeBuffer* out_Buffer = controller->NewWriteBuffer(DATA_SIZE, sizeof(float));

	IComputeProgram::BindIndex ind{};

	ind.GlobalIndex = 0;
	program->KernelSetBuffer(kernel_name1, in_Buffer, ind);

	ind.GlobalIndex = 1;
	program->KernelSetBuffer(kernel_name1, out_Buffer, ind);
	//program->KernelSetBuffer(kernel_name1, out_Buffer, ind);

	program->FinishBuild();

	in_Buffer->SetData(Data);


	program->RunKernel(kernel_name1, DATA_SIZE, 0, 0);

	out_Buffer->GetData(Data);

	for (int i = 0; i < DATA_SIZE; i++)
	{
		printf("res '%i': %f\n", i, Data[i]);
	}

	/*program->RunKernel(kernel_name2, DATA_SIZE, 0, 0);

	out_Buffer->GetData(Data);

	for (int i = 0; i < DATA_SIZE; i++)
	{
		printf("res '%i': %i\n", i, Data[i]);
	}*/

	ComputeInterface::DisposePlatform(ComputeInterface::VULKAN);
	printf("Vulkan Disposed.");

	return 0;
}


const char* KernelSource =
"__kernel void hello(__global float *input, __global float *output)\n"\
"{\n"\
"  size_t id = get_global_id(0);\n"
"  output[id] = input[id] * input[id];\n"
"}\n"\
"\n";


int OpenCL_test()
{
	printf("OpenCL_Device_Info size: %i\n", sizeof(OpenCL_Device_Info::mem_size));

	//return 0;

	std::vector<Platform> platforms = ComputeInterface::GetSupportedPlatforms_OpenCL();

	for (const auto& p : platforms)
	{
		printf("Platform %s:\n", p.name);

		std::vector<OpenCL_Device_Info> devices = ComputeInterface::GetSupportedDevices_OpenCL(p);
		for (auto info : devices)
		{
			//OpenCL_Device_Info info = d.OpenCL_Info;
			//printf("\t%s - %s: Frequency: %u, threads: %u, Memory: %lu, Work Size: %u \n", info.vendor, info.name, info.clock_frequency, info.num_compute_units * info.group_size, info.mem_size, info.max_work_size);
			printf("\t%s - %s\n", info.vendor, info.name);
		}
	}

	Platform platf = platforms[1];
	OpenCL_Device_Info dev = ComputeInterface::GetSupportedDevices_OpenCL(platf)[0];

	ComputeInterface::ControllerInfo controllerInfo;
	controllerInfo.platform = platf;
	controllerInfo.device = &dev;
	controllerInfo.SetProgramDir("C:/Users/jdrurka1/source/repos/Dynamics-io/Dynamics.io-Testbench/CPP_Bench/shaders/OpenCL/Tree");

	IComputeController* controller = ComputeInterface::GetComputeController(ComputeInterface::OpenCL, controllerInfo);

	std::string kernel_name = "Init";

	IComputeProgram::ProgramInfo p_info("Tree", IComputeProgram::FileType::Text);
	p_info.AddKernel(kernel_name);

	IComputeProgram* program = controller->AddProgram(p_info);


	if (program->GetState() == IComputeProgram::ProgramBuildState::BuildError)
	{
		if (program->GetBuildResultCode() != 0)
		{
			printf("Build failed: %i\n", program->GetBuildResultCode());
			return -1;
		}

		//printf("%s\n\n -------------- \n\n", controller->GetProgramBuilder()->GetFullSource().c_str());
		printf("BUILD ERROR: %s\n", program->GetBuildErrorMessage().c_str());
		
		return -1;
	}

	printf("Finished building program '%s'.\n", p_info.Name().c_str());

	return 0;

	int Data[DATA_SIZE] = { 0 };

	IComputeBuffer* compBuffer = controller->NewReadWriteBuffer(DATA_SIZE, sizeof(int));

	IComputeProgram::BindIndex ind{};
	ind.ParameterIndex = 0;
	program->KernelSetBuffer(kernel_name, compBuffer, ind);

	program->RunKernel(kernel_name, DATA_SIZE, 0, 0);

	compBuffer->GetData(Data);

	for (int i = 0; i < DATA_SIZE; i++)
	{
		printf("res '%i': %i\n", i, Data[i]);
	}


	return 0;
}