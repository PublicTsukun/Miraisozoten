//=============================================================================
//
// message box処理 [messageBox.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "messageBox.h"

#include "Library\ObjectBase2D.h"

#include "Library/DebugProcess.h"
#include "Library/Input.h"
#include "Library/WindowClass.h"
#include "HitCheck.h"

#include "voicetenTest.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MessageBoxColi(int no, Vector2 cod);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
C2DObject S_MessageBox[MESSAGEBOX_MAX];
C2DObject S_MessageBoxEffect[MESSAGEBOX_MAX];

MESSAGEBOX S_MessageBoxWk[MESSAGEBOX_MAX];
MESSAGEBOX S_MessageBoxEffectWk[MESSAGEBOX_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
void InitMessageBox(void)
{
	MESSAGEBOX *mb = GetMessageBox(0);
	MESSAGEBOX *mbe = GetMessageBoxEfx(0);

	for (int i = 0; i < MESSAGEBOX_MAX; i++)
	{
		(mb + i)->use = false;
		(mb + i)->pos = Vector2(0, 0);
		(mb + i)->len = 0.0f;
		(mb + i)->wid = 0.0f;
		(mb + i)->efx = false;

	}

	for (int i = 0; i < MESSAGEBOX_MAX; i++)
	{
		(mbe + i)->use = false;
		(mbe + i)->pos = Vector2(0, 0);
		(mbe + i)->len = 0.0f;
		(mbe + i)->wid = 0.0f;
		(mbe + i)->efx = false;
	}

	// パラメータ設定
	(mb + 0)->pos = Vector2(200, 200);
	(mb + 0)->len = 48.0f;
	(mb + 0)->wid = 48.0f;
	(mb + 0)->use = true;

	S_MessageBox[0].Init(
		(mb + 0)->pos.x,
		(mb + 0)->pos.y,
		(mb + 0)->len,
		(mb + 0)->wid,
		"data/作業/message_button000.png"
		);

	(mbe + 0)->pos = Vector2(200, 200);
	(mbe + 0)->len = 48.0f;
	(mbe + 0)->wid = 48.0f;
	(mbe + 0)->use = false;

	S_MessageBoxEffect[0].Init(
		(mbe + 0)->pos.x,
		(mbe + 0)->pos.y,
		(mbe + 0)->len,
		(mbe + 0)->wid,
		"data/作業/message_button_effect.png"
		);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMessageBox(void)
{
	MESSAGEBOX *mb = GetMessageBox(0);
	MESSAGEBOX *mbe = GetMessageBoxEfx(0);

	for (int i = 0; i < MESSAGEBOX_MAX; i++)
	{
		S_MessageBox[i].Release();
	}

	for (int i = 0; i < MESSAGEBOX_MAX; i++)
	{
		S_MessageBoxEffect[i].Release();
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMessagebox(void)
{
	MESSAGEBOX *mb = GetMessageBox(0);
	MESSAGEBOX *mbe = GetMessageBoxEfx(0);

	for (int i = 0; i < MESSAGEBOX_MAX; i++)
	{
		if ((mb + i)->use == true)
		{
			S_MessageBox[i].Draw();

		}

		if ((mb + i)->efx == true)
		{
			S_MessageBoxEffect[i].Draw();

		}

	}


}


//=============================================================================
// 取得
//=============================================================================
MESSAGEBOX *GetMessageBox(int no)
{
	return (&S_MessageBoxWk[no]);
}

MESSAGEBOX *GetMessageBoxEfx(int no)
{
	return (&S_MessageBoxEffectWk[no]);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMessageBox(void)
{
	MESSAGEBOX *mb = GetMessageBox(0);

	POINT p;
	GetCursorPos(&p);
	ScreenToClient(WindowClass::GetHWnd(), &p);

	Vector2 mousePos;
	mousePos.x = float(p.x);
	mousePos.y = float(p.y);

	//PrintDebugProcess("x位置 : (%f)\n", mousePos.x);
	//PrintDebugProcess("y位置 : (%f)\n", mousePos.y);

	for (int i = 0; i < MESSAGEBOX_MAX; i++)
	{
		MessageBoxColi(i, mousePos);
	}

}

//=============================================================================
// 衝突判定（マウス）
//=============================================================================
void MessageBoxColi(int no, Vector2 cod)
{
	// 変数宣言
	MESSAGEBOX *mb = GetMessageBox(0);

	Vector2 pos;
	Vector2 siz;

	bool hitCheck;

	// パラメータ設定
	pos = (mb + 0)->pos;

	siz.x = (mb + 0)->len;
	siz.y = (mb + 0)->wid;

	//PrintDebugProcess("変数 : (%f)\n", pos.x);
	//PrintDebugProcess("変数 : (%f)\n", pos.y);
	//PrintDebugProcess("変数 : (%f)\n", siz.x);
	//PrintDebugProcess("変数 : (%f)\n", siz.y);
	//PrintDebugProcess("x位置 : (%f)\n", cod.x);
	//PrintDebugProcess("y位置 : (%f)\n", cod.y);

	// チェック
	hitCheck = Collision::RxC2(pos, siz, cod);

	// 処理
	if (hitCheck == true)
	{
		SetMessageboxEfxOn(no);
	}
	else if (hitCheck == false)
	{
		SetMessageboxEfxOff(no);
	}

}

//=============================================================================
// エフェクトスイッチオン
//=============================================================================
void SetMessageboxEfxOn(int no)
{
	MESSAGEBOX *mb = GetMessageBox(0);
	(mb + no)->efx = true;

}

//=============================================================================
// エフェクトスイッチオフ
//=============================================================================
void SetMessageboxEfxOff(int no)
{
	MESSAGEBOX *mb = GetMessageBox(0);
	(mb + no)->efx = false;

}