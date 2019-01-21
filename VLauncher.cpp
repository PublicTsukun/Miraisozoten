//=============================================================================
//
// voiceten���ˏ��� [VLauncher.cpp]
// Author : �v�F��
//
//=============================================================================
#include "VLauncher.h"

#include "Library/DebugProcess.h"
#include "voiceten.h"
#include "voicetank.h"
#include "AimPointer.h"

#include "Library\Camera.h"
#include "GameSound.h"

#include "StageManager.h"

#include "S-Editor.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define V_FREQ (10)	// ���˕p�x�A1�� : frame

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
D3DXVECTOR3* CalcScreenToWorld(
	D3DXVECTOR3* pout,
	int Sx,  // �X�N���[��X���W
	int Sy,  // �X�N���[��Y���W
	float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
	);

D3DXVECTOR3* CalcScreenToXZ(
	D3DXVECTOR3* pout,
	int Sx,
	int Sy,
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
	);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int timerVL;

//=============================================================================
// Voiceten Launcher
//=============================================================================
void UpdateVLauncher(void)
{
	STAGE *stage = GetStage();

	if (stage->status == STAGE_STATUS_NORMAL ||
		stage->status == STAGE_STATUS_END
		)
	{
		//if (VoiceTankUI::GetVoiceVolume() > VOICETEN_SHOT_VOL)
		if (1)
		{
			Vector2 direction = AimPointer::GetPosition();

			D3DXVECTOR3 *pout;
			pout = &D3DXVECTOR3(0, 0, 0);

			pout =
				CalcScreenToXZ
				(
					pout,
					(int)direction.x,
					(int)direction.y,
					(int)SCREEN_WIDTH,
					(int)SCREEN_HEIGHT,
					&(GetMtxView)(),
					&(GetMtxProj)()
					);

			if (timerVL % V_FREQ == 0)
			{
				SetVoiceten(
					Vector3(0.0f, 250.0f, -800.0f),				// ���ˈʒu
																//Vector3(0.0f, 250.0f, -0.0f),				// ���ˈʒu
					Vector3(pout->x, pout->y, pout->z));		// �ڕW�ʒu
				PlaySE(SHOOT_BULLET);
			}

			// �^�C�}�[�J�E���g�A�b�v
			timerVL++;

			PrintDebugProcess("pout: (%f), (%f), (%f)\n", pout->x, pout->y, pout->z);

		}
		else
		{
			timerVL = 0;
		}

	}

}

//=============================================================================
// ��
// �X�N���[�����W�����[���h���W�ɕϊ��i CalcScreenToWorld�֐� �j
// �X�N���[�����W�����[���h���W�ɕϊ�
//=============================================================================
D3DXVECTOR3* CalcScreenToWorld(
	D3DXVECTOR3* pout,
	int Sx,  // �X�N���[��X���W
	int Sy,  // �X�N���[��Y���W
	float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
	) {
	// �e�s��̋t�s����Z�o
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, View);
	D3DXMatrixInverse(&InvPrj, NULL, Prj);
	D3DXMatrixIdentity(&VP);
	VP._11 = Screen_w / 2.0f; VP._22 = -Screen_h / 2.0f;
	VP._41 = Screen_w / 2.0f; VP._42 = Screen_h / 2.0f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// �t�ϊ�
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(pout, &D3DXVECTOR3(Sx, Sy, fZ), &tmp);

	return pout;
}


//=============================================================================
// ��
// �X�N���[�����W��XZ���ʂ̃��[���h���W��_�Z�o�i CalcScreenToXZ�֐� �j
// XZ���ʂƃX�N���[�����W�̌�_�Z�o�֐�
//=============================================================================
D3DXVECTOR3* CalcScreenToXZ(
	D3DXVECTOR3* pout,
	int Sx,
	int Sy,
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
	) {
	D3DXVECTOR3 nearpos;
	D3DXVECTOR3 farpos;
	D3DXVECTOR3 ray;
	CalcScreenToWorld(&nearpos, Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj);
	CalcScreenToWorld(&farpos, Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj);
	ray = farpos - nearpos;
	D3DXVec3Normalize(&ray, &ray);

	// ���Ƃ̌������N���Ă���ꍇ�͌�_��
	// �N���Ă��Ȃ��ꍇ�͉����̕ǂƂ̌�_���o��
	if (ray.y <= 0) {
		// ����_
		float Lray = D3DXVec3Dot(&ray, &D3DXVECTOR3(0, 1, 0));
		float LP0 = D3DXVec3Dot(&(-nearpos), &D3DXVECTOR3(0, 1, 0));
		*pout = nearpos + (LP0 / Lray)*ray;
	}
	else {
		*pout = farpos;
	}

	return pout;
}