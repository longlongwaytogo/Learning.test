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

	//加载声音文件  
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);  
	Mix_Music *sound=Mix_LoadMUS("D://11.mp3");  
	Mix_PlayMusic(sound,1);  
	SDL_Delay(10000);    //一定要有此句话，否则程序会立即关闭，而不会听到声音  
	return 0;  

}