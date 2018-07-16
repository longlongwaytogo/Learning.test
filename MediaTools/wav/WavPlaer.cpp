#include "WavPlaer.h"

#include <windows.h>
#include <mmsystem.h>
WavPlaer::WavPlaer(void)
{
}


WavPlaer::~WavPlaer(void)
{
}

 

bool WavPlaer::play(std::string fileName,int playType /*= PLAY_NORMAL*/)
{
	bool ret = false;
	if(PLAY_NORMAL == playType)
	{
		ret = PlaySoundA(fileName.c_str(),NULL,SND_FILENAME);
	}

	else if( PLAY_REPEAT == playType)
	{
		ret = PlaySoundA(fileName.c_str(),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
	}
	
	return ret;
}

bool WavPlaer::pause()
{
	return true;
}

bool WavPlaer::stop()
{
	return true;

}

bool WavPlaer::resume()
{
	return true;

}
