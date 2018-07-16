#pragma once

#include <string>

class WavPlaer
{
public:
	WavPlaer(void);
	~WavPlaer(void);

	enum {
		PLAY_NORMAL,
		PLAY_REPEAT
	} PlayType;
	bool play(std::string fileName,int playType = PLAY_NORMAL); // ����

	bool pause(); // ��ͣ

	bool stop(); // ֹͣ

	bool resume();// ����


};

