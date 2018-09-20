//=============================================================================
//
// カメラ処理 [Camera.cpp]
//
//=============================================================================
#include "Camera.h"
#include "Direct3D.h"
#include "Input.h"

// マクロ定義
#define CtoA_INTERVAL_MAX	(640.0f)	// カメラと注視点間の最大距離
#define CtoA_INTERVAL_MIN	(320.0f)	// カメラと注視点間の最小距離
#define CAMERA_ANGLE		(10)


//----コンストラクタ--------
CCamera::CCamera()
{
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Gaze = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	UpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Angle = D3DXVECTOR3(0.0f, D3DXToRadian(90), 0.0f);
	Interval = CtoA_INTERVAL_MIN;
	Sensitivity = GAZE_MOVE_VALUE;
}

//----デストラクタ--------
CCamera::~CCamera()
{

}

//----初期化--------
void CCamera::Init(void)
{
	// カメラの初期化
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

//----マトリックス生成--------
void CCamera::CreateMatrix(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

	/* ビューマトリックス */
	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&ViewMatrix);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&ViewMatrix,
		&Position,		// カメラの視点
		&Gaze,			// 視線先
		&UpVector);		// 上方向

						// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &ViewMatrix);


	/* プロジェクションマトリックス */
	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&ProjectionMatrix);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&ProjectionMatrix,
		VIEW_ANGLE,		// ビュー平面の視野角
		VIEW_ASPECT,	// ビュー平面のアスペクト比
		VIEW_NEAR_Z,	// ビュー平面のNearZ値
		VIEW_FAR_Z);	// ビュー平面のFarZ値

						// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &ProjectionMatrix);
}

//----マトリックス取得----
D3DXMATRIX CCamera::GetViewMatrix(void)
{
	return this->ViewMatrix;
}


//*****************************************************************************
// グローバル変数
//*****************************************************************************
CCamera GameCamera;

#if _DEBUG
CCamera DebugCamera;
bool DebugCameraFlag = false;
#endif // _DEBUG


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCamera(void)
{
	// ゲームカメラ
	GameCamera.Init();

#if _DEBUG
	// デバックカメラ
	DebugCamera.Init();
#endif // _DEBUG


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCamera(D3DXVECTOR3 target)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void SetCamera(void)
{
#if _DEBUG
	if (DebugCameraFlag)
	{
		// デバックカメラ
		DebugCamera.CreateMatrix();
	}
	else
	{
		// ゲームカメラ
		GameCamera.CreateMatrix();
	}
#else
	// ゲームカメラ
	GameCamera.CreateMatrix();
#endif // _DEBUG

}

//=============================================================================
// ビューマトリックス取得関数
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return GameCamera.GetViewMatrix();
}

