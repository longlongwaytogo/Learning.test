#include "comm.h"
float comm::s_val = 3.14f;

const float  s_cval = 2.23f;
float comm::sqrt(float v)
{
	return v * v;
}

float comm::getValue()
{
	return m_val;
}

void comm::setValue(float v)
{
	m_val = v;
}

std::string GetSystemName()
{
	static std::string info = "windows 10";
	return info;
}

int GetSystemNum()
{
	return  2023829923;
}

 
