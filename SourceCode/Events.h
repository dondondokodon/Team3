#pragma once
#include "OBJ2D.h"
#include "SceneBuildSlect.h"

class Events
{
protected:
	extraSprite text[10];
	VECTOR2 scale  = { 1.0f,1.0f };
	bool isScaleUp = false;
	int pushCount  =0;
	bool isRight   = false;
	int drawMask=0;

private:
	enum
	{
		TEXT_TITLE = 1 << 0, // text[0]
		TEXT_MSG1  = 1 << 1, // text[1]
		TEXT_LEFT  = 1 << 2, // text[2]
		TEXT_RIGHT = 1 << 3, // text[3]
		TEXT_MSG2  = 1 << 4, // text[4]
		TEXT_MSG3  = 1 << 5, // text[5]
		TEXT_MSG4  = 1 << 6, // text[6]
		TEXT_MSG5  = 1 << 7, // text[7]
		TEXT_MSG6  = 1 << 8, // text[8]
		TEXT_MSG7  = 1 << 9, // text[9]
	};

public:
	Events(){}
	bool update();		//true‚Åscene•Ï‚¦‚é
	void init();
	void render();
};

