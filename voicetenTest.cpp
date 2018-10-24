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

//=============================================================================
// Voiceten Launcher
//=============================================================================
void TestVL(void)
{
	if (GetKeyboardTrigger(DIK_J))
	{
		SetVoiceten(
			Vector3(200.0f, 200.0f, 0.0f),			// 発射位置
			Vector3(-200.0f, 200.0f, 200.0f));			// 目標位置

		SetVoiceten(
			Vector3(200.0f, 200.0f, 0.0f),			// 発射位置
			Vector3(-300.0f, 100.0f, 0.0f));			// 目標位置

		SetVoiceten(
			Vector3(200.0f, 200.0f, 0.0f),			// 発射位置
			Vector3(-100.0f, 100.0f, -100.0f));			// 目標位置


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