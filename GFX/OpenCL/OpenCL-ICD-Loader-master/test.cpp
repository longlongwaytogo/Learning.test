#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

// link: icd: https://blog.csdn.net/10km/article/details/50495452
#include <CL/cl.h>

cl_int LoadFileSource(const char *pFileName, std::string &Str);


const static char* source = {
	"__kernel void helloworld(__global char *pIn, __global char *pOut)\n"
	"{	\n"
	"	int iNum = get_global_id(0); \n"
	"	pOut[iNum] = pIn[iNum] + 1;\n"
	"}\n"
};

int main()
{
	// cl_platform ��ʾһ��OpenCL��ִ��ƽ̨��������GPUӲ������N����A��
	cl_platform_id * platforms;
	const char*pFileName = "HelloWorld_Kernel.cl";
	// OpenCL�ж���Ŀ�ƽ̨������
	cl_uint num_platforms;
	cl_int i, err, platform_index = -1;
	err = clGetPlatformIDs(0, NULL, &num_platforms);
	if (err < 0)
	{
		perror("couldn't find any platforms");
		exit(1);
	}

	printf("num of platforms:%d\n", num_platforms);

	// Ϊflatform ����ռ�
	platforms = (cl_platform_id*)(malloc(sizeof(cl_platform_id) * num_platforms));

	clGetPlatformIDs(num_platforms, platforms, NULL);
	char* ext_data = NULL;
	size_t ext_size = 0;
	const char icd_ext[] = "cl_khr_icd";

	// ��ȡƽ̨��Ϣ
	for (i = 0; i < num_platforms; ++i)
	{
		// buffer size
		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, 0, NULL, &ext_size);
		if (err < 0)
		{
			perror("Couldn't read extension data");
			exit(1);
		}
		printf("buffer size:%d\n", ext_size);

		ext_data = (char*)malloc(ext_size);

		// get extension function
		clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, ext_size, ext_data, NULL);
		printf("platform %d support function:%s\n", i, ext_data);

		// get graphic card name 
		char* name = (char*)malloc(ext_size);
		clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, ext_size, name, NULL);
		printf("platform %d name is: %s\n", i, name);

		// get graphic card vendor name
		char* vendor = (char*)malloc(ext_size);
		clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, ext_size, vendor, NULL);
		printf("platform %d vendor info: %s\n", i, vendor);

		// get plat version
		char* ver = (char*)malloc(ext_size);
		clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, ext_size, ver, NULL);
		printf(" platform %d version:%s\n", i, ver);

		// check is the graphic card dependecy or not
		char* profile = (char*)malloc(ext_size);
		clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, ext_size, profile, NULL);
		printf("ƽ̨ %d �Ƕ����ģ�full profile������Ƕ��ʽ�ģ�embeded profile�� ? : %s\n", i, profile);

		// check is support ICD extension
		if (strstr(ext_data, icd_ext) != NULL)
			platform_index = i;
		std::cout << "platform ID = " << platform_index << std::endl;
		// Displayu whether ICD extension is support
		if (platform_index > -1)
			std::cout << "ƽ̨ " << platform_index << "֧��ICD��չ:" << icd_ext << std::endl;

		free(ext_data);
		free(name);
		free(vendor);
		free(ver);
		free(profile);
	}

	if (platform_index <= -1)
		std::cout << "No platforms support" << std::endl;

	// --2. ��ѯGPU�豸����ѡ������豸-
	cl_uint num_devices = 0;
	cl_device_id* pDevices; // �豸ids

	err = clGetDeviceIDs(platforms[platform_index], CL_DEVICE_TYPE_GPU, 0, NULL, &num_devices);
	std::cout << "num devies:" << num_devices;
	if (0 == num_devices)	// ���û��GPU�豸 
	{
		pDevices = (cl_device_id*)malloc(sizeof(cl_device_id)* num_devices);
		clGetDeviceIDs(platforms[platform_index], CL_DEVICE_TYPE_CPU, num_devices, pDevices, 0);
	}
	else
	{
		pDevices = (cl_device_id*)malloc(sizeof(cl_device_id)* num_devices);
		clGetDeviceIDs(platforms[platform_index], CL_DEVICE_TYPE_GPU, num_devices, pDevices, 0);

	}

	// 3. create device context
	cl_context  pContext = clCreateContext(NULL, 1, pDevices, NULL, NULL, NULL);
	if (NULL == pContext)
	{
		std::cout << "Error: cann't create context" << std::endl;
		return 0;
	}

	// 4. create commandQueue;
	cl_command_queue commandQueue = clCreateCommandQueue(pContext, pDevices[0], 0, NULL);
	if (commandQueue == NULL)
	{
		std::cout << "create commandQueue Error " << std::endl;
		return 0;
	}

	// 5. create object
	std::string strSource;
	/*err = LoadFileSource(pFileName, strSource);
	const char* pSource = strSource.c_str();
	cl_uint uiArraySourceSize = strSource.size();*/

	const char* pSource = source;
	cl_uint uiArraySourceSize = strlen(pSource);

	// 6. create program
	cl_program program = clCreateProgramWithSource(pContext, 1, &pSource, &uiArraySourceSize, NULL);
	if (program == NULL)
	{
		std::cout << "create program error!" << std::endl;
		return 0;
	}

	// 7. compile program
	err = clBuildProgram(program, 1, pDevices, NULL, NULL, NULL);
	if (CL_SUCCESS != err)
	{
		std::cout << "Buid Program error!" << std::endl;
		char szBuildlog[16384];
		clGetProgramBuildInfo(program, *pDevices, CL_PROGRAM_BUILD_LOG, sizeof(szBuildlog), szBuildlog,NULL);
		std::cout << "err log:" << std::endl;
		std::cout << szBuildlog << std::endl;
		clReleaseProgram(program);
		return 0;
	}

	// 8. create input output buffer
	const char		*pInput = "gdkknvnqkc";			// �����ַ���
	size_t			uiStrlength = strlen(pInput);	// �����ַ�������
	char			*pOutput = NULL;				// ����ַ���
	cl_mem			memInputBuffer = NULL;			// �����ڴ����
	cl_mem			memOutputBuffer = NULL;			// ����ڴ����
	cl_kernel		Kernel = NULL;					// �ں˶���
	size_t			uiGlobal_Work_Size[1] = { 0 };		// �����趨�ں˷ֲ�	


	memInputBuffer = clCreateBuffer(
		pContext,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, // �����ڴ�Ϊֻ���������Դ����������ڴ渴�Ƶ��豸�ڴ�
		(uiStrlength + 1)* sizeof(char),
		(void*)pInput,
		NULL);

	memOutputBuffer = clCreateBuffer(
		pContext,
		CL_MEM_WRITE_ONLY,
		(uiStrlength + 1) * sizeof(char),
		NULL, NULL);

	if (NULL == memInputBuffer || NULL == memOutputBuffer)
	{
		std::cout << "Error: create memory objects fail" << std::endl;
		return 0;
	}

	// 9 . create kernel object
	Kernel = clCreateKernel(program, "helloworld", // cl �ļ���ں���
		NULL);
	if (NULL == Kernel)
	{
		std::cout << "Cann't create kernel object!" << std::endl;
		return 0;
	}

	// 10. setting kernel object parameter
	err = clSetKernelArg(Kernel,
		0, // index 
		sizeof(cl_mem),
		(void*)&memInputBuffer);

	err |= clSetKernelArg(Kernel, 1, sizeof(cl_mem), (void*)&memOutputBuffer);
	if (CL_SUCCESS != err)
	{
		std::cout << "setting kernel arguments err!" << std::endl;
		return 0;
	}

	// 10 run kernel object
	uiGlobal_Work_Size[0] = uiStrlength; // �����ַ�����С

	// ����������У������豸��ִ���ں��Ŷ�
	err = clEnqueueNDRangeKernel(
		commandQueue,
		Kernel,
		1,
		NULL,
		uiGlobal_Work_Size, // ȷ���ں����豸�ϵĶ������Ԫ��ķֲ�
		NULL,
		0,
		NULL,
		NULL);

	if (CL_SUCCESS != err)
	{
		std::cout << "Cann't run kernel" << std::endl;
		return 0;
	}

	// 12 read outputmem to host memory
	pOutput = (char*)malloc(uiStrlength + 1); // uiStrLenth 
	err = clEnqueueReadBuffer(
		commandQueue,
		memOutputBuffer,
		CL_TRUE, // �ں˶�ȡ���֮ǰ���ú������᷵��
		0,
		uiStrlength * sizeof(char),
		pOutput,
		0,
		NULL,
		NULL);
	if (NULL != err)
	{
		std::cout << "Cann't reading result from buffer" << std::endl;
		return 0;
	}

   // 13 output result
	pOutput[uiStrlength] = '\0';
	std::cout << "Input String:" << std::endl;
	std::cout << pInput << std::endl;
	std::cout << "Output String:" << std::endl;
	std::cout << pOutput << std::endl;

	// 14 .release resource
	err = clReleaseKernel(Kernel);
	err = clReleaseProgram(program);
	err = clReleaseMemObject(memInputBuffer);
	err = clReleaseMemObject(memOutputBuffer);
	err = clReleaseCommandQueue(commandQueue);
	err = clReleaseContext(pContext);

	if (NULL != pOutput)
	{
		free(pOutput);
	}

	if (pDevices)
	{
		free(pDevices);
	}

	getchar();
	free(platforms);
	
	return 0;
}



// ��cl�ļ�����תΪ�ַ���
cl_int LoadFileSource(const char *pFileName, std::string &Str)
{
	size_t		uiSize = 0;
	size_t		uiFileSize = 0;
	char		*pStr = NULL;
	std::fstream fFile(pFileName, (std::fstream::in | std::fstream::binary));


	if (fFile.is_open())
	{
		fFile.seekg(0, std::fstream::end);
		uiSize = uiFileSize = (size_t)fFile.tellg();  // ����ļ���С
		fFile.seekg(0, std::fstream::beg);
		pStr = new char[uiSize + 1];

		if (NULL == pStr)
		{
			fFile.close();
			return 0;
		}

		fFile.read(pStr, uiFileSize);				// ��ȡuiFileSize�ֽ�
		fFile.close();
		pStr[uiSize] = '\0';
		Str = pStr;

		delete[] pStr;

		return 0;
	}

	std::cout << "Error: Failed to open cl file\n:" << pFileName << std::endl;

	return -1;

}