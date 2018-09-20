//=============================================================================
//
// �J�������� [Camera.cpp]
//
//=============================================================================
#include "Camera.h"
#include "Direct3D.h"
#include "Input.h"

// �}�N����`
#define CtoA_INTERVAL_MAX	(640.0f)	// �J�����ƒ����_�Ԃ̍ő勗��
#define CtoA_INTERVAL_MIN	(320.0f)	// �J�����ƒ����_�Ԃ̍ŏ�����
#define CAMERA_ANGLE		(10)


//----�R���X�g���N�^--------
CCamera::CCamera()
{
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Gaze = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	UpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Angle = D3DXVECTOR3(0.0f, D3DXToRadian(90), 0.0f);
	Interval = CtoA_INTERVAL_MIN;
	Sensitivity = GAZE_MOVE_VALUE;
}

//----�f�X�g���N�^--------
CCamera::~CCamera()
{

}

//----������--------
void CCamera::Init(void)
{
	// �J�����̏�����
	Gaze = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Interval = CtoA_INTERVAL_MAX;
	Sensitivity = GAZE_MOVE_VALUE;

	Position.x = 0.0f;
	Position.y = Interval * sinf(D3DXToRadian(CAMERA_ANGLE));
	Position.z = Interval * -cosf(D3DXToRadian(CAMERA_ANGLE));
	Position += Gaze;

	UpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	Angle = D3DXVECTOR3(0.0f, D3DXToRadian(90), 0.0f);

}

//----�}�g���b�N�X����--------
void CCamera::CreateMatrix(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

	/* �r���[�}�g���b�N�X */
	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&ViewMatrix);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&ViewMatrix,
		&Position,		// �J�����̎��_
		&Gaze,			// ������
		&UpVector);		// �����

						// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &ViewMatrix);


	/* �v���W�F�N�V�����}�g���b�N�X */
	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&ProjectionMatrix);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&ProjectionMatrix,
		VIEW_ANGLE,		// �r���[���ʂ̎���p
		VIEW_ASPECT,	// �r���[���ʂ̃A�X�y�N�g��
		VIEW_NEAR_Z,	// �r���[���ʂ�NearZ�l
		VIEW_FAR_Z);	// �r���[���ʂ�FarZ�l

						// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &ProjectionMatrix);
}

//----�}�g���b�N�X�擾----
D3DXMATRIX CCamera::GetViewMatrix(void)
{
	return this->ViewMatrix;
}


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CCamera GameCamera;

#if _DEBUG
CCamera DebugCamera;
bool DebugCameraFlag = false;
#endif // _DEBUG


//=============================================================================
// ����������
//=============================================================================
HRESULT InitCamera(void)
{
	// �Q�[���J����
	GameCamera.Init();

#if _DEBUG
	// �f�o�b�N�J����
	DebugCamera.Init();
#endif // _DEBUG


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCamera(D3DXVECTOR3 target)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void SetCamera(void)
{
#if _DEBUG
	if (DebugCameraFlag)
	{
		// �f�o�b�N�J����
		DebugCamera.CreateMatrix();
	}
	else
	{
		// �Q�[���J����
		GameCamera.CreateMatrix();
	}
#else
	// �Q�[���J����
	GameCamera.CreateMatrix();
#endif // _DEBUG

}

//=============================================================================
// �r���[�}�g���b�N�X�擾�֐�
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return GameCamera.GetViewMatrix();
}

