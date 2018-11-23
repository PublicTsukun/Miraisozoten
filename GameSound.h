//=============================================================================
//
// タイトル処理 [title.h]
//
//=============================================================================
#ifndef _GAME_SOUND_H_
#define _GAME_SOUND_H_

#include <Windows.h>

#define BGM_VOLUME_MIN		(-8000)
#define BGM_VOLUME_MAX		(-500)

#define VOLUME_CONTROL_DOWN	(20)
#define VOLUME_CONTROL_UP	(120)

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
	COUNT_1,
	COUNT_2,
	COUNT_3,
	START,
	FINISH,
	SHOOT_BULLET,
	SCORE_SLOT,
	SCORE_DECISION,
	VIGOR,
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
