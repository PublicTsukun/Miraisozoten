#ifndef _VOICE_TANK_H_INCLUDE_
#define _VOICE_TANK_H_INCLUDE_
/* íSìñ : èâ */

#include "UIEnergyTank.h"
#include "Library\Common.h"
constexpr int VoiceVolumeMIN = 120;
constexpr int VoiceVolumeMAX = 3000;

class VoiceTankUI : public CEnergyTankUI
{
public:
	static int GetVoiceVolume();

public:
	void Init();
	void Update();
	void Uninit();

};


#endif // !_VOICE_TANK_H_INCLUDE_
