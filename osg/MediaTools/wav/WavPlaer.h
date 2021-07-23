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
	bool play(std::string fileName,int playType = PLAY_NORMAL); // ²¥·Å

	bool pause(); // ÔÝÍ£

	bool stop(); // Í£Ö¹

	bool resume();// ¼ÌÐø


};

