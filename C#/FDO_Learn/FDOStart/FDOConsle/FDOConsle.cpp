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
		//FdoStringP dbName = L"OSGeo.SQLite";
		FdoStringP dbName = L"OSGeo.MySQL";
		
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
	 
		FdoPtr<FdoIConnectionPropertyDictionary> dict = info->GetConnectionProperties();

		FdoInt32 count = 0;
		FdoString ** names = NULL;
		FdoStringP name;
		FdoStringP localname;
		FdoStringP val;
		FdoStringP defaultVal;
		bool isRequired = false;
		bool isProtected = false;
		bool isFilename = false;
		bool isFilepath = false;

		bool isDatastorename = false;
		bool isEnumerable = false;
		FdoInt32 enumCount = 0;
		FdoString ** enumNames = NULL;
		FdoStringP enumName;
		names = dict->GetPropertyNames(count);
		for (int i = 0; i < count; i++) {
			name = names[i];
			val = dict->GetProperty(name);
			defaultVal = dict->GetPropertyDefault(name);
			localname = dict->GetLocalizedName(name);
			isRequired = dict->IsPropertyRequired(name);
			isProtected = dict->IsPropertyProtected(name);
			isFilename = dict->IsPropertyFileName(name);
			isFilepath = dict->IsPropertyFilePath(name);
			isDatastorename = dict->IsPropertyDatastoreName(name);
			isEnumerable = dict->IsPropertyEnumerable(name);
			if (isEnumerable) {
				if (isRequired) {
					enumNames = dict->EnumeratePropertyValues(name, enumCount);
					for (int j = 0; j < enumCount; j++) {
						enumName = enumNames[j];
					}
				}
			}
		}
	
		dict->SetProperty(L"Username", L"root");
		dict->SetProperty(L"Password", L"66666666");
		dict->SetProperty(L"Service", L"localhost");
	
		FdoStringP connectStr = fdoConnection->GetConnectionString();
		std::wcout << connectStr << std::endl;
		//fdoConnection->SetConnectionString(L"Username = root; Password = 66666666; Service = localhost; ");
		
		FdoConnectionState state = fdoConnection->Open();

		FdoPtr<FdoICommandCapabilities> commandCapabilities = fdoConnection->GetCommandCapabilities();
		bool bSupportsCreateDatastore = false;
		FdoInt32 numCommands;
		FdoInt32* commands = commandCapabilities->GetCommands(numCommands);
		for (int i = 0; i < numCommands; i++) {
			switch (commands[i]) {
			case FdoCommandType_CreateDataStore: bSupportsCreateDatastore = true;
			}
		}

		FdoPtr<FdoICreateDataStore> createDataStoreCmd = 
			dynamic_cast<FdoICreateDataStore *> (fdoConnection->CreateCommand(FdoCommandType_CreateDataStore));
		FdoPtr<FdoIDataStorePropertyDictionary> createDsDict = createDataStoreCmd->GetDataStoreProperties();
		createDsDict->SetProperty(L"DataStore", L"fdo_user");
		createDataStoreCmd->Execute();

	}

    return 0;
}

