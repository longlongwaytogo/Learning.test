#include <iostream>
#include <windows.h>


#pragma comment(lib,"winmm.lib")

#include "WavPlaer.h"

void main(int argc,char** argv)
{

	std::string fileName = "D:\\song1.wav";
	int type = WavPlaer::PLAY_NORMAL;
	if(argc > 1)
	{
		fileName = argv[1];
	}
	if(argc > 2) 
	{
		type = atoi(argv[2]);
	}

	std::cout<< "wav play" << std::endl;

	WavPlaer player;
	
	player.play("D:\\song1.wav",type);

	while(1)
	{
		Sleep(100);
	}
 
}