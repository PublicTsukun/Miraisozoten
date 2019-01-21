//=============================================================================
//
// voiceten発射処理 [VLauncher.cpp]
// Author : 宋彦霖
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
// マクロ定義
//*****************************************************************************
#define V_FREQ (10)	// 発射頻度、1発 : frame

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
D3DXVECTOR3* CalcScreenToWorld(
	D3DXVECTOR3* pout,
	int Sx,  // スクリーンX座標
	int Sy,  // スクリーンY座標
	float fZ,  // 射影空間でのZ値（0～1）
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
// グローバル変数
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
					Vector3(0.0f, 250.0f, -800.0f),				// 発射位置
																//Vector3(0.0f, 250.0f, -0.0f),				// 発射位置
					Vector3(pout->x, pout->y, pout->z));		// 目標位置
				PlaySE(SHOOT_BULLET);
			}

			// タイマーカウントアップ
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
// 闇
// スクリーン座標をワールド座標に変換（ CalcScreenToWorld関数 ）
// スクリーン座標をワールド座標に変換
//=============================================================================
D3DXVECTOR3* CalcScreenToWorld(
	D3DXVECTOR3* pout,
	int Sx,  // スクリーンX座標
	int Sy,  // スクリーンY座標
	float fZ,  // 射影空間でのZ値（0～1）
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
	) {
	// 各行列の逆行列を算出
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, View);
	D3DXMatrixInverse(&InvPrj, NULL, Prj);
	D3DXMatrixIdentity(&VP);
	VP._11 = Screen_w / 2.0f; VP._22 = -Screen_h / 2.0f;
	VP._41 = Screen_w / 2.0f; VP._42 = Screen_h / 2.0f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// 逆変換
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(pout, &D3DXVECTOR3(Sx, Sy, fZ), &tmp);

	return pout;
}


//=============================================================================
// 闇
// スクリーン座標とXZ平面のワールド座標交点算出（ CalcScreenToXZ関数 ）
// XZ平面とスクリーン座標の交点算出関数
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

	// 床との交差が起きている場合は交点を
	// 起きていない場合は遠くの壁との交点を出力
	if (ray.y <= 0) {
		// 床交点
		float Lray = D3DXVec3Dot(&ray, &D3DXVECTOR3(0, 1, 0));
		float LP0 = D3DXVec3Dot(&(-nearpos), &D3DXVECTOR3(0, 1, 0));
		*pout = nearpos + (LP0 / Lray)*ray;
	}
	else {
		*pout = farpos;
	}

	return pout;
}