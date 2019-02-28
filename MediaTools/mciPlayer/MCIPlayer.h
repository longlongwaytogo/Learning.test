//////////////////////////////////////////////////////////////////////////
// @File:MCIPlayer.h
// @description: 使用windows Media SDK 中的 MCI进行音频播放开发
// @author:longlongwayto
// @date:2018/06/15

#ifndef __MCIPLAYER_H__
#define __MCIPLAYER_H__

class MCIPlayer
{

public:

	MCIPlayer();
	~MCIPlayer();

	bool openMusicFile(char* fileName);


	bool playMusic( int mode = 0);

	bool stopMusic();

	bool pauseMusic();

	bool resumeMusic();

	bool closeDevice();

	void setVolume(DWORD dwVol);

private:

	unsigned int m_nDevice;


};

#endif // __MCIPLAYER_H__