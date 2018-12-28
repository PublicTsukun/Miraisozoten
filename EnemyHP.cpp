//=============================================================================
//
// EnemyHP処理 [EnemyHP.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "EnemyHP.h"

#include "Library/DebugProcess.h"

#include "Library/Input.h"

#include "enemyRE.h"
#include "EnemyDB.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
void EnemyHP::SetUse(bool use)
{
	this->use = use;
}

void EnemyHP::Enable(void)
{
	SetUse(TRUE);
}

void EnemyHP::Disable(void)
{
	SetUse(FALSE);
}

bool EnemyHP::GetUse(void)
{
	return this->use;
}

float EnemyHP::GetSizeX(void)
{
	return this->Size.x;
}

void EnemyHP::InitVertexEnemyHP(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].coord = Vector3(0.0f, 0.0f, 0.0f);
		pVtx[1].coord = Vector3(Size.x, 0.0f, 0.0f);
		pVtx[2].coord = Vector3(0.0f, -Size.y, 0.0f);
		pVtx[3].coord = Vector3(Size.x, -Size.y, 0.0f);

		// 頂点データをアンロックする
		VtxBuff->Unlock();
	}
}

void EnemyHP::SetVertexEnemyHP(float sizeX, float hpRate)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[1].coord = Vector3(sizeX, 0.0f, 0.0f);
		pVtx[3].coord = Vector3(sizeX, -Size.y, 0.0f);

		// テクスチャ座標の設定
		pVtx[1].uv = Vector2(hpRate, 0.0f);
		pVtx[3].uv = Vector2(hpRate, 1.0f);

		// 頂点データをアンロックする
		VtxBuff->Unlock();
	}
}

//*****************************************************************************
// グローバル変数
//*****************************************************************************
EnemyHP EnemyHPWk[ENEMY_MAX];

//=============================================================================
// 取得
//=============================================================================
EnemyHP *GetEnemyHP(int no)
{
	return &EnemyHPWk[no];
}

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemyHP(void)
{
	EnemyHP *EnemyHP = GetEnemyHP(0);

	// パラメータ
	const Vector3 tempPos = Vector3(0, 0, 0);
	const Vector2 tempSize = Vector2(64, 4);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		(EnemyHP + i)->LoadTexture("data/TEXTURE/UI/enemyHP.png");
		(EnemyHP + i)->Init(tempPos, tempSize);
		(EnemyHP + i)->InitVertexEnemyHP();
	}

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyHP(void)
{
	EnemyHP *e = GetEnemyHP(0);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		(e + i)->Release();

	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyHP(void)
{
	ENEMY *Enemy = GetEnemyRE(0);
	EnemyHP *EnemyHP = GetEnemyHP(0);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if ((Enemy + i)->use == TRUE)
		{
			(EnemyHP + i)->Draw();
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyHP(void)
{
	ENEMY *Enemy = GetEnemyRE(0);
	
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if ((Enemy + i)->use == TRUE)
		{
			SetEnemyHP(i);

			#ifdef _DEBUG
			// テスト用
			if (GetKeyboardTrigger(DIK_A))
			{
				(Enemy + i)->hp -= 2;
			}
			#endif
		}
	}
}

//=============================================================================
// セット処理
//=============================================================================
void SetEnemyHP(int no)
{
	ENEMY *Enemy = GetEnemyRE(no);
	EnemyDB *EnemyDB = GetEnemyDB(Enemy->type);
	EnemyHP *EnemyHP = GetEnemyHP(no);

	float hpRate = 1.0f - ( float(Enemy->hp) / float(EnemyDB->GetHP()) );
	if (hpRate > 1.0f) { hpRate = 1.0f; }
	if (hpRate < 0.0f) { hpRate = 0.0f; }
	float sizeX = EnemyHP->GetSizeX() * hpRate;

	EnemyHP->SetVertexEnemyHP(sizeX, hpRate);
}