//=============================================================================
//
// voiceten���� [voicetenTest.cpp]
// Author : �v�F��
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
			Vector3(200.0f, 200.0f, 0.0f),			// ���ˈʒu
			Vector3(-200.0f, 200.0f, 200.0f));			// �ڕW�ʒu

		SetVoiceten(
			Vector3(200.0f, 200.0f, 0.0f),			// ���ˈʒu
			Vector3(-300.0f, 100.0f, 0.0f));			// �ڕW�ʒu

		SetVoiceten(
			Vector3(200.0f, 200.0f, 0.0f),			// ���ˈʒu
			Vector3(-100.0f, 100.0f, -100.0f));			// �ڕW�ʒu


	}

}

//=============================================================================
// Message Button Effects
//=============================================================================
void TestMB(void)
{
	// �}�E�X�@�X�N���[�����W->�N���C�A���g���W
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(WindowClass::GetHWnd(), &p);

	// ���ʃI���i�e�X�g�j
	if (GetKeyboardTrigger(DIK_K))
	{
		SetMessageboxEfxOn(0);
	}

	// ���ʃI�t�i�e�X�g�j
	if (GetKeyboardTrigger(DIK_L))
	{
		SetMessageboxEfxOff(0);
	}


}