//=============================================================================
//
// voiceten���� [voicetenTest.cpp]
// Author : �v�F��
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
			Vector3(200.0f, 200.0f, 0.0f),			// ���ˈʒu
			Vector3(-400.0f, 200.0f, 200.0f));		// �ڕW�ʒu
	}
}