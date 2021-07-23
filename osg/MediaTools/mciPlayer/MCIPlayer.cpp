#include "MCIPlayer.h"

#include <windows.h>
#include <mmsystem.h>
#include <Digitalv.h>

#pragma  comment(lib,"winmm.lib")
MCIPlayer::MCIPlayer():m_nDevice(0)
{

}

MCIPlayer::~MCIPlayer()
{
	if(m_nDevice)
	{
		MCI_CLOSE_PARMS ps;
		ps.dwCallback = NULL;

		mciSendCommand(m_nDevice,MCI_CLOSE,MCI_NOTIFY,(DWORD)&ps);

		
	}

}

bool MCIPlayer::openMusicFile(char* fileName)
{
	MCI_OPEN_PARMS mciopen;  
	mciopen.lpstrElementName =fileName;  

	mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT,(DWORD_PTR)(&mciopen));  
	m_nDevice =  mciopen.wDeviceID;  
	mciSendCommand(MCI_ALL_DEVICE_ID, MCI_CLOSE, MCI_WAIT, NULL);  
	return m_nDevice == 0;

}

bool MCIPlayer::playMusic( char* fileName，int mode /*= 0*/)
{
	MCI_OPEN_PARMS mciOpenParms;  
	memset(&mciOpenParms, 0, sizeof(MCI_OPEN_PARMS));  
	mciOpenParms.lpstrElementName = pFileName;  

	DWORD dwResult = 0;  
	dwResult = mciSendCommand(m_DeviceID, MCI_OPEN, MCI_OPEN_ELEMENT,  
		(DWORD)(LPVOID)&mciOpenParms);  

	
	MCI_PLAY_PARMS mciPP;  

	DWORD opReturn;  
	opReturn = mciSendCommand(m_nDevice, MCI_PLAY, MCI_NOTIFY, (DWORD)&mciPP);  
	return opReturn;  

}

bool MCIPlayer::stopMusic()
{
	  DWORD retclose=mciSendCommand(m_nDevice, MCI_CLOSE, NULL, NULL);  
	return retclose;
}

bool MCIPlayer::pauseMusic()
{
	 DWORD  dwResult = mciSendCommand(m_nDevice, MCI_PAUSE, NULL, NULL);  
	return dwResult;
}

bool MCIPlayer::resumeMusic()
{
	 DWORD dwResult = mciSendCommand(m_nDevice, MCI_RESUME, NULL, NULL);  
	return dwResult;

}

bool MCIPlayer::closeDevice()
{
	return true;

}

void MCIPlayer::setVolume(DWORD dwVol)
{
	MCI_DGV_SETAUDIO_PARMS	mciSetAudioPara;
	mciSetAudioPara.dwCallback	= NULL;
	mciSetAudioPara.dwItem	 = MCI_DGV_SETAUDIO_VOLUME;
	mciSetAudioPara.dwValue	 = dwVol; //此处就是音量大小 (0--1000)
	DWORD dwReturn = mciSendCommand(m_nDevice, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE |  MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&mciSetAudioPara);
	return dwReturn;
}
