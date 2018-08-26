// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;
#define BOOST_TEST_MODULE My Test 
#include <boost/test/included/unit_test.hpp> 


struct global_fixture // 全局测试夹具类
{
	global_fixture() { std::cout << "-------------global setup------------\n"; }
	~global_fixture() { std::cout << "------------ global shutdown-------------\n"; }
};

struct assign_fixture
{
	assign_fixture() { std::cout << "----------- suit setup-----------" << std::endl; }
	~assign_fixture() { std::cout << "------------suit shutdown ------------" << std::endl; }

	std::vector<int > v;
};

// BOOST_GLOBAL_FIXTURE(global_fixture);


 
// 定义测试套件级别的夹具
 //BOOST_FIXTURE_TEST_SUITE(s_assign,assign_fixture);
 
// BOOST_AUTO_TEST_SUITE(s_assign)

BOOST_AUTO_TEST_CASE(first_test)
{
	int i = 1;
	BOOST_TEST(i);
	BOOST_TEST(i == 2);
}


BOOST_AUTO_TEST_CASE(second_Test)
{
	std::cout << "second_Test" << std::endl;
}

#include <iostream>
#include <boost/lexical_cast.hpp>

BOOST_AUTO_TEST_CASE(lexical_cast_Test)
{
	using std::string;
	const double d = 123.13;
	string s = boost::lexical_cast<string>(d);
	std::cout << s << std::endl;
}

#include <boost/filesystem.hpp>

BOOST_AUTO_TEST_CASE(FileSystem_path_Test)
{
	boost::filesystem::path p1("C:\\");
	boost::filesystem::path p2("C:\\windows");
	boost::filesystem::path p3("C:\\Program Files");
	boost::filesystem::path p("C:\\Windows\\System");
	std::cout << p.string() << std::endl;
	//std::cout << p.file_string() << std::endl;
	//std::cout << p.directory_string() << std::endl;
	//std::cout << p.filename() << std::endl;

	std::cout << "root_name:" << p.root_name() << std::endl;
	std::cout << "parent path:" << p.parent_path() << std::endl;
	std::cout << p.filename() << std::endl;
	std::cout << p.root_directory() << std::endl;
	boost::filesystem::path p4("photo.jpg");
	std::cout << p4.stem() << std::endl;
	std::cout << p4.extension() << std::endl;


	for (boost::filesystem::path::const_iterator it = p3.begin(); it != p3.end(); ++it)
		cout << *it << endl;

	boost::filesystem::path p5("c:\\");
	p5 /= "Windows\\System";
	std::cout << p5.string() << std::endl;

	boost::filesystem::file_status s = boost::filesystem::status(p5);
	std::cout << boost::filesystem::is_directory(s) << std::endl;

	BOOST_CHECK_EQUAL(1,3);
}


// BOOST_AUTO_TEST_SUITE_END() // 测试套件结束