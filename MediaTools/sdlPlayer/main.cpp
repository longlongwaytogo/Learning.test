#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <signal.h>  
#include <SDL.h>  
#include <SDL_mixer.h>  

#include <iostream>

using namespace std;

int main(int argc,char** argv)
{

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){  
		std::cout << SDL_GetError() << std::endl;   
		return 1;  
	}  

	//���������ļ�  
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);  
	Mix_Music *sound=Mix_LoadMUS("D://11.mp3");  
	Mix_PlayMusic(sound,1);  
	SDL_Delay(10000);    //һ��Ҫ�д˾仰���������������رգ���������������  
	return 0;  

}