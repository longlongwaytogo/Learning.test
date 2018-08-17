#include "stdafx.h"
#include "FDOHelper.h"

#include <Fdo/IProviderRegistry.h>
#include <Fdo/ClientServices/ProviderCollection.h>
#include <Fdo/ClientServices/ProviderRegistry.h>
#include <Fdo/ClientServices/FeatureAccessManager.h>
#include <Fdo/ClientServices/Provider.h>

std::vector<std::wstring> FDOHelper::m_providers;

FDOHelper::FDOHelper()
{
}


FDOHelper::~FDOHelper()
{
}

void FDOHelper::GetProviderInfo()
{ 
	// 获取Provider注册信息
	FdoPtr<FdoProviderRegistry> reg = (FdoProviderRegistry*)FdoFeatureAccessManager::GetProviderRegistry();
	FdoPtr<FdoProviderCollection> providers =(FdoProviderCollection*)reg->GetProviders();
	
	FdoStringP displayName;
	FdoStringP internalName;
	FdoStringP description;
	FdoPtr<FdoProvider> provider;
	const int count = providers->GetCount();

	m_providers.clear();
	for (int i = 0; i < count; ++i)
	{
		provider = providers->GetItem(i);
		displayName = provider->GetDisplayName();
		internalName = provider->GetName();
		description = provider->GetDescription();

		std::wcout << L"dispalyName:" << displayName << std::endl;
		std::wcout << L"internalName:" << internalName << std::endl;
		// std::wcout << L"description:" << description << std::endl;

		m_providers.push_back(std::wstring((FdoString*)internalName));
	}
	 
}
