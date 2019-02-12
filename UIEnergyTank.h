#ifndef _UI_ENERGYTANK_H_INCLUDE_
#define _UI_ENERGYTANK_H_INCLUDE_


#include "Library\ObjectBase2D.h"

#define ENERGY_MIN (250)
#define ENERGY_CORD (140)

class CEnergyTankUI
{
	static Dx9Texture texTank;
	static Dx9Texture texVolume;
	static Dx9Texture texVoiceTen;

protected:
	C2DObject Back;
	C2DObject Liquid;
	C2DObject Tank;
	C2DObject Volume;
	C2DObject VoiceTen;

	Vector2 Size;
	Vector2 Position;
	float   MaxValue;

public:
	static void Initialize();
	static void Uninitialize();

public:
	void Init(float posX, float posY, float sizX, float sizY, float value);
	void SetValue(float value);
	void Draw();

};

#endif // !_UI_ENERGYTANK_H_INCLUDE_
