#pragma once

#ifdef comm_EXPORTS
#define COMM_API __declspec(dllexport) 
#else
#define COMM_API __declspec(dllimport)
#endif 

#include <string>
class comm
{
public:
	static float sqrt(float v);
	float getValue();
	void setValue(float v);
private:
	
	float m_val;
public:
	COMM_API static float s_val;
};
COMM_API extern const float s_cval;

std::string GetSystemName();

// 静态函数不能被dll导出
// static int GetSystemNum();
