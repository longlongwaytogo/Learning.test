// cliTest.cpp: 主项目文件。

#include "stdafx.h"
#include "osgWindow.h"

using namespace System;
using namespace System::Windows::Forms;


int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Hello World");

    cliTest::osgWindow^form = gcnew cliTest::osgWindow;
    Application::Run(form);
    return 0;
}
