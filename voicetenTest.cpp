//=============================================================================
//
// voiceten処理 [voicetenTest.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "voicetenTest.h"
#include "voiceten.h"
#include "Library\Input.h"

#include "Library/ObjectBase3D.h"

//=============================================================================
// Voiceten Launcher
//=============================================================================
void TestVL(void)
{
	if (GetKeyboardTrigger(DIK_J))
	{
		SetVoiceten(
			Vector3(200.0f, 200.0f, 0.0f),			// 発射位置
			Vector3(-200.0f, 200.0f, 0.0f));		// 目標位置

		SetVoiceten(
			Vector3(200.0f, 200.0f, 0.0f),			// 発射位置
			Vector3(-400.0f, 200.0f, 200.0f));		// 目標位置

		SetVoiceten(
			Vector3(200.0f, 200.0f, 0.0f),			// 発射位置
			Vector3(-200.0f, 000.0f, -100.0f));		// 目標位置
	}
}