#pragma once
///////////////////////////////////////////////////////////////////////////
// @file FDOHelper.h
// @description: ����FDO�ĳ��������������
// @author: szh
// @data: 2018/08/17

#include <vector>
#include <string>

class FDOHelper
{
public:
	FDOHelper();
	~FDOHelper();
	static void GetProviderInfo();
	 
public:
	static std::vector<std::wstring> m_providers;

};

