#ifndef _VOICE_TANK_H_INCLUDE_
#define _VOICE_TANK_H_INCLUDE_
/* íSìñ : èâ */

#include "Library\ObjectBase2D.h"

class CEnergyTankUI
{
	C2DObject Back;
	C2DObject Liquid;
	C2DObject Bubble[3];
	C2DObject Tank;
	C2DObject Volume;
	C2DObject VoiceTen;
	float     BubbleState[3];

public:
	void Init();
	void Update();
	void Draw();
	void Uninit();

};


#endif // !_VOICE_TANK_H_INCLUDE_
