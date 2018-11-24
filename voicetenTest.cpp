//=============================================================================
//
// voiceten処理 [voicetenTest.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "voicetenTest.h"

#include "Library/DebugProcess.h"
#include "Library/Input.h"
#include "Library/ObjectBase3D.h"
#include "Library/ObjectBase2D.h"
#include "Library/WindowClass.h"
#include "HitCheck.h"

#include "voiceten.h"
#include "messageBox.h"
#include "enemyRE.h"

/* 初追加分 */
#include "voicetank.h"
#include "AimPointer.h"
#include "GameSound.h"

//=============================================================================
// Voiceten Launcher
//=============================================================================
void TestVL(void)
{
	if (CEnergyTankUI::GetVoiceVolume() > 30)	// 30 : 一定値以下を無視
	{
		//SetVoiceten(
		//	Vector3(200.0f, 200.0f, 0.0f),			// 発射位置
		//	Vector3(-200.0f, 200.0f, 200.0f));			// 目標位置

		Vector2 direction = AimPointer::GetPosition();

		SetVoiceten(
			Vector3(0.0f, 100.0f, -200.0f),			// 発射位置
			Vector3(direction.x, direction.y, 0.0f));			// 目標位置

		//SetVoiceten(
		//	Vector3(200.0f, 200.0f, 0.0f),			// 発射位置
		//	Vector3(-100.0f, 100.0f, -100.0f));			// 目標位置

		PlaySE(SHOOT_BULLET);
	}


	// テスト用、全滅
	if (GetKeyboardTrigger(DIK_X))
	{
		VanisnAllEnenyRE();
	}

}

//=============================================================================
// Message Button Effects
//=============================================================================
void TestMB(void)
{
	// マウス　スクリーン座標->クライアント座標
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(WindowClass::GetHWnd(), &p);

	// 効果オン（テスト）
	if (GetKeyboardTrigger(DIK_K))
	{
		SetMessageboxEfxOn(0);
	}

	// 効果オフ（テスト）
	if (GetKeyboardTrigger(DIK_L))
	{
		SetMessageboxEfxOff(0);
	}

}

//=============================================================================
// Collision
//=============================================================================
void TestCO(void)
{
	VOICETEN *v = GetVoiceten(0);
	ENEMY *e = GetEnemyRE(0);

	// 衝突範囲設定(1)
	const float len = 24.0f;
	const float hei = 24.0f;
	const float wid = 5.0f;

	// 衝突範囲設定(2)
	Vector3 vA1 = v->pos;
	Vector3 vA2 = v->pos;
	Vector3 vB1 = e->pos;
	Vector3 vB2 = e->pos;

	vA1.x = v->pos.x - len;		// 左
	vA1.y = v->pos.y + hei;		// 上
	vA1.z = v->pos.z - wid;		// 前

	vA2.x = v->pos.x + len;		// 右
	vA2.y = v->pos.y - hei;		// 下
	vA2.z = v->pos.z + wid;		// 奥

	vB1.x = e->pos.x - len;		// 左
	vB1.y = e->pos.y + hei;		// 上
	vB1.z = e->pos.z - wid;		// 前

	vB2.x = e->pos.x + len;		// 右
	vB2.y = e->pos.y - hei;		// 下
	vB2.z = e->pos.z + wid;		// 奥

	// チェック
	if ((vA2.x > vB1.x)
		&& (vB2.x > vA1.x)
		&& (vA2.y < vB1.y)
		&& (vB2.y < vA1.y)
		&& (vA2.z > vB1.z)
		&& (vB2.z > vA1.z)
		)
	{
		// 処理
		e->use = FALSE;
	}

	//PrintDebugProcess("A: (%f), (%f), (%f)\n", v->pos.x, v->pos.y, v->pos.z);

	//PrintDebugProcess("A: (%f), (%f), (%f)\n", vA1.x, vA1.y, vA1.z);
	//PrintDebugProcess("A: (%f), (%f), (%f)\n", vA2.x, vA2.y, vA2.z);

	//PrintDebugProcess("B: (%f), (%f), (%f)\n", e->pos.x, e->pos.y, e->pos.z);

	//PrintDebugProcess("B: (%f), (%f), (%f)\n", vB1.x, vB1.y, vB1.z);
	//PrintDebugProcess("B: (%f), (%f), (%f)\n", vB2.x, vB2.y, vB2.z);


	//PrintDebugProcess("check: (%d)\n", check);

}