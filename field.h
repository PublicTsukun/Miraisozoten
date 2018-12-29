//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#ifndef _FEILD_H_
#define _FEILD_H_

#include "Library/Math.h"
#include <Windows.h>



#define	WALL_SIZE_X		(1990.0f)
#define	WALL_SIZE_Y		(1090.0f)



#define WALL_POS_X	(0.00f)
#define WALL_POS_Y	(200.00f)
#define WALL_POS_Z	(2000.00f)


#define WALL_LIVE_NUM_X	(48)
#define WALL_LIVE_NUM_Y	(27)
#define LIVEWALL_SIZE_X	(WALL_SIZE_X/WALL_LIVE_NUM_X)
#define LIVEWALL_SIZE_Y	(WALL_SIZE_Y/WALL_LIVE_NUM_Y)

//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitField(void);
void LoadFieldTex(void);
void ReleaseTex(void);
void UninitField(void);
void DrawField(void);
void UpdateField(void);

void SetFeildTex(int StageNo);


#endif