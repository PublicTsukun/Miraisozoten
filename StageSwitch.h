//=============================================================================
//
// スコア処理 [score.h]
// Author : 
//
//=============================================================================
#ifndef _STAGE_SWITCH_H_
#define _STAGE_SWITCH_H_


#include <Windows.h>
#include "Library/Common.h"

void InitStageSwitch(void);
void UninitStageSwitch(void);
void DrawStageSwitch(void);
void UpdateStageSwitch(void);

void CameraShutter(int stagenum);
void UseBoard(int stagenum);

#endif