// FileSystem.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <windows.h>
#include <fstream>


using namespace boost::filesystem;
namespace fs = boost::filesystem;
int main(int argc, char** argv)
{
	{
		// \u263A is "Unicode WHITE SMILING FACE = have a nice day!"
		std::string narrow_string("smile2");
		std::wstring wide_string(L"smile2\u263A");
		std::list<char> narrow_list;
		narrow_list.push_back('s');
		narrow_list.push_back('m');
		narrow_list.push_back('i');
		narrow_list.push_back('l');
		narrow_list.push_back('e');
		narrow_list.push_back('3');
		std::list<wchar_t> wide_list;
		wide_list.push_back(L's');
		wide_list.push_back(L'm');
		wide_list.push_back(L'i');
		wide_list.push_back(L'l');
		wide_list.push_back(L'e');
		wide_list.push_back(L'3');
		wide_list.push_back(L'\u263A');

		{ fs::ofstream f("smile"); }
		{ fs::ofstream f(L"smile\u263A"); }
		{ fs::ofstream f(narrow_string); }
		{ fs::ofstream f(wide_string); }
		{ fs::ofstream f(narrow_list); }
		{ fs::ofstream f(wide_list); }
		narrow_list.pop_back();
		narrow_list.push_back('4');
		wide_list.pop_back();
		wide_list.pop_back();
		wide_list.push_back(L'4');
		wide_list.push_back(L'\u263A');
		{ fs::ofstream f(fs::path(narrow_list.begin(), narrow_list.end())); }
		{ fs::ofstream f(fs::path(wide_list.begin(), wide_list.end())); }

	}
	try
	{

		if (argc > 1)
		{
			path p(argv[1]);
			if (is_regular_file(p))
				std::cout << p << " size:" << file_size(p) << "\n";
			else if (is_directory(p))
			{
				std::cout << p << " is a directory\n";
				std::vector<std::string> v;
				for (directory_entry& x : directory_iterator(p))
				{
					std::cout << " " << x.path() << "\n";
					v.push_back(x.path().filename().string());
					std::sort(v.begin(), v.end());
					
				}
				for (auto & x : v)
					std::cout << x << std::endl;

			}
			else
				std::cout << p << " does not exist\n";
		}
	}
	catch (const filesystem_error& ex)
	{
		std::cout << ex.what() << std::endl;

	}

	{
		boost::filesystem::path p("C:\\Windows\\CarSim.ini");
		try
		{
			std::cout <<"CarSim.ini file size:" <<  boost::filesystem::file_size(p) << std::endl;
			std::time_t t = boost::filesystem::last_write_time(p);
			std::cout << "CarSim.ini last write time:" << std::ctime(&t) << std::endl;
		}
		catch (boost::filesystem::filesystem_error& e)
		{
			std::cerr << e.what() << std::endl;
		}


	}

	{
		// read system space
		boost::filesystem::path p("C:\\");
		boost::filesystem::space_info s = boost::filesystem::space(p);
		std::cout << s.capacity << std::endl;
		std::cout << s.free << std::endl;
		std::cout << s.available << std::endl;
	}

	{
		// file folder operate
		try
		{
			boost::filesystem::path p("C:\\Test1");
			if (boost::filesystem::create_directory(p))
			{
				boost::filesystem::rename(p, "C:\\Test2");
				boost::filesystem::remove("C:\\Test2");
				std::cout << p << std::endl;
			}
		}
		catch (boost::filesystem::filesystem_error& e)
		{
			std::cout << e.what() << std::endl;
		}

	}

	{ // 创建一个路径
		std::cout << boost::filesystem::complete("photo.jpg") << std::endl;
		std::cout << boost::filesystem::complete("photo.jpg", "D:\\") << std::endl;
		std::cout << boost::filesystem::current_path() << std::endl;
		SetCurrentDirectoryA("C:\\");
		std::cout << boost::filesystem::current_path() << std::endl;

		
	}
	{
		//  filestream
		boost::filesystem::path p("D:\\test.txt");
		boost::filesystem::ofstream ofs(p);
		ofs << "Hello world" << std::endl;
	}
	{
		boost::filesystem::path p("D:\\666666.txt");
		boost::filesystem::ofstream ofs(p);
		if (ofs.is_open())
			std::cout << "file opened" << std::endl;
		else
			std::cout << "open file fail" << std::endl;
		ofs << "Hello, world!" << std::endl;
	}
    return 0;
} 


