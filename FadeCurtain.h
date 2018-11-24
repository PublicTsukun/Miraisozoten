#ifndef __FADE_CURTAIN_H_INCLUDE__
#define __FADE_CURTAIN_H_INCLUDE__


#include "Library/ObjectBase2D.h"


enum FADE_CURTAIN_STATE
{
	OPEN  = 0,
	CLOSS = 1,
	SLEEP = 2,
	FADE_CURTAIN_STATE_MAX = SLEEP
};

class FadeCurtain : public ObjectBase2D
{
	static Dx9Texture Texture[FADE_CURTAIN_STATE_MAX];

	FADE_CURTAIN_STATE State;
	int TextureNumber;
	int Timer;

public:
	// 初期化は全部で一度のみ
	static int  Init();
	
	// 終了処理は全部で一回のみ
	static void Uninit();

public:
	FadeCurtain();

	int  Update();
	void Draw();

	void SetFade(FADE_CURTAIN_STATE state);

};


#endif // !__FADE_CURTAIN_H_INCLUDE__
