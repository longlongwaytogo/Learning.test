// FDOConsle.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "FDOHelper.h"

#include <fdo/ClientServices/FeatureAccessManager.h>
#include <fdo.h>

int main()
{
	//setlocale(NULL, "936"); // wrong 
	setlocale(NULL, "zh-cn"); // right
	//setlocale(NULL, "zh_CN"); // wrong
	std::cout << "zhongguo 中国" << std::endl;
	std::wcout << L"zhongguo 中国" << std::endl;

	FDOHelper::GetProviderInfo();

	{
		// test Fdo interface
		// Get connect mgr
		FdoPtr<FdoConnectionManager> connectMgr = (FdoConnectionManager*)FdoFeatureAccessManager::GetConnectionManager();
	
		if (connectMgr)
		{
			std::cout << "connect Mgr get OK!" << std::endl;
		}
		else
		{
			std::cout << "connect Mgr get Fail!" << std::endl;

		}
		// get connect
		FdoStringP dbName = L"OSGeo.SQLite";
		//FdoString dbName = L"OSGeo.MySQL";
		
		//FdoPtr<FdoIConnection> fdoConnection = connectMgr->CreateConnection(dbName);
		FdoPtr<FdoIConnection> fdoConnection = connectMgr->CreateConnection(dbName);

		if (fdoConnection)
		{
			 
			std::cout << "connect  to " << dbName << " OK!" << std::endl;
		}
		else
		{
			std::cout << "connect  to " << dbName << " FAIL!" << std::endl;
		}

		FdoPtr<FdoIConnectionInfo> info = fdoConnection->GetConnectionInfo();
		std::wcout << L"provider Name:" << info->GetProviderName();
	}


    return 0;
}

