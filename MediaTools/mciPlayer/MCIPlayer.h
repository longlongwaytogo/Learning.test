//////////////////////////////////////////////////////////////////////////
// @File:MCIPlayer.h
// @description: ʹ��windows Media SDK �е� MCI������Ƶ���ſ���
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