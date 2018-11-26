//=============================================================================
//
// タイトル処理 [title.h]
//
//=============================================================================
#ifndef _GAME_SOUND_H_
#define _GAME_SOUND_H_

#include <Windows.h>

#define BGM_VOLUME_MIN		(-9000)
#define BGM_VOLUME_MAX		(-2000)

#define VOLUME_CONTROL_DOWN	(50)
#define VOLUME_CONTROL_UP	(300)

enum BGM_NO
{
	TITLE,
	GAME_AKIBA,
	GAME_SPACE,
	GAME_BONUS,
	RESULT,
	BGM_MAX
};

enum SE_NO
{
	CURSOL,
	DECIDE,
	START,
	COUNT_1,
	COUNT_2,
	COUNT_3,
	FINISH,
	SHOOT_BULLET,
	SCORE_SLOT,
	SCORE_DECISION,
	VIGOR,
	MODE,
	CURTAIN,
	GAGE_1ST2ND,
	GAGE_LAST,
	THANKYOU,
	EXCELLENT,
	SLOT_STOP,
	SE_MAX
};
//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitGameSound(void);
void UninitGameSound(void);

void PlaySE(int no);
void PlayBGM(int no);
void StopSE(int no);
void StopBGM(int no);
bool PlayCheckSE(int no);
bool PlayCheckBGM(int no);

void UpdateGameSound(void);

#endif
