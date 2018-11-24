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
#include "enemyRE.h"

/* ���ǉ��� */
#include "voicetank.h"
#include "AimPointer.h"
#include "GameSound.h"

//=============================================================================
// Voiceten Launcher
//=============================================================================
void TestVL(void)
{
	if (CEnergyTankUI::GetVoiceVolume() > 30)	// 30 : ���l�ȉ��𖳎�
	{
		//SetVoiceten(
		//	Vector3(200.0f, 200.0f, 0.0f),			// ���ˈʒu
		//	Vector3(-200.0f, 200.0f, 200.0f));			// �ڕW�ʒu

		Vector2 direction = AimPointer::GetPosition();

		SetVoiceten(
			Vector3(0.0f, 100.0f, -200.0f),			// ���ˈʒu
			Vector3(direction.x, direction.y, 0.0f));			// �ڕW�ʒu

		//SetVoiceten(
		//	Vector3(200.0f, 200.0f, 0.0f),			// ���ˈʒu
		//	Vector3(-100.0f, 100.0f, -100.0f));			// �ڕW�ʒu

		PlaySE(SHOOT_BULLET);
	}


	// �e�X�g�p�A�S��
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

//=============================================================================
// Collision
//=============================================================================
void TestCO(void)
{
	VOICETEN *v = GetVoiceten(0);
	ENEMY *e = GetEnemyRE(0);

	// �Փ˔͈͐ݒ�(1)
	const float len = 24.0f;
	const float hei = 24.0f;
	const float wid = 5.0f;

	// �Փ˔͈͐ݒ�(2)
	Vector3 vA1 = v->pos;
	Vector3 vA2 = v->pos;
	Vector3 vB1 = e->pos;
	Vector3 vB2 = e->pos;

	vA1.x = v->pos.x - len;		// ��
	vA1.y = v->pos.y + hei;		// ��
	vA1.z = v->pos.z - wid;		// �O

	vA2.x = v->pos.x + len;		// �E
	vA2.y = v->pos.y - hei;		// ��
	vA2.z = v->pos.z + wid;		// ��

	vB1.x = e->pos.x - len;		// ��
	vB1.y = e->pos.y + hei;		// ��
	vB1.z = e->pos.z - wid;		// �O

	vB2.x = e->pos.x + len;		// �E
	vB2.y = e->pos.y - hei;		// ��
	vB2.z = e->pos.z + wid;		// ��

	// �`�F�b�N
	if ((vA2.x > vB1.x)
		&& (vB2.x > vA1.x)
		&& (vA2.y < vB1.y)
		&& (vB2.y < vA1.y)
		&& (vA2.z > vB1.z)
		&& (vB2.z > vA1.z)
		)
	{
		// ����
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